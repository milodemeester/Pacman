//
// Created by milo on 11/4/25.
//

#include "../include/WallModel.h"

void logic::WallModel::set_position(const Coordinate& pos) {
    this->position = pos;
    Event e = Event::EntityPositionChanged;
    notify(e);
}