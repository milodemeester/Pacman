//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"

#include "../include/Stopwatch.h"
#include "../include/World.h"
#include "Event.h"

namespace logic::entity {
Direction GhostModel::get_opposite_direction(Direction dir) {
    switch (dir) {
    case (Direction::North): {
        return Direction::South;
    }
    case (Direction::East): {
        return Direction::West;
    }
    case (Direction::South): {
        return Direction::North;
    }
    case (Direction::West): {
        return Direction::East;
    }
    }
    return Direction::East;
}

std::vector<Direction> GhostModel::get_other_direction(Direction dir) {
    switch (dir) {
    case (Direction::East): {
        return {Direction::North, Direction::South, Direction::West};
    }
    case (Direction::South): {
        return {Direction::North, Direction::East, Direction::West};
    }
    case (Direction::West): {
        return {Direction::North, Direction::East, Direction::South};
    }
    case (Direction::North): {
        return {Direction::East, Direction::South, Direction::West};
    }
    default: {
        return {};
    }
    }
}

GhostModel::GhostModel(Coordinate pos, Direction dir, int world_width, int world_height)
    : MoveableSubject(pos, dir, world_width, world_height) {
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    initialize_time = stopwatch->get_now();
}

void GhostModel::update(float dt, World& world) {
    // check if the ghost can leave the center
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    auto time_waited = stopwatch->get_time_between(stopwatch->get_now(), initialize_time);
    if (wait_time < time_waited) {
        waiting = false;
    }
}

float GhostModel::get_speed() { return speed_; }

void GhostModel::set_fear_mode() {
    chasing_mode = false;
    Event e = Event::FearMode;
    notify(e);
}

void GhostModel::set_chase_mode() {
    chasing_mode = true;
    Event e = Event::ChaseMode;
    notify(e);
}

bool GhostModel::is_chasing_mode() { return chasing_mode; }
}