#include "scorewarrior/units/warrior.h"

namespace scorewarrior::units {

Warrior::Warrior(int id, int strength)
       : Unit(id),
         strength_(strength) {}

} // namespace scorewarrior::units