//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"
#include "../include/Stopwatch.h"
#include "../include/World.h"

logic::GhostModel::GhostModel(Coordinate pos, Direction dir, int world_width, int world_height) : MoveableSubject(pos, dir, world_width, world_height) {
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    initialize_time = stopwatch->get_now();
}

void logic::GhostModel::update(float dt) {
    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    auto time_waited = stopwatch->get_time_between(stopwatch->get_now(), initialize_time);
    if (wait_time < time_waited) {
        chasing_mode = true;
    }
}

logic::PinkyModel::PinkyModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) { wait_time = 0; }

logic::BlinkyModel::BlinkyModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) { wait_time = 5000; }

logic::ClydeModel::ClydeModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) { wait_time = 10000; }

void logic::BlinkyModel::update(float dt, World& world) { GhostModel::update(dt); }
void logic::PinkyModel::update(float dt, World& world) { GhostModel::update(dt); }
void logic::ClydeModel::update(float dt, World& world) { GhostModel::update(dt); }