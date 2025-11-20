//
// Created by milo on 11/18/25.
//

#include "../include/InkyModel.h"

#include "../include/Random.h"
#include "../include/World.h"

#include <map>
#include <algorithm> // Nodig voor std::find

logic::InkyModel::InkyModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {
    wait_time = 0;
}

void logic::InkyModel::update(float dt, World& world) {
    Direction current_direction = direction_;
    Coordinate current_position = position_; // Gebruik de huidige positie om de volgende te bepalen

    // Bepaal de volgende staat (richting en positie) op basis van de HUIDIGE staat.
    auto next_state = get_viable_state(current_direction, current_position, dt, world);

    // Werk de positie en richting in één keer bij naar de nieuwe staat.
    set_position(next_state.second);
    set_direction(next_state.first);
}

logic::Direction logic::InkyModel::get_opposite_direction(logic::Direction dir) {
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

std::vector<logic::Direction> logic::InkyModel::get_other_direction(logic::Direction dir) {
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
        return {logic::Direction::West, logic::Direction::East, logic::Direction::South};
    }
    default: {
        return {};
    }
    }
}

std::pair<logic::Direction,Coordinate> logic::InkyModel::get_viable_state(logic::Direction& current_direction, Coordinate& current_location, float dt, World& world) {
    std::vector<logic::Direction> possible_directions = {Direction::North, Direction::South, Direction::East, Direction::West};
    possible_directions.erase(std::remove(possible_directions.begin(), possible_directions.end(), get_opposite_direction(current_direction)), possible_directions.end());

    std::vector<std::pair<Direction,Coordinate>> viable_states;

    for (auto& direction_option : possible_directions) {
        // Gebruik een kopie van de positie voor elke simulatie
        Coordinate next_pos = calculate_new_position(dt, direction_option, current_location);
        if (!world.check_wall_collision(next_pos, direction_option, speed_, true)) {
            viable_states.emplace_back(direction_option, next_pos);
        }
    }

    if (viable_states.empty()) {
        // Als er geen opties zijn (doodlopende weg), draai dan om.
        Direction opposite_dir = get_opposite_direction(current_direction);
        Coordinate next_pos = calculate_new_position(dt, opposite_dir, current_location);
        return {opposite_dir, next_pos};
    }

    auto random = Random::getInstance();
    int new_state_index = random->getNumber(0, static_cast<int>(viable_states.size()) - 1);
    return viable_states[new_state_index];
}