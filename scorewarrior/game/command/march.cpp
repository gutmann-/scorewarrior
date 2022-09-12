#include "scorewarrior/game/command/march.h"

#include <bits/stdc++.h>

namespace scorewarrior::game::command {

March::March(int unit_id, const world::Position& to_position, world::World* world)
     : UnitCommand(unit_id),
       unit_(),
       start_position_(),
       to_position_(to_position),
       ticks_marched_(0),
       ticks_to_march_(-1),
       world_(world) {}

void March::OnBegin(const std::function<void(March*)>& on_begin) {
  UnitCommand::OnBegin([this, on_begin](Command*){ on_begin(this); });
}

void March::OnDone(const std::function<void(March*)>& on_done) {
  UnitCommand::OnDone([this, on_done](Command*){ on_done(this); });
}

void March::Init(uint32_t current_time) {
  auto map = world_->take_map();

  start_position_ = map->PositionOfUnit(unit_id());
  unit_ = map->ExtractUnit(unit_id());

  world_->set_map(std::move(map));

  ticks_to_march_ = CalculateMarchTime();
}

bool March::Execute(uint32_t current_time) {
  ticks_marched_ += current_time - previous_call_tick();

  const bool is_done = ticks_to_march_ != -1 && ticks_marched_ >= ticks_to_march_;

  if (is_done) {
    auto map = world_->take_map();
    map->PlaceUnit(to_position_, std::move(unit_));
    world_->set_map(std::move(map));
  }

  return is_done;
}

int March::CalculateMarchTime() const {
  return static_cast<int>(sqrt(
        (to_position_.x() - start_position_.x()) * (to_position_.x() - start_position_.x()) +
        (to_position_.y() - start_position_.y()) * (to_position_.y() - start_position_.y())
      ));
}

} // scorewarrior::game::command
