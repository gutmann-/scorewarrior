#ifndef SCOREWARRIOR_UNITS_TWO_UNITS_DISPATCHER_H_
#define SCOREWARRIOR_UNITS_TWO_UNITS_DISPATCHER_H_

#include "scorewarrior/units/unit.h"

#include "scorewarrior/utils/hash_pair.h"

#include <functional>

namespace scorewarrior::units {

/**
 * Простейший диспетчек коллизий между двумя юнитами разных типов.
 */
class TwoUnitsDispatcher {
public:
  using Handler = std::function<void(Unit*, Unit*)>;

  /**
   * Регистрирует обработчик @param handler, обрабатывающий коллизию двух юнитов.
   * @tparam UnitType1 Тип первого юнита.
   * @tparam UnitType2 Тип второго юнита.
   * @param handler обработчик
   */
  template<class UnitType1, class UnitType2>
  void RegisterHandler(const std::function<void(UnitType1*, UnitType2*)>& handler) {
    auto k = std::pair<std::type_index, std::type_index>(typeid(UnitType1),
                                                         typeid(UnitType2));
    auto wrapper = [handler](Unit* a, Unit* b) {
      auto p1 = static_cast<UnitType1*>(a);
      auto p2 = static_cast<UnitType2*>(b);

      handler(p1, p2);
    };

    handlers_[k] = wrapper;
  }

  /**
   * Обработать коллизию двух юнитов.
   * @param a первый юнит
   * @param b второй юнит
   */
  void Handle(Unit* a, Unit* b) const;
private:
  using UnorderedMap =
  std::unordered_map
  <
    std::pair<std::type_index, std::type_index>, // пара истинных типов
    Handler, // обработчик для пары этих типов
    utils::HashPair
  >;


  UnorderedMap handlers_;
};

} // namespace scorewarrior::units

#endif // SCOREWARRIOR_UNITS_TWO_UNITS_DISPATCHER_H_
