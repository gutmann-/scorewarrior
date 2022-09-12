#include "scorewarrior/command/command.h"

namespace scorewarrior::command {

Command::Command()
       : last_known_tick_(0),
         called_once_(false),
         is_done_(false),
         on_begin_(),
         on_done_(),
         then_() {}

void Command::operator()(uint32_t current_time) {
  if (!called_once_) {
    Init(current_time);
    CallOnBegin();

    last_known_tick_ = current_time;
    called_once_ = true;
  }

  if (!is_done_) {
    is_done_ = Execute(current_time);
    last_known_tick_ = current_time;

    if (is_done_)
      CallOnDone();
  }
}

} // namespace scorewarrior::command