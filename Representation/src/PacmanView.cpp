//
// Created by milo on 11/5/25.
//

#include "../include/FruitView.h"
#include "../include/PacmanView.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../Logic/include/PacmanModel.h"

representation::PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel>& model) {
    model->addObserver(this);
}

void representation::PacmanView::onNotify(const logic::Subject& entity, logic::Event& e) {

}

void representation::PacmanView::update(float dT) {

}

void representation::PacmanView::draw(sf::RenderWindow& window) {

}