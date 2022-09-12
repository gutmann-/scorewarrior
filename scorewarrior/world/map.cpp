#include "scorewarrior/world/map.h"

#include <stdexcept>


namespace scorewarrior::world {

Map::Map(int width, int height)
   : width_(width), height_(height),
     map_(),
     unit_place_() {}

void Map::PlaceUnit(const Position& where, std::unique_ptr<units::Unit> unit) {
  ValidatePosition(where);
  if (!unit) return;

  ExtractUnit(unit->id());

  const auto unit_id = unit->id();
  unit_place_[unit_id] = where;
  map_[where].emplace(unit_id, std::move(unit));
}

std::unique_ptr<units::Unit> Map::ExtractUnit(int unit_id) {
  std::unique_ptr<units::Unit> extracted;

  auto unit_position_iterator = unit_place_.find(unit_id);
  if (unit_position_iterator != unit_place_.end()) {
    const auto& unit_position = unit_position_iterator->second;

    auto& units = map_[unit_position];
    auto unit_iterator = units.find(unit_id);

    extracted = std::move(unit_iterator->second);
    units.erase(unit_iterator);

    unit_place_.erase(unit_position_iterator);

    if (map_[unit_position].empty())
      map_.erase(unit_position);
  }

  return extracted;
}

Position Map::PositionOfUnit(int unit_id) const {
  auto unit_position_iterator = unit_place_.find(unit_id);
  if (unit_position_iterator != unit_place_.end()) {
    return unit_position_iterator->second;
  } else {
    const auto err_str = std::string("Can't locate unit with id == ") +
        std::to_string(unit_id);
    throw std::out_of_range(err_str);
  }
}

std::set<int> Map::UnitsIdsInPlace(const Position& position) const {
  ValidatePosition(position);

  std::set<int> ids;

  auto units_iterator = map_.find(position);
  if (units_iterator != map_.end()) {
    for (auto& [_, unit] : units_iterator->second)
      ids.insert(unit->id());
  }

  return ids;
}

size_t Map::NumerOfUnitsInPlace(const Position& position) const {
  ValidatePosition(position);

  auto units_iterator = map_.find(position);
  if (units_iterator != map_.end())
    return units_iterator->second.size();
  return 0;
}

bool Map::ContainsUnit(int unit_id) const {
  auto unit_position_iterator = unit_place_.find(unit_id);
  return unit_position_iterator != unit_place_.end();
}

void Map::ValidatePosition(const Position& position) const {
  if (position.x() >= width() || position.y() >= height()) {
    const auto err_str = std::string("Position [") +
        std::to_string(position.x()) + "; " + std::to_string(position.y()) + "]" +
        " is outside of the map " + std::to_string(width()) + "X" + std::to_string(height());
    throw std::out_of_range(err_str);
  }
}

} // namespace scorewarrior::world