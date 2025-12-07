//
// Created by milo on 11/20/25.
//

#include "../include/BlinkyModel.h"

logic::BlinkyModel::BlinkyModel(Coordinate pos, Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 5000; // 5 seconden voor blinky
}

void logic::BlinkyModel::update(float dt, World& world) {
    // clyde is the third ghost, chases 4 locations in front of pacman
    Coordinate target = compute_pacman_forward_pos(world, 4.0);
    update_(dt, world, target);
}