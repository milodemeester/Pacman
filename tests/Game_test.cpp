//
// Created by milod on 29/10/2025.
//

#include <gtest/gtest.h>
#include "../include/Game.h" // Inclusief je eigen Game header

// Een 'Test Fixture' om een Game object klaar te zetten voor elke test
class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code die voor elke test wordt uitgevoerd
        // game = new Game(); // Bijvoorbeeld
    }

    void TearDown() override {
        // Code die na elke test wordt uitgevoerd
        // delete game;
    }

    // Game* game; // Je kunt hier objecten declareren
};

// Een voorbeeldtest die controleert of een Game object correct wordt aangemaakt.
// Gebruik TEST_F als je de Fixture (GameTest) wilt gebruiken.
TEST_F(GameTest, CanBeCreated) {
    Game myGame; // Maak een instance van je Game klasse
    // Voeg hier een simpele check toe. Dit is een placeholder.
    // Bijvoorbeeld, als je een 'getScore()' methode hebt die met 0 begint:
    // EXPECT_EQ(myGame.getScore(), 0);

    // Voor nu, een simpele assertion die altijd slaagt.
    ASSERT_TRUE(true);
}

// Een simpele test zonder Fixture.
// Gebruik TEST als je geen setup/teardown per test nodig hebt.
TEST(ExampleTest, BasicAssertion) {
    EXPECT_EQ(2 + 2, 4);
}