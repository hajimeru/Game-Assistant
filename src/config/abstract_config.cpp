#include "abstract_config.h"
#include <rapidjson/error/en.h>

#include "utils.h"
USING_NAMESPACE_GAME_ASSISTANT

bool AbstractConfig::Load(const QString& filename)
{
  QString json = utils::LoadFileByString(filename);
  rapidjson::Document document;
  document.Parse(json.toStdString().c_str()); // 解析，Parse()无返回值，也不会抛异常
  if (document.HasParseError()) // 通过HasParseError()来判断解析是否成功
  {
    // 可通过GetParseError()取得出错代码，
    // 注意GetParseError()返回的是一个rapidjson::ParseErrorCode类型的枚举值
    // 使用函数rapidjson::GetParseError_En()得到错误码的字符串说明，这里的En为English简写
    // 函数GetErrorOffset()返回出错发生的位置
    qDebug()<< QString::asprintf("parse error: (%d:%d)%s\n", document.GetParseError(), document.GetErrorOffset(), rapidjson::GetParseError_En(document.GetParseError()));
    return false;
  }
  return Parse(document);
}