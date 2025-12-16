//
// Created by milo on 11/5/25.
//

#include "../include/PacmanView.h"
#include "../../Logic/include/PacmanModel.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace representation::view {
PacmanView::PacmanView(const std::shared_ptr<logic::entity::PacmanModel>& model, SpriteMap& sprite_map)
    : sprite_map_(sprite_map) {
    world_direction = model->get_direction();
    world_position = model->get_position();

    // save the textures into the animation_sequence
    sf::IntRect pacman_closed_rect(853, 5, 33, 33);
    sf::IntRect open_right1_rect(853, 55, 33, 33);
    sf::IntRect open_right2_rect(853, 105, 33, 33);
    sf::IntRect open_left1_rect(852, 355, 33, 33);
    sf::IntRect open_left2_rect(852, 405, 33, 33);
    sf::IntRect open_down1_rect(852, 205, 33, 33);
    sf::IntRect open_down2_rect(852, 255, 33, 33);
    sf::IntRect open_up1_rect(853, 504, 33, 33);
    sf::IntRect open_up2_rect(853, 554, 33, 33);

    animation_sequences[logic::core::Direction::East] = {pacman_closed_rect, open_right1_rect, open_right2_rect};
    animation_sequences[logic::core::Direction::West] = {pacman_closed_rect, open_left1_rect, open_left2_rect};
    animation_sequences[logic::core::Direction::North] = {pacman_closed_rect, open_up1_rect, open_up2_rect};
    animation_sequences[logic::core::Direction::South] = {pacman_closed_rect, open_down1_rect, open_down2_rect};
}

void PacmanView::onNotify(const logic::entity::Subject& entity, logic::core::Event& event) {
    switch (event) {
    case (logic::core::Event::EntityPositionChanged): {
        world_position = entity.get_position();
        break;
    }
    case (logic::core::Event::EntityDirectionChanged): {
        world_direction = entity.get_direction();
        break;
    }
    }
}

void PacmanView::update(float dt) {
    // handle animation
    animation_timer += dt;
    if (animation_timer > animation_speed) {
        // reset animation timer and move index
        animation_timer = 0.0f;
        const auto& crnt_sequence = animation_sequences.at(world_direction);
        if (!crnt_sequence.empty()) {
            current_sprite_index = (current_sprite_index + 1) % crnt_sequence.size();
        }
    }
}

void PacmanView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    // Get the sprite IntRect
    const auto& sprite_rects = animation_sequences.at(world_direction);
    if (sprite_rects.empty() || current_sprite_index >= sprite_rects.size()) {
        return; // do nothing if the animation is not valid
    }
    const sf::IntRect& current_rect = sprite_rects.at(current_sprite_index);

    // Make a new sprite using this rect
    sf::Sprite sprite = sprite_map_.getSprite(current_rect);

    // use the camera to calculate the coordinates
    auto screen = cam->worldToScreen(world_position, {33, 33});
    sf::Vector2f new_coords = screen.first;
    sf::Vector2f sprite_size = screen.second;

    sprite.setScale(sprite_size);
    sprite.setPosition(new_coords);
    window.draw(sprite);
}
} // namespace representation::view