cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

option(BUILD_GAME_EXE "Build the graphical game executable (requires SFML)" ON)

# --- Pacman logic library ---
add_library(pacman_logic STATIC
        Logic/src/Ghost.cpp Logic/include/Ghost.h
        Logic/src/Pacman.cpp Logic/include/Pacman.h
        Logic/src/Score.cpp  Logic/include/Score.h
        Logic/src/Stopwatch.cpp Logic/include/Stopwatch.h
        Logic/src/World.cpp Logic/include/World.h
        Logic/src/GameFactory.cpp
        Logic/include/GameFactory.h
        Logic/src/Observer.cpp
        Logic/include/Observer.h
        Logic/src/Fruit.cpp
        Logic/include/Fruit.h
)

# --- Tests ---
find_package(GTest REQUIRED)

enable_testing()

add_executable(pacman_tests
        tests/Game_test.cpp)
target_link_libraries(pacman_tests PRIVATE pacman_logic GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(pacman_tests)

# --- SFML Game executable ---
if(BUILD_GAME_EXE)
    find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
    add_executable(pacman
            main.cpp
            Logic/src/Ghost.cpp Logic/include/Ghost.h
            Logic/src/Pacman.cpp Logic/include/Pacman.h
            Logic/src/Score.cpp Logic/include/Score.h
            Logic/src/Stopwatch.cpp Logic/include/Stopwatch.h
            Logic/src/World.cpp Logic/include/World.h
            Representation/src/Camera.cpp Representation/include/Camera.h
            Logic/src/Entity.cpp Logic/include/Entity.h
            Representation/src/Game.cpp Representation/include/Game.h
            Representation/src/LevelState.cpp Representation/include/LevelState.h
            Representation/src/MenuState.cpp Representation/include/MenuState.h
            Representation/src/PausedState.cpp Representation/include/PausedState.h
            Representation/src/State.cpp Representation/include/State.h
            Representation/src/StateManager.cpp Representation/include/StateManager.h
            Representation/src/VictoryState.cpp Representation/include/VictoryState.h
            Utilities/utils.cpp
            Utilities/utils.h
            Logic/src/GameFactory.cpp
            Logic/include/GameFactory.h
            Logic/src/Wall.cpp
            Logic/include/Wall.h
            Logic/src/Observer.cpp
            Logic/include/Observer.h
            Representation/src/SfmlFactory.cpp
            Representation/include/SfmlFactory.h
            Logic/src/Coin.cpp
            Logic/include/Coin.h
            Logic/src/Fruit.cpp
            Logic/include/Fruit.h

    )
    target_link_libraries(pacman PRIVATE pacman_logic sfml-graphics sfml-window sfml-system)
endif()
