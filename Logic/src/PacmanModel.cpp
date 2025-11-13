//
// Created by milo on 11/1/25.
//

#include "../include/PacmanModel.h"

namespace logic {
class World;
}
logic::PacmanModel::PacmanModel(Coordinate pos, Direction dir) : Subject(pos, dir) {}

Coordinate logic::PacmanModel::calculate_new_position(float dt) {
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

void logic::PacmanModel::update(float dt, Direction wanted_direction, World& world) {
    Direction current_direction = get_direction();
    // Als de speler een nieuwe richting kiest, kijk of die geldig is.
    if (wanted_direction != current_direction) {
        set_direction(wanted_direction);
        Coordinate next_pos_if_turned = calculate_new_position(float(dt));

        // Als de nieuwe richting niet tot een botsing leidt, ga door met die richting.
        if (!world.check_wall_collision(next_pos_if_turned, speed)) {
            set_position(next_pos_if_turned);
            return; // Klaar voor deze frame
        }

        // Zo niet, herstel de oude richting en ga verder.
        set_direction(current_direction);
    }

    // Ga verder met de huidige (of herstelde) richting.
    Coordinate next_pos = calculate_new_position(float(dt));

    // Beweeg alleen als dit niet tot een botsing leidt.
    // Anders stopt Pacman gewoon tegen de muur.
    if (!world.check_wall_collision(next_pos, get_speed())) {
        set_position(next_pos);
        world.check_coin_collision(next_pos, speed);
    }
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