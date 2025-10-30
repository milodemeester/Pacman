cmake_minimum_required(VERSION 3.26)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

# Forceer SFML STATIC build zodat er geen runtime-DLLs nodig zijn op Windows
# (zorg dat dit vóór FetchContent_MakeAvailable(SFML) staat)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# SFML via FetchContent - configureer als static om runtime DLL issues te vermijden
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Herstel BUILD_SHARED_LIBS naar default (indien je later shared wilt bouwen voor andere deps)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)

# GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(googletest)

# Main executable
add_executable(pacman
        src/main.cpp
        src/Game.cpp
        include/Game.h
)

target_include_directories(pacman PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman PRIVATE sfml-graphics sfml-window sfml-system)

# Als SFML static gebouwd is, definieer SFML_STATIC voor correcte symbolen/defines
target_compile_definitions(pacman PRIVATE SFML_STATIC)

enable_testing()

# Tests executable
add_executable(pacman_tests
        tests/Game_test.cpp
        src/Game.cpp
)
target_include_directories(pacman_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(pacman_tests PRIVATE GTest::gtest_main sfml-graphics sfml-window sfml-system)

# Definieer SFML_STATIC ook voor de tests target wanneer SFML statisch is
target_compile_definitions(pacman_tests PRIVATE SFML_STATIC)

# Zorg dat CTest toont wat er misgaat
set(CTEST_OUTPUT_ON_FAILURE ON)

include(GoogleTest)
gtest_discover_tests(pacman_tests)