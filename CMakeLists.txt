cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

# Forceer STATIC build voor dependencies die we binnenhalen
# 1) SFML static -> geen runtime DLL-gedoe voor de app
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# SFML via FetchContent
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# 2) GoogleTest static -> geen gtest*.dll nodig voor pacman_tests
# (Laat BUILD_SHARED_LIBS hier nog steeds OFF)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(googletest)

# Als je nadien toch shared libs voor andere zaken wilt bouwen, kun je dit terug ON zetten:
# set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# Main executable
add_executable(pacman
        src/main.cpp
        src/Game.cpp
        include/Game.h
)
target_include_directories(pacman PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman PRIVATE sfml-graphics sfml-window sfml-system)
# Nodig wanneer SFML statisch gelinkt is
target_compile_definitions(pacman PRIVATE SFML_STATIC)

enable_testing()

# Tests executable (zonder SFML en zonder Game.cpp)
add_executable(pacman_tests
        tests/Game_test.cpp
)
target_include_directories(pacman_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman_tests PRIVATE GTest::gtest_main)

# Zorg dat CTest toont wat er misgaat
set(CTEST_OUTPUT_ON_FAILURE ON)

include(GoogleTest)
gtest_discover_tests(pacman_tests)