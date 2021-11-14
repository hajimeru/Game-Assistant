#include "abstract_config.h"
#include <rapidjson/error/en.h>

#include "utils.h"
USING_NAMESPACE_GAME_ASSISTANT

bool AbstractConfig::Load(const QString& filename)
{
  QString json = utils::LoadFileByString(filename);
  rapidjson::Document document;
  document.Parse(json.toStdString().c_str()); // ������Parse()�޷���ֵ��Ҳ�������쳣
  if (document.HasParseError()) // ͨ��HasParseError()���жϽ����Ƿ�ɹ�
  {
    // ��ͨ��GetParseError()ȡ�ó�����룬
    // ע��GetParseError()���ص���һ��rapidjson::ParseErrorCode���͵�ö��ֵ
    // ʹ�ú���rapidjson::GetParseError_En()�õ���������ַ���˵���������EnΪEnglish��д
    // ����GetErrorOffset()���س�������λ��
    qDebug()<< QString::asprintf("parse error: (%d:%d)%s\n", document.GetParseError(), document.GetErrorOffset(), rapidjson::GetParseError_En(document.GetParseError()));
    return false;
  }
  return Parse(document);
}