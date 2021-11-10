#ifndef GAMEASSISTANT_PROJECT_TEST_MAINWINDOW_H_
#define GAMEASSISTANT_PROJECT_TEST_MAINWINDOW_H_

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
};


#endif // !PROJECT_TEST_H
