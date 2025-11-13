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
#include "../include/PacmanView.h"
#include "../include/GhostView.h"

representation::LevelState::LevelState(StateManager& manager, sf::Vector2u windowSize)
    : State(manager), spriteMap_("../data/sprite.png"), factory(std::make_shared<SfmlFactory>(camera, windowSize, spriteMap_)), world(factory)
{
    views = std::move(factory->getCreatedViews());
    camera.set_world_size({20,11});
}

void representation::LevelState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        render(window);
    }
    else if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        if (key == sf::Keyboard::Up) {
            world.move_pacman(logic::Direction::North);
        }
        else if (key == sf::Keyboard::Down)  {
            world.move_pacman(logic::Direction::South);
        }
        else if (key == sf::Keyboard::Right) {
            world.move_pacman(logic::Direction::East);
        }
        else if (key == sf::Keyboard::Left) {
            world.move_pacman(logic::Direction::West);
        }
        else if (key == sf::Keyboard::Escape) {
            std::unique_ptr<PausedState> paused = std::make_unique<PausedState>(manager_, window.getSize());
            manager_.push_state(std::move(paused));
        }
    }
}

void representation::LevelState::update(double delta_time) {
    world.update(delta_time);
    for (const auto& view : views) {
        view->update(delta_time);
    }
}


void representation::LevelState::render(sf::RenderWindow& window) {
    representation::Camera cam;
    cam.set_world_size({float(world.get_width()), float(world.get_height())});
    render(window, cam);
}

void representation::LevelState::render(sf::RenderWindow& window, Camera& cam) {
    PacmanView* pacman;
    std::vector<GhostView*> ghosts;

    for (auto& view : views) {
        if (dynamic_cast<representation::PacmanView*>(view.get())) {
            pacman = dynamic_cast<representation::PacmanView*>(view.get());
        }
        else if (dynamic_cast<GhostView*>(view.get())) {
            ghosts.push_back(dynamic_cast<GhostView*>(view.get()));
        }
        else {
            view->draw(window, cam);
        }
    }
    for (auto& ghost : ghosts) {
        ghost->draw(window, cam);
    }
    pacman->draw(window, cam);
}