#ifndef SCOREWARRIOR_GAME_COMMAND_MARCH_H_
#define SCOREWARRIOR_GAME_COMMAND_MARCH_H_

#include "scorewarrior/command/unit_command.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

class March : public scorewarrior::command::UnitCommand {
public:
  March(int unit_id, const world::Position& to_position, world::World* world);

  void OnBegin(const std::function<void(March*)>& on_begin);
  void OnDone(const std::function<void(March*)>& on_done);

  [[nodiscard]] const world::Position& from_position() const { return start_position_; }
  [[nodiscard]] const world::Position& to_position() const { return to_position_; }
private:
  void Init(uint32_t current_time) override;
  bool Execute(uint32_t current_time) override;

  [[nodiscard]] int CalculateMarchTime() const;


  std::unique_ptr<units::Unit> unit_;

  world::Position start_position_;
  const world::Position to_position_;

  uint32_t ticks_marched_, ticks_to_march_;

  world::World* world_;
};

} // scorewarrior::game::command

#endif // SCOREWARRIOR_GAME_COMMAND_MARCH_H_
