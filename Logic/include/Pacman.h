//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Entity.h"

class Pacman : public Entity {
public:
    Pacman() = default;
    void update(float dt) override;
};

#endif // PACMAN_PACMAN_H
