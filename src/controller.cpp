#include "controller.h"
#include <QProcess>
#include <QMutex>
#include <QDebug>
#include "utils.h"
USING_NAMESPACE_GAME_ASSISTANT

Controller::~Controller()
{

}

Controller::Controller()
{

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

  return true;
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
  if (ret && !ret_data.second.isEmpty()) {
    ConvertCrlfToLf(ret_data.second);
  }
  //调用 CallCommand
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
