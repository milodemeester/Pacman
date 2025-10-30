cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

# SFML via FetchContent - configureer als shared om minder define-issues te hebben
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# GoogleTest
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(googletest)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)


# Main executable
add_executable(pacman
        src/main.cpp
        src/Game.cpp
        include/Game.h
)

target_include_directories(pacman PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman PRIVATE sfml-graphics sfml-window sfml-system)

enable_testing()

# Tests executable
add_executable(pacman_tests
        tests/Game_test.cpp
        src/Game.cpp
)
target_include_directories(pacman_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman_tests PRIVATE GTest::gtest_main sfml-graphics sfml-window sfml-system)

# Zorg dat CTest toont wat er misgaat
set(CTEST_OUTPUT_ON_FAILURE ON)

include(GoogleTest)
gtest_discover_tests(pacman_tests)
