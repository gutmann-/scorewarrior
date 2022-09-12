#include "scorewarrior/game/command/finish.h"

#include "scorewarrior/command/executor.h"

namespace scorewarrior::game::command {

Finish::Finish(Executor* executor)
      : Command(),
        executor_(executor) {}

bool Finish::Execute(uint32_t current_time) {
  executor_->Rewind();
  return executor_->number_of_not_finished_commands() == 1;
}

} // namespace scorewarrior::game::command