# Maak de executable voor onze tests
add_executable(pacman_tests
        Game_test.cpp
        # VOEG HIER DE IMPLEMENTATIE VAN DE GAME KLASSE TOE
        # We gebruiken ${CMAKE_SOURCE_DIR} om naar de root van het project te verwijzen.
        ${CMAKE_SOURCE_DIR}/src/Game.cpp
)

# Link de test-executable met je eigen game code en de Google Test library
target_link_libraries(pacman_tests PRIVATE
        ${PROJECT_NAME}
        GTest::gtest_main
)

# Neem hier GoogleTest op en ontdek de tests
include(GoogleTest)
gtest_discover_tests(pacman_tests)