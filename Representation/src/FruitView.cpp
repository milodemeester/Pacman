//
// Created by milo on 11/5/25.
//

#include "../include/FruitView.h"
#include "../../Logic/include/FruitModel.h"
#include "../include/Camera.h"

representation::FruitView::FruitView(std::shared_ptr<logic::entity::FruitModel>& model, SpriteMap& sprite_map)
    : sprite(sprite_map.getSprite(sf::IntRect(601, 153, 36, 36))) {
    world_location_ = model->get_position();
}
void representation::FruitView::onNotify(const logic::entity::Subject& entity, logic::core::Event& e) {
    switch (e) {
    case (logic::core::Event::EntityPositionChanged): {
        world_location_ = entity.get_position();
        break;
    }
    case (logic::core::Event::EntityDestruct): {
        invisible = true;
        break;
    }
    case (logic::core::Event::EntityReset): {
        invisible = false;
    }
    }
}

void representation::FruitView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    if (!invisible) {
        auto screen = cam->worldToScreen(world_location_, {36, 36});
        sf::Vector2f sprite_size = screen.second;
        sf::Vector2f new_coords = screen.first;
        sprite.setScale(sprite_size);
        sprite.setPosition(new_coords.x, new_coords.y);
        window.draw(sprite);
    }
}