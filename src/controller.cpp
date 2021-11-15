#include "controller.h"
#include <QProcess>
#include <QMutex>
#include <QDebug>

USING_NAMESPACE_GAME_ASSISTANT

Controller::Controller()
{

}

QPair<bool, QVector<unsigned char>> Controller::CallCommand(const QString& cmd)
{
  static QMutex mutex;
  QMutexLocker locker(&mutex);

  QProcess process;
  process.start(cmd);
  process.waitForFinished(0);

  //处理返回的数据
  qDebug() << QString::fromLocal8Bit(process.readAllStandardOutput());
  return QPair<bool, QVector<unsigned char>>();
}

bool Controller::Screencap()
{
  //处理截图的命令

  //调用 CallCommand
  return true;
}

Controller::~Controller()
{

}
