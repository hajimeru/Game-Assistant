#ifndef GAMEASSISTANT_TERMINAL_CONFIG_H_ 
#define GAMEASSISTANT_TERMINAL_CONFIG_H_
#include "game_assistant_global.h"
#include "abstract_config.h"
#include "global_struct_define.h"
#include <QHash>
NAMESPACE_GAME_ASSISTANT_BEGIN
class TerminalConfig : public AbstractConfig {
public:
  virtual ~TerminalConfig() = default;

  const QHash<QString, EmulatorInfo>& get_emulators_map() const noexcept {
    return emulators_info_;
  }

protected:
  virtual bool Parse(const rapidjson::Document& document) override;

private:
  QHash<QString, EmulatorInfo> emulators_info_;
};

NAMESPACE_GAME_ASSISTANT_END
#endif // !GAMEASSISTANT_TERMINAL_CONFIG_H_
