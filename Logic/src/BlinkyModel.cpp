//
// Created by milo on 11/20/25.
//

#include "../include/BlinkyModel.h"
#include "../include/Stopwatch.h"

logic::BlinkyModel::BlinkyModel(Coordinate pos, Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 5000;
}

void logic::BlinkyModel::reset_() {
    GhostModel::reset_();
    wait_time = 5000;
    auto stopwatch = Stopwatch::getInstance();
    initialize_time = stopwatch->get_now();
}

void logic::BlinkyModel::go_to_center() {
    set_position(starting_position_);
}