//
// Created by milo on 11/5/25.
//

#include "../include/PacmanView.h"
#include "../../Logic/include/PacmanModel.h"
#include "../include/Camera.h"
#include "../include/FruitView.h"
#include "../include/SpriteMap.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Texture.hpp>

representation::PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel>& model) {
    model_ = model;
    model->addObserver(this);
    SpriteMap sprite_map("../data/sprite.png");
    sf::Sprite pacman_closed = sprite_map.getSprite(sf::IntRect(853,5,33,33));
    sf::Sprite open_right1 = sprite_map.getSprite(sf::IntRect(853,55,30,33));
    sf::Sprite open_right2 = sprite_map.getSprite(sf::IntRect(853,105,23,33));
    sf::Sprite open_left1 = sprite_map.getSprite(sf::IntRect(855,355,30,33));
    sf::Sprite open_left2 = sprite_map.getSprite(sf::IntRect(862,405,23,33));
    sf::Sprite open_down1 = sprite_map.getSprite(sf::IntRect(852,205,33,30));
    sf::Sprite open_down2 = sprite_map.getSprite(sf::IntRect(852,255,33,23));
    sf::Sprite open_up1 = sprite_map.getSprite(sf::IntRect(853,507,33,30));
    sf::Sprite open_up2 = sprite_map.getSprite(sf::IntRect(853,564,33,23));
    m_sprites.insert(std::pair(PacmanSpriteState::CLOSED, pacman_closed));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_RIGHT_1, open_right1));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_RIGHT_2, open_right2));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_LEFT_1, open_left1));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_LEFT_2, open_left2));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_DOWN_1, open_down1));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_DOWN_2, open_down2));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_UP_1, open_up1));
    m_sprites.insert(std::pair(PacmanSpriteState::OPEN_UP_2, open_up2));
}

void representation::PacmanView::onNotify(const logic::Subject& entity, logic::Event& event) {
    if (event == logic::Event::EntityPositionChanged) {

    }
}

void representation::PacmanView::draw(sf::RenderWindow& window, Camera& cam) {
    sf::Vector2f new_coords = cam.worldToScreen(model_->get_position(), window.getSize(), cam.get_world_size());
    sf::Sprite& sprite = m_sprites.at(PacmanSpriteState::OPEN_RIGHT_1);
    sprite.setPosition(new_coords.x, new_coords.y);
    window.draw(sprite);
}