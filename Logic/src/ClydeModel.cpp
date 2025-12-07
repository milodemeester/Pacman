//
// Created by milo on 11/20/25.
//
#include "../include/ClydeModel.h"
#include "../include/World.h"

logic::ClydeModel::ClydeModel(Coordinate pos, Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 10000; // 10 seconden voor clyde
}

void logic::ClydeModel::update(float dt, World& world) {
    // clyde is the fourth ghost, chases pacman location
    Coordinate target = world.get_pacman_position();
    update_(dt, world, target);
}