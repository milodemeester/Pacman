//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"

#include "../include/Stopwatch.h"
#include "../include/World.h"
#include "Event.h"

namespace logic::entity {
core::Direction GhostModel::get_opposite_direction(core::Direction dir) {
    switch (dir) {
    case (core::Direction::North): {
        return core::Direction::South;
    }
    case (core::Direction::East): {
        return core::Direction::West;
    }
    case (core::Direction::South): {
        return core::Direction::North;
    }
    case (core::Direction::West): {
        return core::Direction::East;
    }
    }
    return core::Direction::East;
}

std::vector<core::Direction> GhostModel::get_other_direction(core::Direction dir) {
    switch (dir) {
    case (core::Direction::East): {
        return {core::Direction::North, core::Direction::South, core::Direction::West};
    }
    case (core::Direction::South): {
        return {core::Direction::North, core::Direction::East, core::Direction::West};
    }
    case (core::Direction::West): {
        return {core::Direction::North, core::Direction::East, core::Direction::South};
    }
    case (core::Direction::North): {
        return {core::Direction::East, core::Direction::South, core::Direction::West};
    }
    default: {
        return {};
    }
    }
}

GhostModel::GhostModel(Coordinate pos, core::Direction dir, int world_width, int world_height)
    : MoveableSubject(pos, dir, world_width, world_height) {
    std::shared_ptr<core::Stopwatch> stopwatch = core::Stopwatch::getInstance();
    initialize_time = stopwatch->get_now();
}

void GhostModel::update(float dt, core::World& world) {
    // check if the ghost can leave the center
    std::shared_ptr<core::Stopwatch> stopwatch = core::Stopwatch::getInstance();
    auto time_waited = stopwatch->get_time_between(stopwatch->get_now(), initialize_time);
    if (wait_time < time_waited) {
        waiting = false;
    }
}

float GhostModel::get_speed() { return speed_; }

void GhostModel::set_fear_mode() {
    chasing_mode = false;
    core::Event e = core::Event::FearMode;
    notify(e);
}

void GhostModel::set_chase_mode() {
    chasing_mode = true;
    core::Event e = core::Event::ChaseMode;
    notify(e);
}

bool GhostModel::is_chasing_mode() { return chasing_mode; }
} // namespace logic::entity