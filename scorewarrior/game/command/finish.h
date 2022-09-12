#ifndef SCOREWARRIOR_GAME_COMMAND_FINISH_H_
#define SCOREWARRIOR_GAME_COMMAND_FINISH_H_

#include "scorewarrior/command/command.h"

namespace scorewarrior {
namespace command {

class Executor;

} // namespace command

namespace game::command {

class Finish : public scorewarrior::command::Command {
public:
  using Executor = scorewarrior::command::Executor;

  explicit Finish(Executor* executor);
private:
  bool Execute(uint32_t current_time) override;

  Executor* executor_;
};

} // namespace game::command
} // namespace scorewarrior

#endif // SCOREWARRIOR_GAME_COMMAND_FINISH_H_
