# Maak de executable voor onze tests
add_executable(pacman_tests
        Game_test.cpp
)

# Link de test-executable met je eigen game code en de Google Test library
target_link_libraries(pacman_tests PRIVATE
        ${PROJECT_NAME}
        GTest::gtest_main
)

# NEEM HIER GOOGLETEST OP EN ONTDEK DE TESTS
include(GoogleTest)
gtest_discover_tests(pacman_tests)