//
// Created by milo on 11/5/25.
//

#include "../include/CoinView.h"
#include "../../Logic/include/CoinModel.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"

representation::CoinView::CoinView(std::shared_ptr<logic::entity::CoinModel> model, SpriteMap& sprite_map)
    : sprite(sprite_map.getSprite(sf::IntRect(404, 402, 35, 35))) {
    world_location_ = model->get_position();
}

void representation::CoinView::onNotify(const logic::entity::Subject& entity, logic::Event& e) {
    if (e == logic::Event::EntityPositionChanged) {
        world_location_ = entity.get_position();
    } else if (e == logic::Event::EntityDestruct) {
        invisible = true;
    } else if (e == logic::Event::EntityReset) {
        invisible = false;
    }
}

void representation::CoinView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    if (!invisible) {
        auto screen = cam->worldToScreen(world_location_, {32, 32});
        sf::Vector2f sprite_size = screen.second;
        sf::Vector2f new_coords = screen.first;
        sprite.setScale(sprite_size);
        sprite.setColor(sf::Color::White);
        sprite.setPosition(new_coords.x, new_coords.y);
        window.draw(sprite);
    }
}