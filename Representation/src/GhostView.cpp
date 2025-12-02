//
// Created by milo on 11/5/25.
//

#include "../include/GhostView.h"
#include "../../Logic/include/GhostModel.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

representation::GhostView::GhostView(std::shared_ptr<logic::GhostModel>& model, SpriteMap& sprite_map,
                                     logic::GhostType type) {
    model->addObserver(this);
    world_direction = model->get_direction();
    world_pos_ = model->get_position();
    // ----------- sprites -----------
    sf::Sprite FEAR_MODE_1 = sprite_map.getSprite(sf::IntRect(1, 554, 33, 33));
    sf::Sprite FEAR_MODE_2 = sprite_map.getSprite(sf::IntRect(1, 604, 33, 33));
    std::vector<sf::Sprite> NoDir{FEAR_MODE_1, FEAR_MODE_2};
    animation_sequences[logic::Direction::NoDirection] = NoDir;

    if (type == logic::GhostType::Blinky) {
        // ----------- blinky -----------
        sf::Sprite BLINKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(1, 4, 33, 33));
        sf::Sprite BLINKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(1, 54, 33, 33));
        sf::Sprite BLINKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(1, 204, 33, 33));
        sf::Sprite BLINKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(1, 254, 33, 33));
        sf::Sprite BLINKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(1, 104, 33, 33));
        sf::Sprite BLINKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(1, 154, 33, 33));
        sf::Sprite BLINKY_UP_1 = sprite_map.getSprite(sf::IntRect(1, 304, 33, 33));
        sf::Sprite BLINKY_UP_2 = sprite_map.getSprite(sf::IntRect(1, 354, 33, 33));

        std::vector<sf::Sprite> east{BLINKY_RIGHT_1, BLINKY_RIGHT_2};
        std::vector<sf::Sprite> west{BLINKY_LEFT_1, BLINKY_LEFT_2};
        std::vector<sf::Sprite> south{BLINKY_DOWN_1, BLINKY_DOWN_2};
        std::vector<sf::Sprite> north{BLINKY_UP_1, BLINKY_UP_2};

        animation_sequences[logic::Direction::East] = east;
        animation_sequences[logic::Direction::North] = north;
        animation_sequences[logic::Direction::West] = west;
        animation_sequences[logic::Direction::South] = south;
    }

    else if (type == logic::GhostType::Inky) {
        // ----------- inky -----------
        sf::Sprite INKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(101, 4, 35, 35));
        sf::Sprite INKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(101, 54, 35, 35));
        sf::Sprite INKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(101, 204, 35, 35));
        sf::Sprite INKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(101, 254, 35, 35));
        sf::Sprite INKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(101, 104, 35, 35));
        sf::Sprite INKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(101, 154, 35, 35));
        sf::Sprite INKY_UP_1 = sprite_map.getSprite(sf::IntRect(101, 304, 35, 35));
        sf::Sprite INKY_UP_2 = sprite_map.getSprite(sf::IntRect(101, 354, 35, 35));

        std::vector<sf::Sprite> east{INKY_RIGHT_1, INKY_RIGHT_2};
        std::vector<sf::Sprite> west{INKY_LEFT_1, INKY_LEFT_2};
        std::vector<sf::Sprite> south{INKY_DOWN_1, INKY_DOWN_2};
        std::vector<sf::Sprite> north{INKY_UP_1, INKY_UP_2};

        animation_sequences[logic::Direction::East] = east;
        animation_sequences[logic::Direction::North] = north;
        animation_sequences[logic::Direction::West] = west;
        animation_sequences[logic::Direction::South] = south;
    }

    else if (type == logic::GhostType::Pinky) {
        // ----------- pinky -----------
        sf::Sprite PINKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(51, 4, 35, 35));
        sf::Sprite PINKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(51, 54, 35, 35));
        sf::Sprite PINKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(51, 104, 35, 35));
        sf::Sprite PINKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(51, 154, 35, 35));
        sf::Sprite PINKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(51, 204, 35, 35));
        sf::Sprite PINKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(51, 254, 35, 35));
        sf::Sprite PINKY_UP_1 = sprite_map.getSprite(sf::IntRect(51, 304, 35, 35));
        sf::Sprite PINKY_UP_2 = sprite_map.getSprite(sf::IntRect(51, 354, 35, 35));

        std::vector<sf::Sprite> east{PINKY_RIGHT_1, PINKY_RIGHT_2};
        std::vector<sf::Sprite> west{PINKY_LEFT_1, PINKY_LEFT_2};
        std::vector<sf::Sprite> south{PINKY_DOWN_1, PINKY_DOWN_2};
        std::vector<sf::Sprite> north{PINKY_UP_1, PINKY_UP_2};

        animation_sequences[logic::Direction::East] = east;
        animation_sequences[logic::Direction::North] = north;
        animation_sequences[logic::Direction::West] = west;
        animation_sequences[logic::Direction::South] = south;
    }

    else if (type == logic::GhostType::Clyde) {
        // ----------- clyde -----------
        sf::Sprite CLYDED_RIGHT_1 = sprite_map.getSprite(sf::IntRect(151, 4, 35, 35));
        sf::Sprite CLYDED_RIGHT_2 = sprite_map.getSprite(sf::IntRect(151, 54, 35, 35));
        sf::Sprite CLYDED_LEFT_1 = sprite_map.getSprite(sf::IntRect(151, 204, 35, 35));
        sf::Sprite CLYDED_LEFT_2 = sprite_map.getSprite(sf::IntRect(151, 254, 35, 35));
        sf::Sprite CLYDED_DOWN_1 = sprite_map.getSprite(sf::IntRect(151, 104, 35, 35));
        sf::Sprite CLYDED_DOWN_2 = sprite_map.getSprite(sf::IntRect(151, 154, 35, 35));
        sf::Sprite CLYDED_UP_1 = sprite_map.getSprite(sf::IntRect(151, 304, 35, 35));
        sf::Sprite CLYDED_UP_2 = sprite_map.getSprite(sf::IntRect(151, 354, 35, 35));

        std::vector<sf::Sprite> east{CLYDED_RIGHT_1, CLYDED_RIGHT_2};
        std::vector<sf::Sprite> west{CLYDED_LEFT_1, CLYDED_LEFT_2};
        std::vector<sf::Sprite> south{CLYDED_DOWN_1, CLYDED_DOWN_2};
        std::vector<sf::Sprite> north{CLYDED_UP_1, CLYDED_UP_2};

        animation_sequences[logic::Direction::East] = east;
        animation_sequences[logic::Direction::North] = north;
        animation_sequences[logic::Direction::West] = west;
        animation_sequences[logic::Direction::South] = south;
    }
}

void representation::GhostView::onNotify(const logic::Subject& entity, logic::Event& event) {

    switch (event) {
    case (logic::Event::EntityPositionChanged): {
        world_pos_ = entity.get_position();
        break;
    }
    case (logic::Event::EntityDirectionChanged): {
        auto* model = dynamic_cast<const logic::MoveableSubject*>(&entity);
        if (!model) { // entity has to be a MoveableSubject
            return;
        }
        world_direction = model->get_direction();
        break;
    }
    case (logic::Event::FearMode): {
        fear_mode = true;
        break;
    }
    case (logic::Event::ChaseMode): {
        fear_mode = false;
        break;
    }
    }
}

void representation::GhostView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    auto screen = cam->worldToScreen(world_pos_, {35, 35});
    sf::Vector2f new_coords = screen.first;
    std::vector<sf::Sprite> sprite_sequence;
    if (fear_mode) {
        sprite_sequence = animation_sequences[logic::Direction::NoDirection]; // fear-mode sprites
    } else {
        sprite_sequence = animation_sequences.at(world_direction); // normal suquence
    }
    sf::Sprite& sprite = sprite_sequence.at(current_sprite_index);
    sf::Vector2f sprite_size = screen.second;
    sprite.setScale(sprite_size);
    sprite.setPosition(new_coords.x, new_coords.y);
    window.draw(sprite);
}

void representation::GhostView::update(double dt) {
    // animation of the ghost (does not draw anything)
    animation_timer += dt;
    if (animation_timer > animation_speed) { // sprite needs to be changed
        // reset timer
        animation_timer = 0.0f;
        std::vector<sf::Sprite> crnt_sequence;
        if (fear_mode) {
            crnt_sequence = animation_sequences.at(logic::Direction::NoDirection); // fear mode sprite
        } else {
            crnt_sequence = animation_sequences.at(world_direction); // normal mode sprite
        }
        // next sprite
        current_sprite_index += 1;
        current_sprite_index %= crnt_sequence.size();
    }
}