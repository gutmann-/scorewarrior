#include "spawn.h"

namespace scorewarrior::game::command {

Spawn::Spawn(UnitMaker unit_maker, const world::Position& where, world::World* world)
     : Command(),
       unit_maker_(std::move(unit_maker)),
       unit_id_(units::Unit::NOT_INITIALIZED_ID),
       where_(where),
       world_(world) {}


void Spawn::OnDone(const std::function<void(Spawn*)>& on_done) {
  if (on_done)
    Command::OnDone([this, on_done](Command*){ on_done(this); });
}

bool Spawn::Execute(uint32_t current_time) {
  auto new_unit = unit_maker_();
  unit_id_ = new_unit->id();

  auto map = world_->take_map();
  map->PlaceUnit(where_, std::move(new_unit));
  world_->set_map(std::move(map));

  return true;
}

} // namespace scorewarrior::game::command