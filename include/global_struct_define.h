#ifndef GAME_ASSISTANT_GLOBAL_STRUCT_DEFINE_H_
#define GAME_ASSISTANT_GLOBAL_STRUCT_DEFINE_H_
#include "game_assistant_global.h"
#include <QString>

NAMESPACE_GAME_ASSISTANT_BEGIN

struct AdbCmd {
  QString path;
  QString connect;
  QString click;
  QString swipe;
  QString display;
  QString display_regex;
  QString screencap;
};

struct EmulatorInfo {
  QString name;
  QString execdir;
  AdbCmd adb;
};

NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_GLOBAL_STRUCT_DEFINE_H_
