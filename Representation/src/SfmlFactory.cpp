//
// Created by milo on 11/4/25.
//
#include "../include/SfmlFactory.h"
#include "../../Logic/include/GhostModel.h"
#include "../../Logic/include/PacmanModel.h"
#include "../../Logic/include/CoinModel.h"
#include "../../Logic/include/FruitModel.h"
#include "../../Logic/include/WallModel.h"
#include "../include/PacmanView.h"

namespace representation {
class PacmanView;
}
representation::SfmlFactory::SfmlFactory(Camera& c, sf::Vector2u w) {
    camera = c;
    windowSize = w;
}

std::vector<std::unique_ptr<representation::EntityView>>& representation::SfmlFactory::getCreatedViews() {
    return createdViews;
}

std::shared_ptr<logic::PacmanModel> representation::SfmlFactory::createPacman() {
    auto pacman_model = std::make_shared<logic::PacmanModel>(Coordinate(0,0),logic::Direction());
    auto pacman_view = std::make_unique<PacmanView>(pacman_model);
    createdViews.push_back(pacman_view);
    return pacman_model;
}

std::shared_ptr<logic::GhostModel> representation::SfmlFactory::createGhost(std::string name) {
    auto ghost = std::make_shared<logic::GhostView>(name);
    return ghost;
}
std::shared_ptr<logic::CoinModel> representation::SfmlFactory::createCoin() {
    auto coin = std::make_shared<logic::CoinView>();
    return coin;
}
std::shared_ptr<logic::FruitModel> representation::SfmlFactory::createFruit() {
    auto fruit = std::make_shared<logic::FruitView>();
    return fruit;
}
std::shared_ptr<logic::WallModel> representation::SfmlFactory::createWall() {
    auto wall = std::make_shared<logic::WallView>();
    return wall;
}