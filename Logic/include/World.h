//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "Score.h"

#include <memory>
#include <vector>

class Entity;

class World{
    std::vector<std::unique_ptr<Entity>> entities;
    int width;
    int height;
public:
    World(int, int);
    void update(double delta_time);
};


#endif //PACMAN_WORLD_H