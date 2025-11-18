//
// Created by milo on 11/1/25.
//

#include "../include/GhostModel.h"

logic::GhostModel::GhostModel(Coordinate pos, Direction dir, GhostType ghost_type): Subject(pos, dir), type_(ghost_type) {
    switch (type_) {
    case (GhostType::Blinky) : {
        chasing_mode = true;
        break;
    }
    case (GhostType::Inky) : {
        chasing_mode = true;
        break;
    }
    case (GhostType::Pinky) : {
        wait_time = 5000; // 5 seconds
        break;
    }
    case (GhostType::Clyde) : {
        wait_time = 10000;
        break;
    }
    }
}

void logic::GhostModel::update(float dt) {
    switch (type_) {
        case (GhostType::Blinky) : {
        }
        case (GhostType::Inky) : {
        }
        case (GhostType::Pinky) : {
        }
        case (GhostType::Clyde) : {
        }
    }
}