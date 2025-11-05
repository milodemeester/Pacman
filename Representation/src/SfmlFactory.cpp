//
// Created by milo on 11/4/25.
//
#include "../include/SfmlFactory.h"

#include "../../Logic/include/CoinModel.h"
#include "../../Logic/include/FruitModel.h"
#include "../../Logic/include/GhostModel.h"
#include "../../Logic/include/PacmanModel.h"
#include "../../Logic/include/WallModel.h"

#include "../include/CoinView.h"
#include "../include/FruitView.h"
#include "../include/GhostView.h"
#include "../include/PacmanView.h"
#include "../include/WallView.h"

representation::SfmlFactory::SfmlFactory(Camera& c, sf::Vector2u w) {
    camera = c;
    windowSize = w;
}

std::vector<std::unique_ptr<representation::EntityView>>& representation::SfmlFactory::getCreatedViews() {
    return createdViews;
}

std::shared_ptr<logic::PacmanModel> representation::SfmlFactory::createPacman() {
    auto pacman_model = std::make_shared<logic::PacmanModel>(Coordinate(0,0),logic::Direction());
    auto pacman_view = std::make_unique<representation::PacmanView>(pacman_model);
    createdViews.push_back(std::move(pacman_view));
    return pacman_model;
}

std::shared_ptr<logic::GhostModel> representation::SfmlFactory::createGhost(std::string name) {
    auto ghost_model = std::make_shared<logic::GhostModel>();
    auto ghost_view = std::make_unique<representation::GhostView>(ghost_model);
    createdViews.push_back(std::move(ghost_view));
    return ghost_model;
}
std::shared_ptr<logic::CoinModel> representation::SfmlFactory::createCoin() {
    auto coin_model = std::make_shared<logic::CoinModel>();
    auto coin_view = std::make_unique<representation::CoinView>(coin_model);
    createdViews.push_back(std::move(coin_view));
    return coin_model;
}
std::shared_ptr<logic::FruitModel> representation::SfmlFactory::createFruit() {
    auto fruit_model = std::make_shared<logic::FruitModel>();
    auto fruit_view = std::make_unique<representation::FruitView>(fruit_model);
    createdViews.push_back(std::move(fruit_view));
    return fruit_model;
}
std::shared_ptr<logic::WallModel> representation::SfmlFactory::createWall() {
    auto wall_model = std::make_shared<logic::WallModel>();
    auto wall_view = std::make_unique<representation::WallView>(wall_model);
    createdViews.push_back(std::move(wall_view));
    return wall_model;
}