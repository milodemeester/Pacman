//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"

#include "../include/Stopwatch.h"

logic::GhostModel::GhostModel(Coordinate pos, Direction dir): MoveableSubject(pos, dir){
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

logic::InkyModel::InkyModel(Coordinate pos, Direction dir) : GhostModel(pos, dir) {
    wait_time = 0;
}

logic::PinkyModel::PinkyModel(Coordinate pos, Direction dir) : GhostModel(pos, dir) {
    wait_time = 0;
}

logic::BlinkyModel::BlinkyModel(Coordinate pos, Direction dir) : GhostModel(pos, dir) {
    wait_time = 5000;
}

logic::ClydeModel::ClydeModel(Coordinate pos, Direction dir) : GhostModel(pos, dir) {
    wait_time = 10000;
}

void logic::InkyModel::update(float dt, World& world) {
    GhostModel::update(dt);

}
void logic::BlinkyModel::update(float dt, World& world) {
    GhostModel::update(dt);

}
void logic::PinkyModel::update(float dt, World& world) {
    GhostModel::update(dt);

}
void logic::ClydeModel::update(float dt, World& world) {
    GhostModel::update(dt);

}