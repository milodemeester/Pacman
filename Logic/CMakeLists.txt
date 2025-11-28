cmake_minimum_required(VERSION 3.28.3)
project(PacmanLogic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- Pacman logic library ---
add_library(pacman_logic STATIC
        src/CoinModel.cpp include/CoinModel.h
        src/Direction.cpp include/Direction.h
        src/Event.cpp include/Event.h
        src/FruitModel.cpp include/FruitModel.h
        src/GameFactory.cpp include/GameFactory.h
        src/GhostModel.cpp include/GhostModel.h
        src/Observer.cpp include/Observer.h
        src/PacmanModel.cpp include/PacmanModel.h
        src/Score.cpp include/Score.h
        src/Stopwatch.cpp include/Stopwatch.h
        src/Subject.cpp include/Subject.h
        src/WallModel.cpp include/WallModel.h
        src/World.cpp include/World.h
        src/InkyModel.cpp include/InkyModel.h
        src/Random.cpp include/Random.h
        src/PinkyModel.cpp include/PinkyModel.h
        src/Type2Ghost.cpp include/Type2Ghost.h
        src/BlinkyModel.cpp include/BlinkyModel.h
        src/ClydeModel.cpp include/ClydeModel.h
        src/CollectableSubject.cpp include/CollectableSubject.h
)

# Public so the main library can find it
target_include_directories(pacman_logic PUBLIC include)