#ifndef GAME_ASSISTANT_CONTROLLER_H_
#define GAME_ASSISTANT_CONTROLLER_H_
#include "game_assistant_global.h"
#include <QPair>
#include <QVector>

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

  bool TryCaptureEmulator(const EmulatorInfo& emulator_info);

  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;

  void TestScreencap() { Screencap(); }

private:
  Controller();
  QPair<bool, QByteArray> CallCommand(const QString& cmd);
  bool Screencap();
  void ConvertCrlfToLf(QByteArray& data);
private:
  EmulatorInfo emulator_info_;
};
static auto& controller_instance = Controller::get_instance();
NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_CONTROLLER_H_
