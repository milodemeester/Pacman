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
        float y = 0.f + 2.f * (1.f / world_height_); // 2 "blocks" above the box
        target = {x, y};
        if (utils::compute_manhattan_distance({target}, position_) < 0.05f) {
            // out of box
            in_box = false;
            target = compute_pacman_forward_pos(world, 2.0f);
        }
    } else { // out of box, chase 2 blocks in front of pacman
        target = compute_pacman_forward_pos(world, 2.0f);
    }
    update_(dt, world, target);
}
} // namespace logic::entity