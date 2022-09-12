#ifndef SCOREWARRIOR_GAME_COMMAND_CREATE_MAP_H_
#define SCOREWARRIOR_GAME_COMMAND_CREATE_MAP_H_

#include "scorewarrior/command/command.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

class CreateMap : public scorewarrior::command::Command {
public:
  CreateMap(int width, int height, world::World* world);

  void OnDone(const std::function<void(CreateMap*)>& on_done);

  [[nodiscard]] int width() const { return width_; }
  [[nodiscard]] int height() const { return height_; }
private:
  bool Execute(uint32_t current_time) override;

  const int width_, height_;
  world::World* world_;
};

} // namespace scorewarrior::game::command

#endif // SCOREWARRIOR_GAME_COMMAND_CREATE_MAP_H_
