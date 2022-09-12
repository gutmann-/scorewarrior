#include "scorewarrior/game/command/create_map.h"

#include "scorewarrior/world/world.h"

namespace scorewarrior::game::command {

CreateMap::CreateMap(int width, int height, world::World* world)
         : Command(),
           width_(width),
           height_(height),
           world_(world) {}

void CreateMap::OnDone(const std::function<void(CreateMap*)>& on_done) {
  if (on_done)
    Command::OnDone([this, on_done](Command*){ on_done(this); });
}

bool CreateMap::Execute(uint32_t current_time) {
  world_->set_map(std::make_unique<world::Map>(width_, height_));
  return true;
}

} // namespace scorewarrior::game::command
