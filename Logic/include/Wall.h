//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "Entity.h"

class Wall : public Entity {
public:
    Wall() = default;
    void update(float dt) override;
};
#endif // PACMAN_WALL_H
