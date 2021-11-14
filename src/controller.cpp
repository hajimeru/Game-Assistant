#include "controller.h"

USING_NAMESPACE_GAME_ASSISTANT

Controller::Controller()
{

}

QPair<bool, QVector<unsigned char>> Controller::CallCommand(const QString& cmd)
{
  return QPair<bool, QVector<unsigned char>>();
}

bool Controller::Screencap()
{
  return true;
}

Controller::~Controller()
{

}
