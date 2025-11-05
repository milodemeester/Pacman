//
// Created by milod on 29/10/2025.
//

#include <gtest/gtest.h>

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
    // Voor nu, een simpele assertion die altijd slaagt.
    ASSERT_TRUE(true);
}

// Een simpele test zonder Fixture.
// Gebruik TEST als je geen setup/teardown per test nodig hebt.
TEST(ExampleTest, BasicAssertion) { EXPECT_EQ(2 + 2, 4); }