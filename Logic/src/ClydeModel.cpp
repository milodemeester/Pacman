//
// Created by milo on 11/20/25.
//
#include "../include/ClydeModel.h"
#include "../include/World.h"

namespace logic::entity {
ClydeModel::ClydeModel(Coordinate pos, core::Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 10000; // 10 seconden voor clyde
}

void ClydeModel::update(float dt, core::World& world) {
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
            target = world.get_pacman_position();
        }
    } else { // out of box, chase pacman
        target = world.get_pacman_position();
    }
    update_(dt, world, target);
}
} // namespace logic::entity