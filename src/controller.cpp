#include "controller.h"
#include <QProcess>
#include <QMutex>
#include <QDebug>
#include <QtConcurrent>
#include "utils.h"
USING_NAMESPACE_GAME_ASSISTANT

Controller::~Controller()
{
  is_cmd_thread_exit = true;
  cmd_wait_condition.notify_all();
}

Controller::Controller()
{
  //启动 cmd 工作线程
  QtConcurrent::run(this,&Controller::CmdWorkThreadFunc);
}

bool Controller::TryCaptureEmulator(const EmulatorInfo& emulator_info)
{
  emulator_info_ = emulator_info;
  QString adb_path = emulator_info_.adb.path;
  QString emulator_dir = emulator_info_.execdir + '/';
  adb_path = utils::ReplaceStringAll(
    adb_path, "[ExecDir]", emulator_dir);
  emulator_info_.adb.path = adb_path;

  QString connect_cmd = emulator_info_.adb.connect;
  connect_cmd = utils::ReplaceStringAll(
    connect_cmd, "[Adb]", adb_path);
  emulator_info_.adb.connect = connect_cmd;

  QString display_cmd = emulator_info_.adb.display;
  display_cmd = utils::ReplaceStringAll(
    display_cmd, "[Adb]", adb_path);
  emulator_info_.adb.display = display_cmd;

  QString screencap_cmd = emulator_info_.adb.screencap;
  screencap_cmd = utils::ReplaceStringAll(
    screencap_cmd, "[Adb]", adb_path);
  emulator_info_.adb.screencap = screencap_cmd;

  QString swipe_cmd = emulator_info_.adb.swipe;
  swipe_cmd = utils::ReplaceStringAll(
    swipe_cmd, "[Adb]", adb_path);
  emulator_info_.adb.swipe = swipe_cmd;

  QString click_cmd = emulator_info_.adb.click;
  click_cmd = utils::ReplaceStringAll(
    click_cmd, "[Adb]", adb_path);
  emulator_info_.adb.click = click_cmd;

  //尝试连接
  auto&& ret_connect_data = CallCommand(emulator_info_.adb.connect);
  // [todo] 即使端口错误，命令仍然会返回 0，需要做进一步的判断
  if (!ret_connect_data.first) {
    return false;
  }
  //获取屏幕大小
  auto&& ret_display_data = CallCommand(emulator_info_.adb.display);
  if (!ret_display_data.first) {
    return false;
  }
  QByteArray display_data = ret_display_data.second;
  QByteArray display_regex = emulator_info_.adb.display_regex.toLocal8Bit();
  int size_value1,size_value2;
  sscanf_s(display_data.data(), display_regex.data(), &size_value1, &size_value2);
  
  display_width_ = qMax(size_value1, size_value2);
  display_height_ = qMin(size_value1, size_value2);

  return true;
}

cv::Mat Controller::GetCurrentImage(bool raw)
{
  if (!Screencap()) {
    return cv::Mat();
  }
  if (raw) {
    return cache_image_;
  }
  else {
    const static cv::Size size(display_width_, display_height_);
    cv::Mat resize_mat;
    cv::resize(cache_image_, resize_mat, size, cv::INPAINT_NS);
    return resize_mat;
  }
}

QPair<bool, QByteArray> Controller::CallCommand(const QString& cmd)
{
  static QMutex mutex;
  QMutexLocker locker(&mutex);

  QProcess process;
  process.start(cmd);
  while (!process.waitForFinished(0) && process.error() == QProcess::Timedout) {
  }

  QByteArray data;
  quint64 error_code = -1;
  if ((error_code = process.exitStatus()) == QProcess::NormalExit) {
    //处理返回的数据
    data = process.readAllStandardOutput();
  }
  else {
    qDebug() << QString::fromLocal8Bit("CallCommand %1 run error").arg(cmd);
  }
  return QPair<bool, QByteArray>(!error_code, data);
}

bool Controller::Screencap()
{
  //处理截图的命令
  auto&& ret_data = CallCommand(emulator_info_.adb.screencap);
  bool ret = ret_data.first;
  QByteArray& data = ret_data.second;
  if (ret && !data.isEmpty()) {
    cache_image_ = cv::imdecode(
      cv::Mat(1, data.length(), CV_8UC1, data.begin()),
      cv::IMREAD_COLOR);
    if (cache_image_.empty()) {
      qDebug() << "Data is not empty, but image is empty, try to convert lf";
      ConvertCrlfToLf(data);
      cache_image_ = cv::imdecode(
        cv::Mat(1, data.length(), CV_8UC1, data.begin()),
        cv::IMREAD_COLOR);
      if (cache_image_.empty()) {
        qDebug() << "convert lf and retry decode falied!";
        return false;
      }
    }
  }
  else {
    qDebug() << "Data is empty!";
    return false;
  }
  return true;
} 

void Controller::ConvertCrlfToLf(QByteArray& data)
{
  if (data.isEmpty() || data.size() <= 1) {
    return;
  }
  
  auto IsCrlf = [](const char* cur)-> bool {
    return *cur == '\r' && *(cur + 1) == '\n';
  };
  
  char* first_iter = NULL;
  for (char* iter = data.begin(); iter != data.end() - 1; ++iter) {
    if (IsCrlf(iter)) {
      first_iter = iter;
      break;
    }
  }

  if (first_iter == NULL) {
    return;
  }

  // 将所有的crlf剔除
  char* end_return1_iter = data.end() - 1;
  char* next_iter = first_iter;
  while (++first_iter != end_return1_iter){
    if (!IsCrlf(first_iter)) {
      *next_iter = std::move(*first_iter);
      ++next_iter;
    }
  }
  *next_iter = std::move(*end_return1_iter);
  ++next_iter;
  data.remove(data.lastIndexOf(next_iter),data.end() - next_iter);
}

int Controller::PushCmd(const QString& cmd)
{
  QMutexLocker locker(&cmd_queue_mutex_);
  cmd_queue_.enqueue(cmd);
  cmd_wait_condition.notify_one();
  return ++push_id_;
}

void Controller::CmdWorkThreadFunc()
{
  while (!is_cmd_thread_exit) {
    QMutexLocker locker(&cmd_queue_mutex_);
    if (!cmd_queue_.empty()) {
      QString cmd = cmd_queue_.dequeue();
      cmd_queue_mutex_.unlock();
      CallCommand(cmd);
      //[todo] 这里还需要判断命令是否执行成功
      ++complete_id_;
    }
    else {
      cmd_wait_condition.wait(&cmd_queue_mutex_);
    }
  }
}