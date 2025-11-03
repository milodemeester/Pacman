//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H
#include "../../Utilities/utils.h"

class Entity {
    Coordinate position;
    enum Direction { N = 'N', E = 'E', S = 'S', W = 'W' };
    Direction dir = N;
    double speed; // measured in pixels/second

public:
    Entity(Coordinate coordinate, double s) : position(coordinate), speed(s) {}
    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& position) { this->position = position; }
};

#endif //PACMAN_ENTITY_H
