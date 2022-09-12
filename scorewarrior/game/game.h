#ifndef SCOREWARRIOR_GAME_GAME_H_
#define SCOREWARRIOR_GAME_GAME_H_

#include "scorewarrior/command/executor.h"
#include "scorewarrior/command/factory.h"
#include "scorewarrior/command/stream.h"
#include "scorewarrior/game/unit_moving_history.h"
#include "scorewarrior/world/map.h"
#include "scorewarrior/world/ticker.h"
#include "scorewarrior/world/world.h"

namespace scorewarrior::game {
namespace command {

class March;
class Fight;

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

  std::unique_ptr<Command> MakeKillCommand(int unit_id);
  std::unique_ptr<Command> MakeFightCommand(int unit_id);
  std::unique_ptr<Command> MakeAfterFightCommand(command::Fight* fight);

  void OnMarchDone(command::March* march);
  void OnUnitKilled(int unit_id);

  void set_map(std::unique_ptr<Map> map) override { map_ = std::move(map); }
  std::unique_ptr<Map> take_map() override { return std::move(map_); }


  std::unique_ptr<Map> map_;
  UnitMovingHistory moving_history_;
  Executor executor_;
  world::Ticker ticker_;

  std::unordered_map<int, size_t> number_of_fights_;
};

} // namespace scorewarrior::game

#endif // SCOREWARRIOR_GAME_GAME_H_
