#ifndef GAME_ASSISTANT_CONTROLLER_H_
#define GAME_ASSISTANT_CONTROLLER_H_
#include "game_assistant_global.h"
#include <QPair>
#include <QVector>

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

  Controller& operator=(const Controller&) = delete;
  Controller& operator=(Controller&&) = delete;
private:
  Controller();

  QPair<bool, QVector<unsigned char>> CallCommand(const QString& cmd);
  bool Screencap();
};
static auto& controller_instance = Controller::get_instance();
NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_CONTROLLER_H_
