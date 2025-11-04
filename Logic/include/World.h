//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "Entity.h"
#include "GameFactory.h"
#include "Score.h"
#include <memory>
#include <vector>

class World{
    std::vector<std::shared_ptr<Wall>> walls;
    int width;
    int height;
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<Pacman> pacman;
    std::shared_ptr<Ghost> blinky ;
    std::shared_ptr<Ghost> pinky ;
    std::shared_ptr<Ghost> inky ;
    std::shared_ptr<Ghost> clyde ;
public:
    World(const std::shared_ptr<GameFactory>& factory, int width, int height);
    void update(double delta_time);
};


#endif //PACMAN_WORLD_H