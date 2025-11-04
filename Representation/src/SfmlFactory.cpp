//
// Created by milo on 11/4/25.
//
#include "../../Logic/include/Pacman.h"
#include "../../Logic/include/Ghost.h"
#include "../include/SfmlFactory.h"

#include "../../Logic/include/Coin.h"
#include "../../Logic/include/Fruit.h"
#include "../../Logic/include/Wall.h"

SfmlFactory::SfmlFactory(Camera& c) {
    camera = c;
}

std::shared_ptr<Pacman> SfmlFactory::createPacman() {
    std::shared_ptr<Pacman> pacman = std::make_shared<Pacman>();
    return pacman;
}

std::shared_ptr<Ghost> SfmlFactory::createGhost(std::string name) {
    auto ghost = std::make_shared<Ghost>(name);
    return ghost;

}
std::shared_ptr<Coin> SfmlFactory::createCoin() {
    auto coin = std::make_shared<Coin>();
    return coin;
}
std::shared_ptr<Fruit> SfmlFactory::createFruit() {
    auto fruit = std::make_shared<Fruit>();
    return fruit;
}
std::shared_ptr<Wall> SfmlFactory::createWall() {
    auto wall = std::make_shared<Wall>();
    return wall;
}