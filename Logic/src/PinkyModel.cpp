//
// Created by milo on 11/20/25.
//

#include "../include/PinkyModel.h"
#include "../include/World.h"

logic::PinkyModel::PinkyModel(Coordinate pos, Direction dir, int world_width, int world_height)
    : Type2Ghost(pos, dir, world_width, world_height) {
    wait_time = 0;
}

void logic::PinkyModel::update(float dt, World& world) {
    // clyde is the third ghost, chases 2 locations in front of pacman
    Coordinate target = compute_pacman_forward_pos(world, 2.0);
    update_(dt, world, target);
}