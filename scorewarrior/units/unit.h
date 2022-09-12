#ifndef SCOREWARRIOR_UNITS_UNIT_H_
#define SCOREWARRIOR_UNITS_UNIT_H_

#include <typeindex>
#include <cinttypes>

namespace scorewarrior::units {

/**
 * Базовый класс для игровых юнитов.
 */
class Unit {
public:
  enum : int {
    NOT_INITIALIZED_ID = -1, // не инициализиованный id
  };

  /**
   * Создаёт юнит с идентификатором @param id
   * @param id идентификатор юнита
   */
  explicit Unit(int id = NOT_INITIALIZED_ID);
  virtual ~Unit() = default;

  /**
   * Идентификатор юнита.
   * @return идентификатор юнита.
   */
  [[nodiscard]] int id() const { return id_; }
  /**
   * Истинныый тип юнита.
   * @return истинный тип юнита.
   */
  [[nodiscard]] virtual std::type_index type_index() const = 0;
private:
  const int id_;
};

} // namespace scorewarrior

#endif // SCOREWARRIOR_UNITS_UNIT_H_
