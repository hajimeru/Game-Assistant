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

  //�����ص�����
  qDebug() << QString::fromLocal8Bit(process.readAllStandardOutput());
  return QPair<bool, QVector<unsigned char>>();
}

bool Controller::Screencap()
{
  //�����ͼ������

  //���� CallCommand
  return true;
}

Controller::~Controller()
{

}
