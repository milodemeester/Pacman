cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

option(BUILD_GAME_EXE "Build the graphical game executable (requires SFML)" ON)

# --- Pacman logic library ---
add_library(pacman_logic STATIC
        Logic/src/CoinModel.cpp Logic/include/CoinModel.h
        Logic/src/Direction.cpp Logic/include/Direction.h
        Logic/src/Event.cpp Logic/include/Event.h
        Logic/src/FruitModel.cpp Logic/include/FruitModel.h
        Logic/src/GameFactory.cpp Logic/include/GameFactory.h
        Logic/src/GhostModel.cpp Logic/include/GhostModel.h
        Logic/src/Observer.cpp Logic/include/Observer.h
        Logic/src/PacmanModel.cpp Logic/include/PacmanModel.h
        Logic/src/Score.cpp Logic/include/Score.h
        Logic/src/Stopwatch.cpp Logic/include/Stopwatch.h
        Logic/src/Subject.cpp Logic/include/Subject.h
        Logic/src/WallModel.cpp Logic/include/WallModel.h
        Logic/src/World.cpp Logic/include/World.h
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
if (BUILD_GAME_EXE)
    find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)
    add_executable(pacman
            main.cpp
            Logic/src/CoinModel.cpp Logic/include/CoinModel.h
            Logic/src/Direction.cpp Logic/include/Direction.h
            Logic/src/Event.cpp Logic/include/Event.h
            Logic/src/FruitModel.cpp Logic/include/FruitModel.h
            Logic/src/GameFactory.cpp Logic/include/GameFactory.h
            Logic/src/GhostModel.cpp Logic/include/GhostModel.h
            Logic/src/Observer.cpp Logic/include/Observer.h
            Logic/src/PacmanModel.cpp Logic/include/PacmanModel.h
            Logic/src/Score.cpp Logic/include/Score.h
            Logic/src/Stopwatch.cpp Logic/include/Stopwatch.h
            Logic/src/Subject.cpp Logic/include/Subject.h
            Logic/src/WallModel.cpp Logic/include/WallModel.h
            Logic/src/World.cpp Logic/include/World.h

            Representation/src/Camera.cpp Representation/include/Camera.h
            Representation/src/CoinView.cpp Representation/include/CoinView.h
            Representation/src/EntityView.cpp Representation/include/EntityView.h
            Representation/src/FruitView.cpp Representation/include/FruitView.h
            Representation/src/Game.cpp Representation/include/Game.h
            Representation/src/GhostView.cpp Representation/include/GhostView.h
            Representation/src/LevelState.cpp Representation/include/LevelState.h
            Representation/src/MenuState.cpp Representation/include/MenuState.h
            Representation/src/PacmanView.cpp Representation/include/PacmanView.h
            Representation/src/PausedState.cpp Representation/include/PausedState.h
            Representation/src/SfmlFactory.cpp Representation/include/SfmlFactory.h
            Representation/src/State.cpp Representation/include/State.h
            Representation/src/StateManager.cpp Representation/include/StateManager.h
            Representation/src/VictoryState.cpp Representation/include/VictoryState.h
            Representation/src/WallView.cpp Representation/include/WallView.h

            Utilities/utils.cpp Utilities/utils.h
            Representation/src/SpriteMap.cpp
            Representation/include/SpriteMap.h
            Logic/src/Random.cpp
            Logic/include/Random.h
    )
    target_link_libraries(pacman PRIVATE pacman_logic sfml-graphics sfml-window sfml-system)
endif ()
