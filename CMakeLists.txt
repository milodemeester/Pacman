cmake_minimum_required(VERSION 3.28)
project(Pacman LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/Game.cpp
        include/Game.h
        tests/Game_test.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

# ===================================================================
# TESTING FRAMEWORK (Google Test)
# ===================================================================

# Download en configureer Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Voeg de test-sectie toe, die alleen wordt uitgevoerd als dit het hoofdproject is.
# Dit voorkomt problemen als je project ooit als subproject wordt gebruikt.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Activeer de 'test' functionaliteit in CMake (voor ctest)
    enable_testing()

    # Voeg de 'tests' map toe aan de build
    add_subdirectory(tests)
endif()