#ifndef SCOREWARRIOR_WORLD_TICKER_H_
#define SCOREWARRIOR_WORLD_TICKER_H_

#include <cstdint>

namespace scorewarrior::world {

class Ticker {
public:
  Ticker();

  Ticker& operator +=(uint32_t time);
  [[nodiscard]] uint32_t current_time() const { return time_; }
private:
  uint32_t time_;
};

} // namespace scorewarrior::world

#endif // SCOREWARRIOR_WORLD_TICKER_H_
