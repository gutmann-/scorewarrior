#ifndef SCOREWARRIOR_GAME_COMMAND_FIGHT_H_
#define SCOREWARRIOR_GAME_COMMAND_FIGHT_H_

#include "scorewarrior/command/unit_command.h"

#include "scorewarrior/units/two_units_dispatcher.h"
#include "scorewarrior/units/warrior.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

class Fight : public scorewarrior::command::UnitCommand {
public:
  Fight(int unit_id, world::World* world);

  void OnDone(const std::function<void(Fight*)>& on_done);

  int enemy_id() const { return enemy_id_; }
  int winner_id() const { return winner_id_; }
  bool all_dead() const { return winner_id() == units::Unit::NOT_INITIALIZED_ID; }
private:
  void Init(uint32_t current_time) override;
  bool Execute(uint32_t current_time) override;

  void CalculateWinner(units::Warrior* w1, units::Warrior* w2);

  world::World* world_;

  int enemy_id_;
  int winner_id_;

  units::TwoUnitsDispatcher dispatcher_;
};

} // namespace scorewarrior::game::command

#endif // SCOREWARRIOR_GAME_COMMAND_FIGHT_H_
