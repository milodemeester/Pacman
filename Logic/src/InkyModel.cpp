//
// Created by milo on 11/18/25.
//

#include "../include/InkyModel.h"

#include "../include/Random.h"
#include "../include/Stopwatch.h"
#include "../include/World.h"

#include <algorithm>
#include <map>

logic::InkyModel::InkyModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {
    wait_time = 0;
}

void logic::InkyModel::update(float dt, World& world) {
    // Check if inky can move or not
    GhostModel::update(dt);

    if (!waiting) {
        // use the current direction and position to determine the next ones
        Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto next_state = get_viable_state(current_direction, current_position, dt, world);
        set_position(next_state.second);
        set_direction(next_state.first);
    }
}

std::pair<logic::Direction, Coordinate> logic::InkyModel::get_viable_state(Direction& current_direction,
                                                                           Coordinate& current_location, float dt,
                                                                           World& world) {
    // If inky just came out frightened mode, turn around
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        return {reversed, final_pos};
    }

    // If inky is not in frightened mode, turn the was_frightened_ bool off
    if (chasing_mode) {
        was_frightened_ = false;
    }

    // Check for every possible direction if it's a viable direction
    std::vector<logic::Direction> possible_directions = {Direction::North, Direction::South, Direction::East,
                                                         Direction::West};
    possible_directions.erase(
        std::remove(possible_directions.begin(), possible_directions.end(), get_opposite_direction(current_direction)),
        possible_directions.end());

    std::vector<std::pair<Direction, Coordinate>> viable_states;

    for (auto& direction_option : possible_directions) {
        // Calculate the position if inky takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction_option, current_location);
        auto events = world.check_entity_collision(next_pos, direction_option, speed_, true, dt);
        if (!utils::has_event(events, Event::WallCollide)) {
            viable_states.emplace_back(direction_option, next_pos);
        }
    }

    if (viable_states.empty()) {
        // Dead end, turn around
        Direction opposite_dir = get_opposite_direction(current_direction);
        Coordinate next_pos = calculate_new_position(dt, opposite_dir, current_location);
        return {opposite_dir, next_pos};
    }

    // Choose random direction out of all the viable diections
    auto random = Random::getInstance();
    int new_state_index = random->getNumber(0, static_cast<int>(viable_states.size()) - 1);
    return viable_states[new_state_index];
}