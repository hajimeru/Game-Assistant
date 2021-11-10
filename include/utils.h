#ifndef GAMEASSISTANT_UTILS_H
#define GAMEASSISTANT_UTILS_H

#include "game_assistant_global.h"

#include <QApplication>
#include <QString>

NAMESPACE_GAME_ASSISTANT_BEGIN
namespace utils {
  static QString get_current_dir() {
    static QString current_dir = QApplication::applicationDirPath();
    return current_dir;
  }

  static QString get_resource_dir() {
    static QString resource_dir = get_current_dir() + "../resource/";
    return resource_dir;
  }

  static QString string_replace_all(const QString& src, const QString& old_value, const QString& new_value) {
    QString str = src;
    for (int pos = 0; pos < str.length(); pos += new_value.length()) {
      if ((pos = str.indexOf(old_value, pos) != -1))
        str.replace(pos, old_value.length(), new_value);
      else
        break;
    }
  }
}
NAMESPACE_GAME_ASSISTANT_END
#endif
