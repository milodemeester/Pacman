cmake_minimum_required(VERSION 3.20)
project(Pacman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- MANUEL GTEST CONFIGURATION ---
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest/include)

# Vertel de linker waar de gecompileerde gtest libraries (.a of .lib) te vinden zijn.
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest/lib)

# --- SFML CONFIG ---
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# --- HOOFDAPPLICATIE ---
add_executable(Pacman
        src/main.cpp
        src/Game.cpp
)

# Link de Pacman game met de SFML libraries.
target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system)

# Zorg ervoor dat de compiler je eigen 'include' map kan vinden.
target_include_directories(Pacman PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- TESTAPPLICATION ---
# Activeer de testfunctionaliteit in CMake.
enable_testing()

# Definieer een aparte executable voor je tests.
add_executable(pacman_tests
        tests/Game_test.cpp
        # We hebben de implementatie van de Game klasse nodig om te kunnen testen.
        src/Game.cpp
)

# Link de test-executable met de gtest libraries.
# De namen 'gtest' en 'gtest_main' moeten overeenkomen met de bestandsnamen in gtest/lib
# (bijv. libgtest.a en libgtest_main.a).
target_link_libraries(pacman_tests PRIVATE gtest gtest_main)

# Zorg ervoor dat de compiler je eigen 'include' map kan vinden.
target_include_directories(pacman_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Vertel ctest dat 'pacman_tests' een test-executable is.
include(GoogleTest)
gtest_discover_tests(pacman_tests)
# -----------------------------