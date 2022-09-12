#ifndef SCOREWARRIOR_PARSER_COMMAND_FILE_H_
#define SCOREWARRIOR_PARSER_COMMAND_FILE_H_

#include "scorewarrior/command/stream.h"

#include <istream>
#include <unordered_map>

namespace scorewarrior::parser {

class CommandFile : public command::Stream {
public:
  explicit CommandFile(std::unique_ptr<std::istream> stream);

  std::unique_ptr<command::Command> Pull() override;
  [[nodiscard]] bool eof() const override;
private:
  using ParseCommandFunction = std::function<std::unique_ptr<command::Command>()>;

  std::unique_ptr<command::Command> ParseCreateMap();
  std::unique_ptr<command::Command> ParseSpawn();
  std::unique_ptr<command::Command> ParseMarch();
  std::unique_ptr<command::Command> ParseWait();
  std::unique_ptr<command::Command> ParseFinish();

  std::unordered_map<std::string, ParseCommandFunction> ParseTable();


  std::unique_ptr<std::istream> stream_;
  std::unordered_map<std::string, ParseCommandFunction> parse_table_;
};

} // namespace scorewarrior::parser

#endif // SCOREWARRIOR_PARSER_COMMAND_FILE_H_
