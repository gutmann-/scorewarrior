#ifndef SCOREWARRIOR_COMMAND_UNIT_COMMAND_H_
#define SCOREWARRIOR_COMMAND_UNIT_COMMAND_H_

#include "scorewarrior/command/command.h"

namespace scorewarrior::command {

/**
 * Команда, связанная с юнитом.
 */
class UnitCommand : public Command {
public:
  /**
   * @param unit_id id юнита, связанного с этой командой.
   */
  explicit UnitCommand(int unit_id) : Command(),
                                      unit_id_(unit_id) {}

  [[nodiscard]] int unit_id() const { return unit_id_; }
private:
  const int unit_id_;
};

} // namespace scorewarrior::command

#endif // SCOREWARRIOR_COMMAND_UNIT_COMMAND_H_
