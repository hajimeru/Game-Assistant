#ifndef GAME_ASSISTANT_RESOURCE_H_
#define GAME_ASSISTANT_RESOURCE_H_
#include "game_assistant_global.h"
#include "abstract_resource.h"

#include "terminal_config.h"

NAMESPACE_GAME_ASSISTANT_BEGIN
class Resource : public AbstractResource {
public:
  virtual ~Resource() = default;

  static Resource& get_instance() {
    static Resource unique_instance;
    return unique_instance;
  }

  virtual bool Load(const QString& dir) override;

  const TerminalConfig& get_terminal_config() const noexcept {
    return terminal_config_unique_ins_;
  }

  Resource& operator=(const Resource&) = delete;
  Resource& operator=(Resource&&) noexcept = delete;

private:
  Resource() = default;

  TerminalConfig terminal_config_unique_ins_;
};

static auto& resource_instance = Resource::get_instance();
NAMESPACE_GAME_ASSISTANT_END
#endif // GAME_ASSISTANT_RESOURCE_H_
