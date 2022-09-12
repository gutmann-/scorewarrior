#ifndef SCOREWARRIOR_WORLD_MAP_H_
#define SCOREWARRIOR_WORLD_MAP_H_

#include "scorewarrior/world/position.h"
#include "scorewarrior/units/unit.h"

#include <map>
#include <memory>
#include <set>

namespace scorewarrior::world {

/**
 * Игровая карта.
 */
class Map {
public:
  Map(int width, int height);
  /**
   * Поставить юнита в указанную клетку.
   * @param where положение клетки в которую будет поставлен юнит
   * @param unit юнит
   */
  void PlaceUnit(const Position& where, std::unique_ptr<units::Unit> unit);
  /**
   * Изъять юнит с идентификатором @param unit_id.
   * @param unit_id идентификатор юнита
   * @return изъятый юнит; если такого юнита нет на карте, вернётся nullptr
   */
  std::unique_ptr<units::Unit> ExtractUnit(int unit_id);

  /**
   * Позиция юнита на карте.
   * @param unit_id идентификатор юнита.
   * @return позиция юнита на карте
   */
  [[nodiscard]] const Position& PositionOfUnit(int unit_id) const;
  /**
   * Получить идентификаторы юнитов, стоящих в клетке @param  position
   * @param position искомое место
   * @return множество идентификаторов юнитов
   */
  [[nodiscard]] std::set<int> UnitsIdsInPlace(const Position& position) const;
  /**
   * Количество юнитов в клетке с позицией @param position
   * @param position искомое место
   * @return количество юнитов в клетке @param  position
   */
  [[nodiscard]] size_t NumerOfUnitsInPlace(const Position& position) const;
  /**
   * Есть ли юнит на карте
   * @param unit_id идентификатор искомого юнита
   * @return true если искомый юнит есть на карте и false иначе
   */
  [[nodiscard]] bool ContainsUnit(int unit_id) const;

  [[nodiscard]] int width() const { return width_; }
  [[nodiscard]] int height() const { return height_; }
private:
  /**
   * Проверяет, лежит ли координата @param position внутри карты.
   * @param position координата для проверки
   * @throw std::out_of_range В случае если координата @param position лежит вне карты
   */
  void ValidatePosition(const Position& position) const;

  /**
   * Проверяет, существует ли юнит с идентификатором @param unit_id на карте
   * @param unit_id идентификатор юнита
   * @throw std::out_of_range В случае если юнита нет на карте.
   */
  void EnsureUnitExists(int unit_id) const;


  int width_, height_;

  // Карта, ключом служит позиция клеток на карте, значение -- словарь
  // в котором ключи -- идентификаторы юнита, а значение -- юнит с этим идентификатором
  std::map<Position, std::map<int, std::unique_ptr<units::Unit>>> map_;
  // Словарь по которому можно быстро найти для юнита с заданным идентификатором его место
  std::map<int, Position> unit_place_;
};

} // namespace scorewarrior::world

#endif // SCOREWARRIOR_WORLD_MAP_H_
