//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "Entity.h"
#include "Stopwatch.h"
#include <vector>

class World{
    Stopwatch* stopwatch;
    std::vector<Entity*> entities;

};


#endif //PACMAN_WORLD_H