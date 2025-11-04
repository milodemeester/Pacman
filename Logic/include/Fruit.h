//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H
#include "Entity.h"

class Fruit : public Entity {
public:
    Fruit() = default;
    void update(float dt) override;
};
#endif // PACMAN_FRUIT_H
