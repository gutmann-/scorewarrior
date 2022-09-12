#ifndef SCOREWARRIOR_GAME_COMMAND_SPAWN_H_
#define SCOREWARRIOR_GAME_COMMAND_SPAWN_H_

#include "scorewarrior/command/command.h"
#include "scorewarrior/world/position.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

class Spawn : public scorewarrior::command::Command {
public:
  using UnitMaker = std::function<std::unique_ptr<units::Unit>()>;

  Spawn(UnitMaker unit_maker, const world::Position& where, world::World* world);

  void OnDone(const std::function<void(Spawn*)>& on_done);

  [[nodiscard]] int unit_id() const { return unit_id_; }
  [[nodiscard]] const world::Position& where() const { return where_; }
private:
  bool Execute(uint32_t current_time) override;


  UnitMaker unit_maker_;
  int unit_id_;
  const world::Position where_;
  world::World* world_;
};

} // scorewarrior::game::command

#endif // SCOREWARRIOR_GAME_COMMAND_SPAWN_H_
