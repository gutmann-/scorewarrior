#include "scorewarrior/game/command/fight.h"

namespace scorewarrior::game::command {

Fight::Fight(int unit_id, world::World* world)
     : UnitCommand(unit_id),
       world_(world),
       enemy_id_(units::Unit::NOT_INITIALIZED_ID),
       winner_id_(units::Unit::NOT_INITIALIZED_ID),
       dispatcher_() {
  auto do_fight = [this](units::Warrior* w1, units::Warrior* w2) {
    CalculateWinner(w1, w2);
  };

  dispatcher_.RegisterHandler(std::function(do_fight));
}

void Fight::OnDone(const std::function<void(Fight*)>& on_done) {
  if (on_done)
    Command::OnDone([this, on_done](Command*){ on_done(this); });
}

void Fight::Init(uint32_t current_time) {
  auto map = world_->take_map();

  auto unit_position = map->PositionOfUnit(unit_id());
  auto units_ids_in_position = map->UnitsIdsInPlace(unit_position);

  if (units_ids_in_position.size() >= 2) {     // в данной клетке есть ещё юниты
    units_ids_in_position.erase(unit_id()); // убираем idшник чтобы не драться сами с собой,
                                               // после этого тут будут только противники
    enemy_id_ = *units_ids_in_position.begin();
  }

  world_->set_map(std::move(map));
}

bool Fight::Execute(uint32_t current_time) {
  auto map = world_->take_map();

  if (!map->ContainsUnit(unit_id())) return true;
  auto unit_position = map->PositionOfUnit(unit_id());

  auto unit = map->ExtractUnit(unit_id());
  auto enemy = map->ExtractUnit(enemy_id());

  dispatcher_.Handle(unit.get(), enemy.get());

  if (winner_id_ == unit->id())
    map->PlaceUnit(unit_position, std::move(unit));
  else if (winner_id_ == enemy->id())
    map->PlaceUnit(unit_position, std::move(enemy));

  world_->set_map(std::move(map));
  return true;
}

void Fight::CalculateWinner(units::Warrior* w1, units::Warrior* w2) {
  if (w1->strength() > w2->strength())
    winner_id_ = w1->id();
  else if (w1->strength() < w2->strength())
    winner_id_ = w2->id();
  else
    winner_id_ = units::Unit::NOT_INITIALIZED_ID;
}

} // namespace scorewarrior::game::command