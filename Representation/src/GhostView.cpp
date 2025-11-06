//
// Created by milo on 11/5/25.
//

#include "../include/GhostView.h"
#include "../../Logic/include/GhostModel.h"

representation::GhostView::GhostView(std::shared_ptr<logic::GhostModel>& model) {
    model->addObserver(this);
}

void representation::GhostView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::GhostView::draw(sf::RenderWindow& window, Camera& cam) {

}