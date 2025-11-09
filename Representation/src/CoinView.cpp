//
// Created by milo on 11/5/25.
//

#include "../include/CoinView.h"
#include "../../Logic/include/CoinModel.h"
#include "../include/SpriteMap.h"

representation::CoinView::CoinView(std::shared_ptr<logic::CoinModel> model, SpriteMap& sprite_map) {
    model->addObserver(this);
    // ----------- sprites -----------
    sf::Sprite coin = sprite_map.getSprite(sf::IntRect(853,5,35,35));
    std::vector<sf::Sprite> east{};
}

void representation::CoinView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::CoinView::draw(sf::RenderWindow& window, Camera& cam) {

}