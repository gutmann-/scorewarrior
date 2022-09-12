#include "scorewarrior/world/ticker.h"

namespace scorewarrior::world {

Ticker::Ticker()
      : time_(0) {}

Ticker& Ticker::operator +=(uint32_t time) {
  time_ += time;
  return *this;
}

} // namespace scorewarrior::world