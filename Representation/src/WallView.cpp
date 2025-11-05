//
// Created by milo on 11/5/25.
//

#include "../include/WallView.h"

representation::WallView::WallView(std::shared_ptr<logic::WallModel> model) {
    model->addObserver(this);
}

void representation::WallView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::WallView::update(float dT) {

}

void representation::WallView::draw(sf::RenderWindow& window) {

}