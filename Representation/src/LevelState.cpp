//
// Created by milo on 11/1/25.
//

#include "../include/LevelState.h"
#include "../include/PausedState.h"
#include "../include/SfmlFactory.h"
#include <SFML/Window/Event.hpp>
#include "../include/StateManager.h"
#include "../include/EntityView.h"

representation::LevelState::LevelState(StateManager& manager, sf::Vector2u windowSize)
    : State(manager), factory(std::make_shared<SfmlFactory>(camera, windowSize)), world(factory, 20, 11)
{
    views = std::move(factory->getCreatedViews());

}

void representation::LevelState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        auto key = event.key;
        if (key.code == sf::Keyboard::Key::Escape) {
            std::unique_ptr<PausedState> paused = std::make_unique<PausedState>(manager_, window.getSize());
            manager_.push_state(std::move(paused));
        }
    }
}

void representation::LevelState::render(sf::RenderWindow& window) {
}

void representation::LevelState::update(double delta_time) {
    world.update(delta_time);
}
