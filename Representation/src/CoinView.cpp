//
// Created by milo on 11/5/25.
//

#include "../include/CoinView.h"
#include "../../Logic/include/CoinModel.h"

representation::CoinView::CoinView(std::shared_ptr<logic::CoinModel> model) {
    model->addObserver(this);
}

void representation::CoinView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::CoinView::draw(sf::RenderWindow& window, Camera& cam) {

}