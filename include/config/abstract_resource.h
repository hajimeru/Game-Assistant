#ifndef GAMEASSISTANT_ABSTRACT_RESOURCE_H_
#define GAMEASSISTANT_ABSTRACT_RESOURCE_H_

#include "game_assistant_global.h"
#include <QString>

NAMESPACE_GAME_ASSISTANT_BEGIN
class AbstractResource {
public:
  AbstractResource() = default;
  AbstractResource(const AbstractResource& rhs) = delete;
  AbstractResource(AbstractResource&& rhs) noexcept = delete;

  virtual ~AbstractResource() = default;

  virtual bool Load(const QString& filename) = 0;
  virtual const QString& get_last_error() const noexcept
  {
    return last_error_;
  }
 
  AbstractResource& operator=(const AbstractResource& rhs) = delete;
  AbstractResource& operator=(AbstractResource&& rhs) = delete;

protected:
  QString last_error_;
};
NAMESPACE_GAME_ASSISTANT_END
#endif