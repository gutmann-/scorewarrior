#include "scorewarrior/units/two_units_dispatcher.h"

#include <stdexcept>

namespace scorewarrior::units {

void TwoUnitsDispatcher::Handle(Unit* a, Unit* b) const {
  auto k = std::make_pair(a->type_index(), b->type_index());

  auto handler_iterator = handlers_.find(k);
  if (handler_iterator != handlers_.end()) {
    auto handler = handler_iterator->second;
    handler(a, b);
  } else {
    const auto& [a_type, b_type] = k;
    const auto err_str = std::string("Can't find handler for unit type \"")
        + a_type.name() + "\""
        + " and unit type \"" + b_type.name() + "\"";
    throw std::out_of_range(err_str);
  }
}

} // namespace scorewarrior::units