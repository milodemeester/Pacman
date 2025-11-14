//
// Created by milo on 11/5/25.
//

#include "../include/WallView.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

representation::WallView::WallView(const std::shared_ptr<logic::WallModel>& model, SpriteMap& sprite_map) {
    sf::Sprite sprite = sprite_map.getWallSprite({32, 32, 35,35});
    m_sprites.insert(std::pair(WallSpriteState::Wall, sprite));

    model_ = model;
    model_->addObserver(this);
}

void representation::WallView::onNotify(const logic::Subject& entity, logic::Event& e) {
}

void representation::WallView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    sf::Sprite& sprite = m_sprites.at(WallSpriteState::Wall);
    auto local_bounds = sprite.getLocalBounds();
    auto screen = cam->worldToScreen(model_->get_position(), {32, 32});
    sf::Vector2f new_coords = screen.first;
    sf::Vector2f sprite_size = screen.second;
    sprite.setPosition(new_coords.x, new_coords.y);
    sprite.setScale(sprite_size);
    window.draw(sprite);
}