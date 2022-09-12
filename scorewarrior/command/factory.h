#ifndef SCOREWARRIOR_COMMAND_FACTORY_H_
#define SCOREWARRIOR_COMMAND_FACTORY_H_

#include "scorewarrior/command/command.h"

#include <memory>

namespace scorewarrior::command {

/**
 * Фабрика команд.
 */
class Factory {
public:
  virtual ~Factory() = default;

  virtual std::unique_ptr<Command> MakeCreateMapCommand(int width, int height) = 0;
  virtual std::unique_ptr<Command> MakeSpawnCommand(int unit_id, int x, int y, int strength) = 0;
  virtual std::unique_ptr<Command> MakeMarchCommand(int unit_id, int x, int y) = 0;
  virtual std::unique_ptr<Command> MakeWaitCommand(int ticks) = 0;
  virtual std::unique_ptr<Command> MakeFinishCommand() = 0;
};

} // namespace scorewarrior::command

#endif // SCOREWARRIOR_COMMAND_FACTORY_H_
