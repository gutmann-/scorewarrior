#ifndef SCOREWARRIOR_GAME_COMMAND_KILL_H_
#define SCOREWARRIOR_GAME_COMMAND_KILL_H_

#include "scorewarrior/command/unit_command.h"

#include <unordered_set>

namespace scorewarrior {
namespace world {

class World;

} // namespace world

namespace game::command {

class Kill : public scorewarrior::command::UnitCommand {
public:
  static std::unique_ptr<Kill> Units(const std::unordered_set<int>& unit_ids, world::World* world);

  Kill(int unit_id, world::World* world);
private:
  bool Execute(uint32_t current_time) override;


  world::World* world_;
};

} // namespace game::command
} // namespace scorewarrior

#endif // SCOREWARRIOR_GAME_COMMAND_KILL_H_
