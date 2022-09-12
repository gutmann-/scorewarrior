#ifndef SCOREWARRIOR_WORLD_POSITION_H_
#define SCOREWARRIOR_WORLD_POSITION_H_

namespace scorewarrior::world {

class Position final {
public:
  Position() : Position(0, 0) {}
  Position(int x, int y) : x_(x), y_(y) {}
  Position(const Position& from) = default;

  [[nodiscard]] int x() const { return x_; }
  [[nodiscard]] int y() const { return y_; }

  Position& operator =(const Position& other) = default;
  bool operator <(const Position& other) const {
    return x() < other.x() || (x() == other.x() && y() < other.y());
  }
private:
  int x_, y_;
};

} // namespace scorewarrior::world

#endif // SCOREWARRIOR_WORLD_POSITION_H_
