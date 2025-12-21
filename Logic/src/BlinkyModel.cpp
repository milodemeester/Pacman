//
// Created by milo on 11/20/25.
//

#include "../include/BlinkyModel.h"

namespace logic::entity {

BlinkyModel::BlinkyModel(Coordinate pos, core::Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 5000; // 5 seconden voor blinky
}

void BlinkyModel::update(float dt, core::World& world) {
    GhostModel::update(dt, world);

    if (waiting) {
        return;
    }
    Coordinate target;
    if (in_box) { // still in the box
        float x = position_.getX();
        float y = 0.f + 2.f * (1 / world_height_); // 2 "blocks" above the box
        target = {x, y};
        if (utils::compute_manhattan_distance({target}, position_) < 0.05) {
            // out of box
            in_box = false;
            target = compute_pacman_forward_pos(world, 4.0);
        }
    } else { // out of box, chase 4 blocks in front of pacman
        target = compute_pacman_forward_pos(world, 4.0);
    }
    update_(dt, world, target);
}
} // namespace logic::entity