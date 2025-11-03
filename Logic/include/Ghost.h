//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../../Representation/include/Entity.h"
#include <string>

class Ghost : public Entity {
    std::string name;
public:
    Ghost(std::string name, Coordinate coordinate, double speed) : name(name), Entity(coordinate, speed) {}

};

#endif // PACMAN_GHOST_H
