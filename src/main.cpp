#include "project_test_mainwindow.h"

#include <QApplication>
#include <QProcess>
#include <qdebug.h>

#include "resource.h"
#include "controller.h"
#include "utils.h"

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

  //[test] game_assitant::Resource
  resource_instance.Load(utils::get_resource_dir());
  auto& terminal_config = resource_instance.get_terminal_config();
  auto& emulator_map = terminal_config.get_emulators_map();
  for (auto& m : emulator_map) {
    if(m.name == "LDPlayer64")
      controller_instance.TryCaptureEmulator(m);
  }
  controller_instance.TestScreencap();
  //[test] controller

  w.show();
  return a.exec();
}