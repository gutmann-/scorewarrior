#include "scorewarrior/game/unit_moving_history.h"

#include <stdexcept>

namespace scorewarrior::game {

UnitMovingHistory::UnitMovingHistory(int max_positions_per_unit)
                 : max_positions_per_unit_(max_positions_per_unit),
                   history_() {}

void UnitMovingHistory::LogNewPosition(int unit_id, const world::Position& position) {
  LogNewPosition(HistoryForUnitId(unit_id), position);
}

const world::Position& UnitMovingHistory::Position(int unit_id, int offset) const {
  return Position(HistoryForUnitId(unit_id), offset);
}

size_t UnitMovingHistory::NumberOfUnitMoves(int unit_id) const {
  return HistoryForUnitId(unit_id).size();
}

void UnitMovingHistory::ClearHistoryForUnit(int unit_id) { history_.erase(unit_id); }
void UnitMovingHistory::Clear() { history_.clear(); }

void UnitMovingHistory::LogNewPosition(std::deque<world::Position>* into, const world::Position& position) {
  into->emplace_back(position);
  if (max_positions_per_unit_ != -1) {
    while (into->size() > max_positions_per_unit_) {
      into->pop_front();
    }
  }
}

std::deque<world::Position>* UnitMovingHistory::HistoryForUnitId(int unit_id) {
  return &history_[unit_id];
}

const std::deque<world::Position>& UnitMovingHistory::HistoryForUnitId(int unit_id) const {
  const auto history_iterator = history_.find(unit_id);
  if (history_iterator != history_.end()) {
    return history_iterator->second;
  } else {
    const auto err_str = std::string("Can't find unit with ID == ") + std::to_string(unit_id);
    throw std::out_of_range(err_str);
  }
}

const world::Position& UnitMovingHistory::Position(const std::deque<world::Position>& history, int offset) const {
  const auto calculated_offset = offset >= 0 ? offset : history.size() + offset;
  if (calculated_offset < history.size()) {
    return history.at(calculated_offset);
  } else {
    throw std::out_of_range("Index out of range");
  }
}

} // namespace scorewarrior::game