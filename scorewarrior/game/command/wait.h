#ifndef SCOREWARRIOR_GAME_COMMAND_WAIT_H_
#define SCOREWARRIOR_GAME_COMMAND_WAIT_H_

#include "scorewarrior/command/command.h"

namespace scorewarrior {

namespace command {

class Executor;

} // namespace command

namespace world {

class Ticker;

} // namespace world

namespace game::command {

class Wait : public scorewarrior::command::Command {
public:
  using Executor = scorewarrior::command::Executor;

  Wait(int ticks, Executor* executor_, world::Ticker* ticker);
private:
  bool Execute(uint32_t current_time) override;

  const int ticks_wait_;

  Executor* executor_;
  world::Ticker* ticker_;
};

} // game::command
} // scorewarrior

#endif // SCOREWARRIOR_GAME_COMMAND_WAIT_H_