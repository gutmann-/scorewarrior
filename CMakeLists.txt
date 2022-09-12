cmake_minimum_required(VERSION 3.0)
project(scorewarrior)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

add_executable(scorewarrior
        main.cpp
        scorewarrior/units/unit.h
        scorewarrior/units/warrior.cpp
        scorewarrior/units/warrior.h
        scorewarrior/units/unit.cpp
        scorewarrior/world/position.h
        scorewarrior/world/map.h
        scorewarrior/world/map.cpp
        scorewarrior/command/command.h
        scorewarrior/command/unit_command.h
        scorewarrior/command/stream.h
        scorewarrior/game/command/wait.h
        scorewarrior/game/command/wait.cpp
        scorewarrior/game/command/march.h
        scorewarrior/game/command/march.cpp
        scorewarrior/game/command/spawn.h
        scorewarrior/game/command/spawn.cpp
        scorewarrior/game/command/create_map.h
        scorewarrior/game/command/create_map.cpp
        scorewarrior/game/game.h
        scorewarrior/game/game.cpp
        scorewarrior/command/executor.h
        scorewarrior/command/executor.cpp
        scorewarrior/command/factory.h
        scorewarrior/game/command/finish.h
        scorewarrior/game/command/finish.cpp
        scorewarrior/world/world.h
        scorewarrior/command/command.cpp
        scorewarrior/world/ticker.h
        scorewarrior/world/ticker.cpp
        scorewarrior/units/two_units_dispatcher.h
        scorewarrior/utils/hash_pair.h
        scorewarrior/units/two_units_dispatcher.cpp
        scorewarrior/game/command/fight.h
        scorewarrior/game/command/fight.cpp
        scorewarrior/parser/command_file.h
        scorewarrior/parser/command_file.cpp)
target_include_directories(scorewarrior PRIVATE ${CMAKE_SOURCE_DIR})
