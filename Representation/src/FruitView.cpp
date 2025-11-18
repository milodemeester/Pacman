//
// Created by milo on 11/5/25.
//

#include "../include/FruitView.h"
#include "../../Logic/include/FruitModel.h"

representation::FruitView::FruitView(std::shared_ptr<logic::FruitModel>& model) { model->addObserver(this); }

void representation::FruitView::onNotify(const logic::Subject& entity, logic::Event& e) {}

void representation::FruitView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {}