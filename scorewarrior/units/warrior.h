#ifndef SCOREWARRIOR_UNITS_WARRIOR_H_
#define SCOREWARRIOR_UNITS_WARRIOR_H_

#include "scorewarrior/units/unit.h"

namespace scorewarrior::units {

class Warrior : public Unit {
public:
  Warrior(int id, int strength);

  [[nodiscard]] int strength() const { return strength_; }
  [[nodiscard]] std::type_index type_index() const override { return typeid(*this); }
private:
  const int strength_;
};

} // namespace scorewarrior

#endif // SCOREWARRIOR_UNITS_WARRIOR_H_
