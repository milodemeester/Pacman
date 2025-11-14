//
// Created by milo on 11/5/25.
//

#include "../include/PacmanView.h"
#include "../../Logic/include/PacmanModel.h"
#include "../../Logic/include/Stopwatch.h"
#include "../include/Camera.h"
#include "../include/FruitView.h"
#include "../include/SpriteMap.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Texture.hpp>

representation::PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel>& model, SpriteMap& sprite_map) {
    model->addObserver(this);
    // ----------- sprites -----------
    sf::Sprite pacman_closed = sprite_map.getSprite(sf::IntRect(853,5,35,35));
    sf::Sprite open_right1 = sprite_map.getSprite(sf::IntRect(853,55,35,35));
    sf::Sprite open_right2 = sprite_map.getSprite(sf::IntRect(853,105,35,35));
    sf::Sprite open_left1 = sprite_map.getSprite(sf::IntRect(855,355,35,35));
    sf::Sprite open_left2 = sprite_map.getSprite(sf::IntRect(862,405,35,35));
    sf::Sprite open_down1 = sprite_map.getSprite(sf::IntRect(852,205,35,35));
    sf::Sprite open_down2 = sprite_map.getSprite(sf::IntRect(852,255,35,35));
    sf::Sprite open_up1 = sprite_map.getSprite(sf::IntRect(853,507,35,35));
    sf::Sprite open_up2 = sprite_map.getSprite(sf::IntRect(853,564,35,35));

    std::vector<sf::Sprite> east{pacman_closed, open_right1, open_right2};
    std::vector<sf::Sprite> north{pacman_closed, open_up1, open_up2};
    std::vector<sf::Sprite> west{pacman_closed, open_left1, open_left2};
    std::vector<sf::Sprite> south{pacman_closed, open_down1, open_down2};

    animation_sequences[logic::Direction::East] = east;
    animation_sequences[logic::Direction::North] = north;
    animation_sequences[logic::Direction::West] = west;
    animation_sequences[logic::Direction::South] = south;
    world_direction = logic::Direction::East;
}

void representation::PacmanView::onNotify(const logic::Subject& entity, logic::Event& event) {
    switch (event) {
        case (logic::Event::EntityPositionChanged) : {
            world_position = entity.get_position();
        }
    case (logic::Event::EntityDirectionChanged) : {
            world_direction = entity.get_direction();
        }
    }
}

void representation::PacmanView::update(double dt) {
    animation_timer += dt;
    if (animation_timer > animation_speed) {
        animation_timer = 0.0f;
        std::vector<sf::Sprite> crnt_sequence = animation_sequences.at(world_direction);
        current_sprite_index += 1;
        current_sprite_index %= crnt_sequence.size();
    }
}

void representation::PacmanView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    auto screen = cam->worldToScreen(world_position, {32, 32});
    sf::Vector2f new_coords = screen.first;
    std::vector<sf::Sprite> sprite_sequence = animation_sequences.at(world_direction);
    sf::Sprite& sprite = sprite_sequence.at(current_sprite_index);
    sf::Vector2f sprite_size = screen.second;
    sprite.setScale(sprite_size);
    sprite.setPosition(new_coords.x, new_coords.y);
    window.draw(sprite);
}