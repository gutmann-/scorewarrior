#include "scorewarrior/game/game.h"

#include "scorewarrior/game/command/create_map.h"
#include "scorewarrior/game/command/fight.h"
#include "scorewarrior/game/command/finish.h"
#include "scorewarrior/game/command/march.h"
#include "scorewarrior/game/command/spawn.h"
#include "scorewarrior/game/command/wait.h"

#include <iostream>

namespace scorewarrior::game {

namespace {

auto MakeLogMarchStr(command::March* march) {
  const auto& position = march->to_position();
  const char* event = !march->is_done() ? "STARTED" : "FINISHED";

  return std::string("MARCH ") + event +
      " " + std::to_string(march->unit_id()) +
      " TO" +
      " " + std::to_string(position.x()) +
      " " + std::to_string(position.y());
}

} // namespace

using Command = Game::Command;

void Game::LoadCommands(std::unique_ptr<CommandStream> stream) {
  stream->UseFactory(this);

  while (!stream->eof()) {
    auto command = stream->Pull();
    if (command)
      executor_.PushCommand(std::move(command));
  }
}

void Game::Run() {
  while (!executor_.all_is_done())
    executor_(ticker_.current_time());
}

void Game::LogCommand(const std::string& str) {
  std::cout << "[" << ticker_.current_time() << "] " << str << std::endl;
}

std::unique_ptr<Command> Game::MakeCreateMapCommand(int width, int height) {
  world::World* world = this;
  auto create_map = std::make_unique<command::CreateMap>(width, height, world);

  create_map->OnDone([this](command::CreateMap* create_map) {
    const auto log_str = std::string("MAP CREATED") +
                                " " + std::to_string(create_map->width()) +
                                " " + std::to_string(create_map->height());

    LogCommand(log_str);
  });

  return create_map;
}

std::unique_ptr<Command> Game::MakeSpawnCommand(int unit_id, int x, int y, int strength) {
  const auto position = world::Position(x, y);
  world::World* world = this;

  auto make_warrior = [unit_id, strength]() -> std::unique_ptr<units::Unit> {
    return std::make_unique<units::Warrior>(unit_id, strength);
  };
  auto spawn =
      std::make_unique<command::Spawn>(make_warrior, position, world);

  spawn->OnDone([this](command::Spawn* spawn) {
    const auto log_str = std::string("WARRIOR SPAWNED") +
        " " + std::to_string(spawn->unit_id()) +
        " ON" +
        " " + std::to_string(spawn->where().x()) +
        " " + std::to_string(spawn->where().y());

    LogCommand(log_str);
  });

  return spawn;
}

std::unique_ptr<Command> Game::MakeMarchCommand(int unit_id, int x, int y) {
  const auto position = world::Position(x, y);
  world::World* world = this;

  auto march = std::make_unique<command::March>(unit_id, position, world);
  march->OnBegin([this](command::March* march){
    const auto log_str = MakeLogMarchStr(march);
    LogCommand(log_str);
  });

  march->OnDone([this](command::March* march) { OnMarchDone(march); });
  return march;
}

std::unique_ptr<Command> Game::MakeWaitCommand(int ticks) {
  return std::make_unique<command::Wait>(ticks, &executor_, &ticker_);
}

std::unique_ptr<Command> Game::MakeFinishCommand() {
  auto finish = std::make_unique<command::Finish>(&executor_);
  finish->OnDone([this](Command*) { LogCommand("FINISH"); });
  return finish;
}

void Game::OnMarchDone(command::March* march) {
  const auto log_str = MakeLogMarchStr(march);
  LogCommand(log_str);

  const auto unit_id = march->unit_id();

  auto unit_position = map_->PositionOfUnit(unit_id);
  if (map_->NumerOfUnitsInPlace(unit_position) > 1) {
    world::World* world = this;

    auto fight = std::make_unique<command::Fight>(unit_id, world);
    fight->OnDone([this](command::Fight* fight) {
      const auto winner_id = fight->winner_id();
      const auto log_str = std::string("FIGHT") +
          " " + std::to_string(fight->unit_id()) +
          " " + std::to_string(fight->enemy_id()) +
          " " + (winner_id == units::Unit::NOT_INITIALIZED_ID ? "ALL DEAD" :
                 "WINNER IS " + std::to_string(winner_id));
      LogCommand(log_str);
    });

    march->Then(std::move(fight));
  }
}

} // namespace scorewarrior::game