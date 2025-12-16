//
// Created by milo on 11/20/25.
//

#include "../include/PinkyModel.h"
#include "../include/World.h"

namespace logic::entity {
PinkyModel::PinkyModel(Coordinate pos, core::Direction dir, int world_width, int world_height)
    : Type2Ghost(pos, dir, world_width, world_height) {
    wait_time = 0;
}

void PinkyModel::update(float dt, core::World& world) {
    GhostModel::update(dt, world);

    if (waiting) {
        return;
    }
    Coordinate target;
    if (in_box) { // still in box
        float x = position_.getX();
        float y = 0 + 2 * (1 / world_height_); // 2 "blocks" above the box
        target = {x, y};
        if (utils::compute_manhattan_distance({target}, position_) < 0.05) {
            // out of box
            in_box = false;
            target = compute_pacman_forward_pos(world, 2.0);
        }
    } else { // out of box, chase 2 blocks in front of pacman
        target = compute_pacman_forward_pos(world, 2.0);
    }
    update_(dt, world, target);
}
} // namespace logic::entity