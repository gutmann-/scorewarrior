#ifndef SCOREWARRIOR_WORLD_WORLD_H_
#define SCOREWARRIOR_WORLD_WORLD_H_

#include "scorewarrior/world/map.h"

namespace scorewarrior::world {

/**
 * Игровой мир.
 */
class World {
public:
  virtual ~World() = default;

  /**
   * Задать карту для мира.
   * @param map
   */
  virtual void set_map(std::unique_ptr<Map> map) = 0;
  /**
   * Изъять карту из мира.
   * @return
   */
  virtual std::unique_ptr<Map> take_map() = 0;
};

}

#endif // SCOREWARRIOR_WORLD_WORLD_H_
