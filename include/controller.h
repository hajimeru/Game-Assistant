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

  //��ʼ����ȡģ�����������Ϣ
  bool TryCaptureEmulator(const EmulatorInfo& emulator_info);
  //��ȡ��ǰģ������ͼ
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
  //ģ������Ϣ
  EmulatorInfo emulator_info_;
  int display_height_;
  int display_width_;
  //��ͼ����
  cv::Mat cache_image_;

  // �������
  QMutex cmd_queue_mutex_;
  QWaitCondition cmd_wait_condition;
  QQueue<QString> cmd_queue_;
  unsigned int push_id_ = 0;
  unsigned int complete_id_ = 0;
  //cmd���й����߳�
  bool is_cmd_thread_exit = false;
};
static auto& controller_instance = Controller::get_instance();
NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_CONTROLLER_H_
