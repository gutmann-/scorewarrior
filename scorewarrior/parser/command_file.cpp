#include "scorewarrior/parser/command_file.h"

#include "scorewarrior/command/factory.h"

namespace scorewarrior::parser {

CommandFile::CommandFile(std::unique_ptr<std::istream> stream)
           : Stream(),
             stream_(std::move(stream)),
             parse_table_() {
  parse_table_ = ParseTable();
}

std::unique_ptr<command::Command> CommandFile::Pull() {
  std::unique_ptr<command::Command> command;

  std::string command_str;
  *stream_ >> command_str;

  if (!eof()) {
    auto parse_iterator = parse_table_.find(command_str);
    if (parse_iterator != parse_table_.end()) {
      auto parse = parse_iterator->second;
      command = parse();
    }
  }

  return command;
}

bool CommandFile::eof() const {
  return stream_->eof();
}

std::unique_ptr<command::Command> CommandFile::ParseCreateMap() {
  int w, h;
  *stream_ >> w >> h;

  return factory()->MakeCreateMapCommand(w, h);
}

std::unique_ptr<command::Command> CommandFile::ParseSpawn() {
  int unit_id, x, y, strength;
  *stream_ >> unit_id >> x >> y >> strength;

  return factory()->MakeSpawnCommand(unit_id, x, y, strength);
}

std::unique_ptr<command::Command> CommandFile::ParseMarch() {
  int unit_id, x, y;
  *stream_ >> unit_id >> x >> y;

  return factory()->MakeMarchCommand(unit_id, x, y);
}

std::unique_ptr<command::Command> CommandFile::ParseWait() {
  int ticks;
  *stream_ >> ticks;

  return factory()->MakeWaitCommand(ticks);
}

std::unique_ptr<command::Command> CommandFile::ParseFinish() {
  return factory()->MakeFinishCommand();
}

std::unordered_map<std::string, CommandFile::ParseCommandFunction>
    CommandFile::ParseTable() {
  std::unordered_map<std::string, ParseCommandFunction> table = {
      { "CREATE_MAP", [this]() { return ParseCreateMap(); } },
      { "SPAWN", [this]() { return ParseSpawn(); } },
      { "MARCH", [this]() { return ParseMarch(); } },
      { "WAIT", [this]() { return ParseWait(); } },
      { "FINISH", [this] { return ParseFinish(); } },
  };

  return table;
}

} // namespace scorewarrior::parser