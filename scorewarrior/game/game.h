#ifndef SCOREWARRIOR_GAME_GAME_H_
#define SCOREWARRIOR_GAME_GAME_H_

#include "scorewarrior/command/executor.h"
#include "scorewarrior/command/factory.h"
#include "scorewarrior/command/stream.h"
#include "scorewarrior/world/map.h"
#include "scorewarrior/world/ticker.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game {
namespace command {

class March;

} // namespace command

class Game : private scorewarrior::command::Factory,
             private scorewarrior::world::World {
public:
  using Command = scorewarrior::command::Command;
  using CommandStream = scorewarrior::command::Stream;
  using Executor = scorewarrior::command::Executor;
  using Map = world::Map;

  Game() = default;

  void LoadCommands(std::unique_ptr<CommandStream> stream);
  void Run();
private:
  void LogCommand(const std::string& str);

  std::unique_ptr<Command> MakeCreateMapCommand(int width, int height) override;
  std::unique_ptr<Command> MakeSpawnCommand(int unit_id, int x, int y, int strength) override;
  std::unique_ptr<Command> MakeMarchCommand(int unit_id, int x, int y) override;
  std::unique_ptr<Command> MakeWaitCommand(int ticks) override;
  std::unique_ptr<Command> MakeFinishCommand() override;

  void OnMarchDone(command::March* march);

  void set_map(std::unique_ptr<Map> map) override { map_ = std::move(map); }
  std::unique_ptr<Map> take_map() override { return std::move(map_); }


  std::unique_ptr<Map> map_;
  Executor executor_;
  world::Ticker ticker_;
};

} // namespace scorewarrior::game

#endif // SCOREWARRIOR_GAME_GAME_H_
