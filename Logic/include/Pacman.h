//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "../../Representation/include/Entity.h"

class Pacman : public Entity {
public:
    Pacman(Coordinate coordinate, double speed) : Entity(coordinate, speed) {}
};

#endif // PACMAN_PACMAN_H
