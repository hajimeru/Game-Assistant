#include "resource.h"

USING_NAMESPACE_GAME_ASSISTANT

bool Resource::Load(const QString& dir)
{
  constexpr static const char* kTerminalConfigFileName = "terminal.json";

  if (!terminal_config_unique_ins_.Load(dir + kTerminalConfigFileName)) {
    last_error_ = terminal_config_unique_ins_.get_last_error();
    return false;
  }

  return true;
}
