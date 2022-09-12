#ifndef SCOREWARRIOR_GAME_UNIT_MOVING_HISTORY_H_
#define SCOREWARRIOR_GAME_UNIT_MOVING_HISTORY_H_

#include "scorewarrior/world/position.h"

#include <cstddef>
#include <deque>
#include <unordered_map>

namespace scorewarrior::game {

class UnitMovingHistory {
public:
  explicit UnitMovingHistory(int max_positions_per_unit = -1);

  void LogNewPosition(int unit_id, const world::Position& position);
  const world::Position& Position(int unit_id, int offset) const;
  size_t NumberOfUnitMoves(int unit_id) const;

  void ClearHistoryForUnit(int unit_id);
  void Clear();
private:
  std::deque<world::Position>* HistoryForUnitId(int unit_id);
  const std::deque<world::Position>& HistoryForUnitId(int unit_id) const;

  void LogNewPosition(std::deque<world::Position>* into, const world::Position& position);
  const world::Position& Position(const std::deque<world::Position>& history, int offset) const;


  const int max_positions_per_unit_;
  std::unordered_map<int, std::deque<world::Position>> history_;
};

} // namespace scorewarrior::game

#endif // SCOREWARRIOR_GAME_UNIT_MOVING_HISTORY_H_
