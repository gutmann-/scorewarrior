#include "scorewarrior/command/executor.h"

namespace scorewarrior::command {

Executor::Executor()
        : commands_(),
          next_command_index_(0),
          number_of_not_finished_commands_(0) {}

void Executor::operator()(uint32_t current_time) {
  auto command_iterator = NextNotDoneCommand();
  if (command_iterator != End()) {
    auto& command = *command_iterator;
    command = Execute(std::move(command), current_time);
  }
}

void Executor::PushCommand(std::unique_ptr<Command> command) {
  if (!command) return;

  if (!command->is_done()) ++number_of_not_finished_commands_;
  commands_.emplace_back(std::move(command));
}

void Executor::Rewind() {
  next_command_index_ = 0;
}

bool Executor::all_is_done() const {
  return number_of_not_finished_commands() == 0;
}

size_t Executor::number_of_not_finished_commands() const {
  return number_of_not_finished_commands_;
}

void Executor::CleanFinishedCommands() {
  decltype(commands_) not_done_yet;

  for (auto& command : commands_) {
    if (!command->is_done())
      not_done_yet.emplace_back(std::move(command));
  }

  commands_ = std::move(not_done_yet);
}

std::unique_ptr<Command> Executor::Execute(std::unique_ptr<Command> command, uint32_t current_time) {
  (*command)(current_time);

  // может у нас после завершения команды есть ещё те,
  // которые надо выполнить сразу вслед за ней?
  while (command->is_done()) {
    --number_of_not_finished_commands_;

    if (auto then = command->Then()) {
      ++number_of_not_finished_commands_;
      command = std::move(then);
      (*command)(current_time);
    } else
      break;
  }

  return command;
}

Executor::CommandIterator Executor::NextCommand() {
  if (next_command_index_ >= commands_.size()) {
    CleanFinishedCommands();
    next_command_index_ = 0;
  }

  return !commands_.empty() ? commands_.begin() + next_command_index_++ : End();
}

Executor::CommandIterator Executor::NextNotDoneCommand() {
  if (all_is_done()) return End();

  CommandIterator iterator;
  do {
    iterator = NextCommand();
  } while (iterator != End() && (*iterator)->is_done());

  return iterator;
}

} // namespace scorewarrior::command