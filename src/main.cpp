#include "project_test_mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <qdebug.h>

#include "terminal_config.h"
int main(int argc, char *argv[])
{
  USING_NAMESPACE_GAME_ASSISTANT;

  QApplication a(argc, argv);
  MainWindow w;

  //[test] QProcess
  //QProcess* process = new QProcess();
  //process->start("C:/Windows/system32/cmd.exe", QStringList() << "/c" << "ping www.baidu.com");
  //process->waitForStarted();
  //process->waitForFinished();
  //QString str = QString::fromLocal8Bit(process->readAllStandardOutput());
  //qDebug() << "[QProcess]" << str;

  w.show();
  return a.exec();
}