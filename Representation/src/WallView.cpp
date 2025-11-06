//
// Created by milo on 11/5/25.
//

#include "../include/WallView.h"

representation::WallView::WallView(const std::shared_ptr<logic::WallModel>& model) {
    model->addObserver(this);
}

void representation::WallView::onNotify(const logic::Subject& entity, logic::Event& e) {
}

void representation::WallView::draw(sf::RenderWindow& window, Camera& cam) {

}