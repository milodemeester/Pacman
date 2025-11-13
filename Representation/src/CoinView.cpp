//
// Created by milo on 11/5/25.
//

#include "../include/CoinView.h"
#include "../../Logic/include/CoinModel.h"
#include "../include/SpriteMap.h"
#include "../include/Camera.h"

representation::CoinView::CoinView(std::shared_ptr<logic::CoinModel> model, SpriteMap& sprite_map) :
    sprite(sprite_map.getSprite(sf::IntRect(404,402,35,35))) {
    world_position = model->get_position();
    model->addObserver(this);
}

void representation::CoinView::onNotify(const logic::Subject& entity, logic::Event& e) {
    if (e == logic::Event::EntityPositionChanged) {
        world_position = entity.get_position();
    }
    else if (e == logic::Event::EntityDestruct) {
        isEaten = true;
    }
}

void representation::CoinView::draw(sf::RenderWindow& window, Camera& cam) {
    if (!isEaten) {
        auto screen = cam.worldToScreen(world_position, window.getSize(), cam.get_world_size(), {32, 32});
        sf::Vector2f sprite_size = screen.second;
        sf::Vector2f new_coords = screen.first;
        sprite.setScale(sprite_size);
        sprite.setColor(sf::Color::White);
        sprite.setPosition(new_coords.x, new_coords.y);
        window.draw(sprite);
    }
}