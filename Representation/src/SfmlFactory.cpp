//
// Created by milo on 11/4/25.
//
#include <utility>

#include "../include/SfmlFactory.h"

#include "../../Logic/include/BlinkyModel.h"
#include "../../Logic/include/ClydeModel.h"
#include "../../Logic/include/CoinModel.h"
#include "../../Logic/include/FruitModel.h"
#include "../../Logic/include/InkyModel.h"
#include "../../Logic/include/PacmanModel.h"
#include "../../Logic/include/PinkyModel.h"
#include "../../Logic/include/WallModel.h"

#include "../include/CoinView.h"
#include "../include/FruitView.h"
#include "../include/GhostView.h"
#include "../include/PacmanView.h"
#include "../include/WallView.h"

representation::SfmlFactory::SfmlFactory(std::shared_ptr<Camera> c, sf::Vector2u w, SpriteMap& spriteMap,
                                         std::shared_ptr<logic::Score> score)
    : sprite_map_(spriteMap), score_(score) {
    camera_ = std::move(c);
    windowSize_ = w;
}

std::vector<std::shared_ptr<representation::EntityView>> representation::SfmlFactory::getCreatedViews() {
    return createdViews_;
}

std::shared_ptr<logic::PacmanModel> representation::SfmlFactory::createPacman(int ww, int wh) {
    auto pacman_model = std::make_shared<logic::PacmanModel>(Coordinate(0, 0), logic::Direction::East, ww, wh);
    auto pacman_view = std::make_shared<PacmanView>(pacman_model, sprite_map_);
    pacman_model->addObserver(score_);
    pacman_model->addObserver(pacman_view);
    createdViews_.push_back(pacman_view);
    return pacman_model;
}

std::shared_ptr<logic::GhostModel> representation::SfmlFactory::createGhost(logic::GhostType type, int ww, int wh) {
    std::shared_ptr<logic::GhostModel> ghost_model;
    switch (type) {
    case (logic::GhostType::Blinky): {
        ghost_model = std::make_shared<logic::BlinkyModel>(Coordinate{0, 0}, logic::Direction::North, ww, wh);
        break;
    }
    case (logic::GhostType::Inky): {
        ghost_model = std::make_shared<logic::InkyModel>(Coordinate{0, 0}, logic::Direction::North, ww, wh);
        break;
    }
    case (logic::GhostType::Pinky): {
        ghost_model = std::make_shared<logic::PinkyModel>(Coordinate{0, 0}, logic::Direction::North, ww, wh);
        break;
    }
    case (logic::GhostType::Clyde): {
        ghost_model = std::make_shared<logic::ClydeModel>(Coordinate{0, 0}, logic::Direction::North, ww, wh);
        break;
    }
    }
    auto ghost_view = std::make_shared<GhostView>(ghost_model, sprite_map_, type);
    ghost_model->addObserver(ghost_view);
    createdViews_.push_back(ghost_view);
    return ghost_model;
}
std::shared_ptr<logic::CoinModel> representation::SfmlFactory::createCoin() {
    auto coin_model = std::make_shared<logic::CoinModel>();
    auto coin_view = std::make_shared<CoinView>(coin_model, sprite_map_);
    coin_model->addObserver(coin_view);
    createdViews_.push_back(coin_view);
    return coin_model;
}
std::shared_ptr<logic::FruitModel> representation::SfmlFactory::createFruit() {
    auto fruit_model = std::make_shared<logic::FruitModel>();
    auto fruit_view = std::make_shared<FruitView>(fruit_model, sprite_map_);
    fruit_model->addObserver(fruit_view);
    createdViews_.push_back(fruit_view);
    return fruit_model;
}
std::shared_ptr<logic::WallModel> representation::SfmlFactory::createWall(bool invisible) {
    auto wall_model = std::make_shared<logic::WallModel>(invisible);
    auto wall_view = std::make_shared<WallView>(wall_model, sprite_map_, invisible);
    wall_model->addObserver(wall_view);
    createdViews_.push_back(wall_view);
    return wall_model;
}