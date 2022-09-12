#include "scorewarrior/game/command/wait.h"

#include "scorewarrior/command/executor.h"
#include "scorewarrior/world/ticker.h"

namespace scorewarrior::game::command {

Wait::Wait(int ticks, Executor* executor, world::Ticker* ticker)
    : Command(),
      ticks_wait_(ticks),
      executor_(executor),
      ticker_(ticker) {}

bool Wait::Execute(uint32_t current_time) {
  executor_->Rewind();
  (*ticker_) += ticks_wait_;
  return true;
}

} // namespace scorewarrior::game::command