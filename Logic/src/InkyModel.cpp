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
    }
}

std::pair<logic::Direction,Coordinate> logic::InkyModel::get_viable_state(logic::Direction& current_direction, Coordinate& current_location, float dt, World& world) {
    int amount_of_viable_directions = 0;
    auto other_directions = get_other_direction(current_direction);
    std::vector<std::pair<Direction,Coordinate>> viable_states;
    for (auto& other_direction : other_directions) {
        direction_ = other_direction;
        auto new_pos = calculate_new_position(dt);
        if (!world.check_wall_collision(new_pos, speed_, true)) {
            std::pair<Direction,Coordinate> p(other_direction, new_pos);
            viable_states.push_back(p);
            amount_of_viable_directions++;
        }
    }
    auto random = Random::getInstance();
    int new_state = random->getNumber(0, amount_of_viable_directions);
    return viable_states[new_state];
}

void logic::InkyModel::update(float dt, World& world) {
    GhostModel::update(dt);
    Direction current_direction = direction_;
    Coordinate next_position = calculate_new_position(dt);
    if (world.check_wall_collision(next_position, speed_, true)) {
        auto next_state = get_viable_state(current_direction, next_position, dt, world);
        set_position(next_state.second);
        set_direction(next_state.first);
    }
    else {
        direction_ = current_direction;
        set_position(next_position);
    }
}