//
// Created by milo on 11/18/25.
//

#include "../include/InkyModel.h"

#include "../include/Random.h"
#include "../include/World.h"

#include <map>

logic::InkyModel::InkyModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) { wait_time = 0; }

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
    auto other_directions = get_other_direction(current_direction);
    std::vector<std::pair<Direction,Coordinate>> viable_states;

    // be careful not to permanently mutate direction_ while probing moves
    Direction original_direction = direction_;

    for (auto& other_direction : other_directions) {
        // temporarily set direction_ to compute a potential new position
        direction_ = other_direction;
        auto new_pos = calculate_new_position(dt);
        if (!world.check_wall_collision(new_pos, speed_, true)) {
            viable_states.emplace_back(other_direction, new_pos);
        }
    }

    // restore original direction to avoid side-effects
    direction_ = original_direction;

    // defensive: geen mogelijke richtingen gevonden => blijf daar waar je bent
    if (viable_states.empty()) {
        return {current_direction, current_location};
    }

    auto random = Random::getInstance();

    int max_index = static_cast<int>(viable_states.size()) - 1;
    int new_state = 0;
    if (max_index == 0) {
        new_state = 0;
    } else {
        new_state = random->getNumber(0, max_index);
    }
    return viable_states[new_state];
}

void logic::InkyModel::update(float dt, World& world) {
    GhostModel::update(dt);
    Direction current_direction = direction_;
    Coordinate next_position = calculate_new_position(dt);
    if (world.check_wall_collision(next_position, speed_, true)) { // TODO: intersection check in world
        auto next_state = get_viable_state(current_direction, next_position, dt, world);
        set_position(next_state.second);
        set_direction(next_state.first);
    }
    else {
        set_direction(current_direction);
        set_position(next_position);
    }
}