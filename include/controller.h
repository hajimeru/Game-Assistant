#ifndef GAME_ASSISTANT_CONTROLLER_H_
#define GAME_ASSISTANT_CONTROLLER_H_
#include "game_assistant_global.h"
#include <QPair>
#include <QVector>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2/opencv.hpp>

#include "global_struct_define.h"

NAMESPACE_GAME_ASSISTANT_BEGIN

class Controller {
public:
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;
  ~Controller();

  static Controller& get_instance() {
    static Controller unique_instance;
    return unique_instance;
  }

  //初始化获取模拟器的相关信息
  bool TryCaptureEmulator(const EmulatorInfo& emulator_info);
  //获取当前模拟器截图
  cv::Mat GetCurrentImage(bool raw);
  

  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;
private:
  Controller();
  QPair<bool, QByteArray> CallCommand(const QString& cmd);
  bool Screencap();
  void ConvertCrlfToLf(QByteArray& data);

  int PushCmd(const QString& cmd);
  void CmdWorkThreadFunc();
private:
  //模拟器信息
  EmulatorInfo emulator_info_;
  int display_height_;
  int display_width_;
  //截图缓存
  cv::Mat cache_image_;

  // 任务队列
  QMutex cmd_queue_mutex_;
  QWaitCondition cmd_wait_condition;
  QQueue<QString> cmd_queue_;
  unsigned int push_id_ = 0;
  unsigned int complete_id_ = 0;
  //cmd队列工作线程
  bool is_cmd_thread_exit = false;
};
static auto& controller_instance = Controller::get_instance();
NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_CONTROLLER_H_
