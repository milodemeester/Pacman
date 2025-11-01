cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Forceer STATIC build voor dependencies die we binnenhalen (optioneel)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

include(FetchContent)

# OPTIONAL: bouw de grafische executable
option(BUILD_GAME_EXE "Build the graphical game executable (requires SFML)" OFF)

# --- Pacman logic library (geen SFML afhankelijkheden) ---
add_library(pacman_logic STATIC
        src/Stopwatch.cpp
        include/Stopwatch.h
        src/World.cpp
        include/World.h
        src/Entity.cpp
        include/Entity.h
        src/Score.cpp
        include/Score.h
        # Voeg hier enkel bestanden toe die puur game-logic bevatten (geen SFML)
)
# Als je warnings/treat-as-errors etc. wilt instellen kun je dat hier doen
# target_compile_options(pacman_logic PRIVATE ...)

# --- GoogleTest (voor unit tests) ---
# We willen tests kunnen bouwen zonder SFML.
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Tests executable — link alleen met pacman_logic en gtest
add_executable(pacman_tests
        tests/Game_test.cpp
        src/Score.cpp
        include/Score.h
)
target_link_libraries(pacman_tests PRIVATE pacman_logic GTest::gtest_main)

set(CTEST_OUTPUT_ON_FAILURE ON)
include(GoogleTest)
gtest_discover_tests(pacman_tests)

# --- SFML en grafische executable (optioneel) ---
if(BUILD_GAME_EXE)
    # Als je SFML statisch wil hebben: BUILD_SHARED_LIBS is al OFF hierboven.
    # Installeer op Linux de development packages (zie hieronder).
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 3.0.2
            GIT_SHALLOW ON
    )
    FetchContent_MakeAvailable(SFML)

    add_executable(pacman
            src/main.cpp
            src/Game.cpp
            include/Game.h
            src/Camera.cpp
            include/Camera.h
            src/State.cpp
            include/State.h
            src/StateManager.cpp
            include/StateManager.h
            src/Score.cpp
            include/Score.h
            src/MenuState.cpp
            include/MenuState.h
            src/PausedState.cpp
            include/PausedState.h
            src/StateFactory.cpp
            include/StateFactory.h
            src/LevelState.cpp
            include/LevelState.h
            src/VictoryState.cpp
            include/VictoryState.h
            # andere representation files die SFML gebruiken
    )
    target_link_libraries(pacman PRIVATE pacman_logic sfml-graphics sfml-window sfml-system)
    # Nodig wanneer SFML statisch gelinkt is
    target_compile_definitions(pacman PRIVATE SFML_STATIC)
endif()