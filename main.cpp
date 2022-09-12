#include <fstream>

#include "scorewarrior/game/game.h"
#include "scorewarrior/parser/command_file.h"



int main(int argc, char* argv[]) {
  if (argc == 2) {
    char* file_path = argv[1];

    auto file = std::make_unique<std::ifstream>(file_path);
    auto stream = std::make_unique<scorewarrior::parser::CommandFile>(std::move(file));

    scorewarrior::game::Game game;
    game.LoadCommands(std::move(stream));
    game.Run();

    return 0;
  } else {
    return 1;
  }
}
