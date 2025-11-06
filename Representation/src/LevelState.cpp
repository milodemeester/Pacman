//
// Created by milo on 11/1/25.
//

#include "../include/LevelState.h"

#include "../include/EntityView.h"
#include "../include/PausedState.h"
#include "../include/SfmlFactory.h"
#include "../include/SpriteMap.h"
#include "../include/StateManager.h"
#include <SFML/Window/Event.hpp>

representation::LevelState::LevelState(StateManager& manager, sf::Vector2u windowSize)
    : State(manager), spriteMap_("../data/sprite.png"), factory(std::make_shared<SfmlFactory>(camera, windowSize, spriteMap_)), world(factory, 20, 11)
{
    views = std::move(factory->getCreatedViews());
    camera.set_world_size({20,11});
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
    representation::Camera cam;
    cam.set_world_size({float(world.get_width()), float(world.get_height())});
    render(window, cam);
}

void representation::LevelState::render(sf::RenderWindow& window, Camera& cam) {
    for (const auto& view : views) {
        view->draw(window, cam);
    }
}

void representation::LevelState::update(double delta_time) {
    world.update(delta_time);
    for (const auto& view : views) {
        view->update(delta_time);
    }
}
