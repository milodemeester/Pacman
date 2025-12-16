//
// Created by milo on 11/5/25.
//

#include "../include/WallView.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

representation::WallView::WallView(const std::shared_ptr<logic::entity::WallModel>& model, SpriteMap& sprite_map,
                                   bool invisible)
    : invisible_(invisible) {
    sf::Sprite sprite = sprite_map.getWallSprite({0, 0, 35, 35});
    m_sprites_.insert(std::pair(WallSpriteState::Wall, sprite));
    set_location(model->get_position());
}

void representation::WallView::onNotify(const logic::entity::Subject& entity, logic::Event& event) {
    switch (event) {
    case (logic::Event::EntityPositionChanged): {
        set_location(entity.get_position());
        break;
    }
    }
}

void representation::WallView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    if (!invisible_) { // if the wall can be displayed
        sf::Sprite& sprite = m_sprites_.at(WallSpriteState::Wall);
        auto screen = cam->worldToScreen(get_location(), {32, 32});
        sf::Vector2f new_coords = screen.first;
        sf::Vector2f sprite_size = screen.second;
        sprite.setPosition(new_coords.x, new_coords.y);
        sprite.setScale(sprite_size);
        window.draw(sprite);
    }
}