//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_GAMEFACTORY_H
#define PACMAN_GAMEFACTORY_H
#include <memory>

class Pacman;
class Ghost;
class Wall;
class Fruit;
class Coin;

class GameFactory {
public:
    virtual ~GameFactory() = default;
    virtual std::shared_ptr<Pacman> createPacman() = 0;
    virtual std::shared_ptr<Ghost> createGhost(std::string name) = 0;
    virtual std::shared_ptr<Wall> createWall() = 0;
    virtual std::shared_ptr<Fruit> createFruit() = 0;
    virtual std::shared_ptr<Coin> createCoin() = 0;

};

#endif // PACMAN_GAMEFACTORY_H
