#ifndef GAMEASSISTANT_ABSTRACT_CONFIG_H_
#define GAMEASSISTANT_ABSTRACT_CONFIG_H_

#include "game_assistant_global.h"
#include "abstract_resource.h"
#include <rapidjson/document.h>

NAMESPACE_GAME_ASSISTANT_BEGIN
class AbstractConfig : public AbstractResource {
public:
  virtual ~AbstractConfig() = default;
  virtual bool load(const QString& filename) override;

protected:
  virtual bool parse(const rapidjson::Document& document) = 0;
};
NAMESPACE_GAME_ASSISTANT_END
#endif
