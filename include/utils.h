#ifndef GAMEASSISTANT_UTILS_H_
#define GAMEASSISTANT_UTILS_H_

#include "game_assistant_global.h"

#include <QApplication>
#include <QString>
#include <QFile>
#include <QDebug>

NAMESPACE_GAME_ASSISTANT_BEGIN
namespace utils {
  static QString get_current_dir() 
  {
    static QString current_dir = QApplication::applicationDirPath()+ "/";
    return current_dir;
  }

  static QString get_resource_dir() 
  {
    static QString resource_dir = get_current_dir() + "../resource/";
    return resource_dir;
  }

  static QString ReplaceStringAll(const QString& src, const QString& old_value, const QString& new_value) 
  {
    QString str = src;
    for (int pos = 0; pos < str.length(); pos += new_value.length()) {
      if ((pos = str.indexOf(old_value, pos)) != -1)
        str.replace(pos, old_value.length(), new_value);
      else
        break;
    }
    return str;
  }

  static QString LoadFileByString(const QString& filename) 
  {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
      qDebug() << "Can't open the file by string!" << endl;
      return QString();
    }

    QString str;
    while (!file.atEnd()){
      QByteArray line = file.readLine();
      QString line_str(line);
      str.append(line_str);
    }
    return str;
  }
}
NAMESPACE_GAME_ASSISTANT_END
#endif
