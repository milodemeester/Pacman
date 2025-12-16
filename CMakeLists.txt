cmake_minimum_required(VERSION 3.28.3)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Add the Logic subdirectory
add_subdirectory(Logic)

# --- SFML Game executable ---
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_executable(pacman
        main.cpp
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
        Representation/src/SpriteMap.cpp Representation/include/SpriteMap.h

        Logic/Utilities/utils.cpp Logic/Utilities/utils.h
)

# Link the logic library
target_link_libraries(pacman PRIVATE pacman_logic sfml-graphics sfml-window sfml-system)