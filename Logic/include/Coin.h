//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Entity.h"

class Coin : public Entity {
public:
    Coin() = default;
    void update(float dt) override;
};

#endif // PACMAN_COIN_H
