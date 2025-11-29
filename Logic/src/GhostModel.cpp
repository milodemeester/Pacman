//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"
#include "../include/Stopwatch.h"
#include "../include/World.h"

logic::Direction logic::GhostModel::get_opposite_direction(logic::Direction dir) {
    switch (dir) {
    case (logic::Direction::North) : {
        return logic::Direction::South;
    }
    case (logic::Direction::East) : {
        return logic::Direction::West;
    }
    case (logic::Direction::South) : {
        return logic::Direction::North;
    }
    case (logic::Direction::West) : {
        return logic::Direction::East;
    }
    }
    return logic::Direction::East;
}

std::vector<logic::Direction> logic::GhostModel::get_other_direction(logic::Direction dir) {
    switch (dir) {
    case (logic::Direction::East): {
        return {logic::Direction::North, logic::Direction::South, logic::Direction::West};
    }
    case (logic::Direction::South): {
        return {logic::Direction::North, logic::Direction::East, logic::Direction::West};
    }
    case (logic::Direction::West): {
        return {logic::Direction::North, logic::Direction::East, logic::Direction::South};
    }
    case (logic::Direction::North): {
        return {logic::Direction::East, logic::Direction::South, logic::Direction::West};
    }
    default: {
        return {};
    }
    }
}

logic::GhostModel::GhostModel(Coordinate pos, Direction dir, int world_width, int world_height) : MoveableSubject(pos, dir, world_width, world_height) {
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    initialize_time = stopwatch->get_now();
}

void logic::GhostModel::update(float dt) {
    // check if the ghost can leave the center
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    auto time_waited = stopwatch->get_time_between(stopwatch->get_now(), initialize_time);
    if (wait_time < time_waited) {
        waiting = false;
    }
}

double logic::GhostModel::get_speed() {
    return speed_;
}

void logic::GhostModel::set_fear_mode() {
    chasing_mode = false;
    Event e = Event::FearMode;
    notify(e);
}

void logic::GhostModel::set_chase_mode() {
    chasing_mode = true;
    Event e = Event::ChaseMode;
    notify(e);
}

bool logic::GhostModel::is_chasing_mode() {
    return chasing_mode;
}