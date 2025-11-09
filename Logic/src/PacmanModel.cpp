//
// Created by milo on 11/1/25.
//

#include "../include/PacmanModel.h"

logic::PacmanModel::PacmanModel(Coordinate pos, Direction dir) : Subject(pos, dir) {}

Coordinate logic::PacmanModel::update(float dt) {
    double epsx = 1/double(world_width);
    double epsy = 1/double(world_height);
    double increase = dt * speed;
    Coordinate pos = get_position();
    Direction dir = get_direction();
    double new_x = 0;
    double new_y = 0;
    switch (dir) {
        case (Direction::North) : {
            new_x = pos.getX();
            new_y = pos.getY() - increase*epsy;
            break;
        }
        case (Direction::East) : {
            new_x = pos.getX() + increase*epsx;
            new_y = pos.getY();
            break;
        }
        case (Direction::South) : {
            new_x = pos.getX();
            new_y = pos.getY() + increase*epsy;
            break;
        }
        case (Direction::West) : {
            new_x = pos.getX() - increase*epsx;
            new_y = pos.getY();
            break;
        }
    }
    return {new_x, new_y};
}

void logic::PacmanModel::set_direction(Direction dir) {
    direction = dir;
    Event event = Event::EntityDirectionChanged;
    notify(event);
}

void logic::PacmanModel::set_position(const Coordinate& pos) {
    position = pos;
    Event event = Event::EntityPositionChanged;
    notify(event);
}