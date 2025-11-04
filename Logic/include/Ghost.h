//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Entity.h"
#include <string>
#include <utility>

class Ghost : public Entity {
    std::string name;
public:
    explicit Ghost(std::string name) : name(std::move(name)) {}
    void update(float dt) override;

};

#endif // PACMAN_GHOST_H
