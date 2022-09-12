#include "scorewarrior/game/command/kill.h"

#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

// static
std::unique_ptr<Kill> Kill::Units(const std::unordered_set<int>& unit_ids, world::World* world) {
  std::unique_ptr<Kill> kill;

  for (const auto& unit_id : unit_ids) {
    auto command = std::make_unique<Kill>(unit_id, world);
    command->Then(std::move(kill));
    kill = std::move(command);
  }

  return kill;
}

Kill::Kill(int unit_id, world::World* world)
    : UnitCommand(unit_id),
      world_(world) {}

bool Kill::Execute(uint32_t current_time) {
  auto map = world_->take_map();
  map->ExtractUnit(unit_id());
  world_->set_map(std::move(map));
  return true;
}

} // namespace scorewarrior::game::command