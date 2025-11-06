//
// Created by milo on 11/5/25.
//

#include "../include/GhostView.h"
#include "../../Logic/include/GhostModel.h"
#include "../include/SpriteMap.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../include/Camera.h"

representation::GhostView::GhostView(std::shared_ptr<logic::GhostModel>& model, SpriteMap& sprite_map, std::string name) : name_(name) {
    model_ = model;
    model_->addObserver(this);
    // ----------- sprites -----------

    if (name == "Blinky") {
        // ----------- blinky -----------
        current_state = GhostSpriteState::BLINKY_RIGHT_1;
        sf::Sprite BLINKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(1,4,35,35));
        sf::Sprite BLINKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(1,54,35,35));
        sf::Sprite BLINKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(1,204,35,35));
        sf::Sprite BLINKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(1,254,35,35));
        sf::Sprite BLINKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(1,104,35,35));
        sf::Sprite BLINKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(1,154,35,35));
        sf::Sprite BLINKY_UP_1 = sprite_map.getSprite(sf::IntRect(1,304,35,35));
        sf::Sprite BLINKY_UP_2 = sprite_map.getSprite(sf::IntRect(1,354,35,35));

        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_RIGHT_1, BLINKY_RIGHT_1));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_RIGHT_2, BLINKY_RIGHT_2));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_LEFT_1, BLINKY_LEFT_1));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_LEFT_2, BLINKY_LEFT_2));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_DOWN_1, BLINKY_DOWN_1));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_DOWN_2, BLINKY_DOWN_2));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_UP_1, BLINKY_UP_1));
        m_sprites.insert(std::pair(GhostSpriteState::BLINKY_UP_2, BLINKY_UP_2));

        std::vector<GhostSpriteState> right_sequence{GhostSpriteState::BLINKY_RIGHT_1,GhostSpriteState::BLINKY_RIGHT_2};
        std::vector<GhostSpriteState> up_sequence{GhostSpriteState::BLINKY_UP_1,GhostSpriteState::BLINKY_UP_2};
        std::vector<GhostSpriteState> left_sequence{GhostSpriteState::BLINKY_LEFT_1,GhostSpriteState::BLINKY_LEFT_2};
        std::vector<GhostSpriteState> down_sequence{GhostSpriteState::BLINKY_DOWN_1,GhostSpriteState::BLINKY_DOWN_2};
        animation_sequences[logic::Direction::North] = up_sequence;
        animation_sequences[logic::Direction::East] = right_sequence;
        animation_sequences[logic::Direction::South] = down_sequence;
        animation_sequences[logic::Direction::West] = left_sequence;
    }

    else if (name == "Inky") {
        // ----------- inky -----------
        current_state = GhostSpriteState::INKY_RIGHT_1;
        sf::Sprite INKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(101,4,35,35));
        sf::Sprite INKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(101,54,35,35));
        sf::Sprite INKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(101,204,35,35));
        sf::Sprite INKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(101,254,35,35));
        sf::Sprite INKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(101,104,35,35));
        sf::Sprite INKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(101,154,35,35));
        sf::Sprite INKY_UP_1 = sprite_map.getSprite(sf::IntRect(101,304,35,35));
        sf::Sprite INKY_UP_2 = sprite_map.getSprite(sf::IntRect(101,354,35,35));

        m_sprites.insert(std::pair(GhostSpriteState::INKY_RIGHT_1, INKY_RIGHT_1));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_RIGHT_2, INKY_RIGHT_2));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_LEFT_1, INKY_LEFT_1));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_LEFT_2, INKY_LEFT_2));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_DOWN_1, INKY_DOWN_1));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_DOWN_2, INKY_DOWN_2));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_UP_1, INKY_UP_1));
        m_sprites.insert(std::pair(GhostSpriteState::INKY_UP_2, INKY_UP_2));

        std::vector<GhostSpriteState> right_sequence = {GhostSpriteState::INKY_RIGHT_1,GhostSpriteState::INKY_RIGHT_2};
        std::vector<GhostSpriteState> up_sequence = {GhostSpriteState::INKY_UP_1,GhostSpriteState::INKY_UP_2};
        std::vector<GhostSpriteState> left_sequence = {GhostSpriteState::INKY_LEFT_1,GhostSpriteState::INKY_LEFT_2};
        std::vector<GhostSpriteState> down_sequence = {GhostSpriteState::INKY_DOWN_1,GhostSpriteState::INKY_DOWN_2};
        animation_sequences[logic::Direction::North] = up_sequence;
        animation_sequences[logic::Direction::East] = right_sequence;
        animation_sequences[logic::Direction::South] = down_sequence;
        animation_sequences[logic::Direction::West] = left_sequence;
    }

    else if (name == "Pinky") {
        // ----------- pinky -----------
        current_state = GhostSpriteState::PINKY_RIGHT_1;
        sf::Sprite PINKY_RIGHT_1 = sprite_map.getSprite(sf::IntRect(51,4,35,35));
        sf::Sprite PINKY_RIGHT_2 = sprite_map.getSprite(sf::IntRect(51,54,35,35));
        sf::Sprite PINKY_DOWN_1 = sprite_map.getSprite(sf::IntRect(51,104,35,35));
        sf::Sprite PINKY_DOWN_2 = sprite_map.getSprite(sf::IntRect(51,154,35,35));
        sf::Sprite PINKY_LEFT_1 = sprite_map.getSprite(sf::IntRect(51,204,35,35));
        sf::Sprite PINKY_LEFT_2 = sprite_map.getSprite(sf::IntRect(51,254,35,35));
        sf::Sprite PINKY_UP_1 = sprite_map.getSprite(sf::IntRect(51,304,35,35));
        sf::Sprite PINKY_UP_2 = sprite_map.getSprite(sf::IntRect(51,354,35,35));

        m_sprites.insert(std::pair(GhostSpriteState::PINKY_RIGHT_1, PINKY_RIGHT_1));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_RIGHT_2, PINKY_RIGHT_2));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_DOWN_1, PINKY_DOWN_1));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_DOWN_2, PINKY_DOWN_2));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_LEFT_1, PINKY_LEFT_1));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_LEFT_2, PINKY_LEFT_2));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_UP_1, PINKY_UP_1));
        m_sprites.insert(std::pair(GhostSpriteState::PINKY_UP_2, PINKY_UP_2));

        std::vector<GhostSpriteState> right_sequence = {GhostSpriteState::PINKY_RIGHT_1,GhostSpriteState::PINKY_RIGHT_2};
        std::vector<GhostSpriteState> up_sequence = {GhostSpriteState::PINKY_UP_1,GhostSpriteState::PINKY_UP_2};
        std::vector<GhostSpriteState> left_sequence = {GhostSpriteState::PINKY_LEFT_1,GhostSpriteState::PINKY_LEFT_2};
        std::vector<GhostSpriteState> down_sequence = {GhostSpriteState::PINKY_DOWN_1,GhostSpriteState::PINKY_DOWN_2};
        animation_sequences[logic::Direction::North] = up_sequence;
        animation_sequences[logic::Direction::East] = right_sequence;
        animation_sequences[logic::Direction::South] = down_sequence;
        animation_sequences[logic::Direction::West] = left_sequence;
    }

    else if (name == "Clyde") {
        // ----------- clyde -----------
        current_state = GhostSpriteState::CLYDED_RIGHT_1;
        sf::Sprite CLYDED_RIGHT_1 = sprite_map.getSprite(sf::IntRect(151,4,35,35));
        sf::Sprite CLYDED_RIGHT_2 = sprite_map.getSprite(sf::IntRect(151,54,35,35));
        sf::Sprite CLYDED_LEFT_1 = sprite_map.getSprite(sf::IntRect(151,204,35,35));
        sf::Sprite CLYDED_LEFT_2 = sprite_map.getSprite(sf::IntRect(151,254,35,35));
        sf::Sprite CLYDED_DOWN_1 = sprite_map.getSprite(sf::IntRect(151,104,35,35));
        sf::Sprite CLYDED_DOWN_2 = sprite_map.getSprite(sf::IntRect(151,154,35,35));
        sf::Sprite CLYDED_UP_1 = sprite_map.getSprite(sf::IntRect(151,304,35,35));
        sf::Sprite CLYDED_UP_2 = sprite_map.getSprite(sf::IntRect(151,354,35,35));

        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_RIGHT_1, CLYDED_RIGHT_1));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_RIGHT_2, CLYDED_RIGHT_2));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_LEFT_1, CLYDED_LEFT_1));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_LEFT_2, CLYDED_LEFT_2));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_DOWN_1, CLYDED_DOWN_1));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_DOWN_2, CLYDED_DOWN_2));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_UP_1, CLYDED_UP_1));
        m_sprites.insert(std::pair(GhostSpriteState::CLYDED_UP_2, CLYDED_UP_2));

        std::vector<GhostSpriteState> right_sequence = {GhostSpriteState::CLYDED_RIGHT_1,GhostSpriteState::CLYDED_RIGHT_2};
        std::vector<GhostSpriteState> up_sequence = {GhostSpriteState::CLYDED_UP_1,GhostSpriteState::CLYDED_UP_1};
        std::vector<GhostSpriteState> left_sequence = {GhostSpriteState::CLYDED_LEFT_1,GhostSpriteState::CLYDED_LEFT_2};
        std::vector<GhostSpriteState> down_sequence = {GhostSpriteState::CLYDED_DOWN_1,GhostSpriteState::CLYDED_DOWN_1};
        animation_sequences[logic::Direction::North] = up_sequence;
        animation_sequences[logic::Direction::East] = right_sequence;
        animation_sequences[logic::Direction::South] = down_sequence;
        animation_sequences[logic::Direction::West] = left_sequence;
    }


}

void representation::GhostView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::GhostView::draw(sf::RenderWindow& window, Camera& cam) {
    sf::Vector2f new_coords = cam.worldToScreen(model_->get_position(), window.getSize(), cam.get_world_size());
    sf::Sprite& sprite = m_sprites.at(current_state);
    sprite.setPosition(new_coords.x, new_coords.y);
    window.draw(sprite);
}

void representation::GhostView::update(double dt) {
    animation_timer += dt;
    if (animation_timer > animation_speed) {
        animation_timer = 0.0f;
        std::vector<GhostSpriteState> crnt_sequence = animation_sequences.at(model_->get_direction());
        current_frame_index += 1;
        current_frame_index %= crnt_sequence.size()-1;
        current_state = crnt_sequence[current_frame_index];
    }
}