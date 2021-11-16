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

  //调用 CallCommand
  return true;
}
