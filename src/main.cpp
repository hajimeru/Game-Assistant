#include "project_test_mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <qdebug.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	QProcess* process = new QProcess();
	process->start("C:/Windows/system32/cmd.exe",QStringList() <<"/c"<<"ping www.baidu.com");
	process->waitForStarted();
	process->waitForFinished();
	QString str = QString::fromLocal8Bit(process->readAllStandardOutput());
	qDebug() << "[QProcess]" << str;

	w.show();
	return a.exec();
}