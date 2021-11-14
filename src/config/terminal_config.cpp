#include "terminal_config.h"

NAMESPACE_GAME_ASSISTANT_BEGIN

bool TerminalConfig::Parse(const rapidjson::Document& document) {

  for (auto itr = document["emulator"].MemberBegin(); itr != document["emulator"].MemberEnd(); ++itr) {
    EmulatorInfo emulator_info;
    emulator_info.name = itr->name.GetString();

    emulator_info.execdir = itr->value["execdir"].GetString();

    auto adb_json = itr->value["adb"].GetObject();
    emulator_info.adb.path = adb_json["path"].GetString();
    emulator_info.adb.connect = adb_json["connect"].GetString();
    emulator_info.adb.click = adb_json["click"].GetString();
    emulator_info.adb.swipe = adb_json["swipe"].GetString();
    emulator_info.adb.display = adb_json["display"].GetString();
    emulator_info.adb.display_regex = adb_json["display_regex"].GetString();
    emulator_info.adb.screencap = adb_json["screencap"].GetString();

    emulators_info_.insert(emulator_info.name, emulator_info);
  }
  return true;
}

NAMESPACE_GAME_ASSISTANT_END