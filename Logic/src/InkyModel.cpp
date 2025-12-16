//
// Created by milo on 11/18/25.
//

#include "../include/InkyModel.h"
#include "../include/Random.h"
#include "../include/Stopwatch.h"
#include "../include/World.h"
#include "Event.h"
#include <algorithm>
#include <map>

namespace logic::entity {
InkyModel::InkyModel(Coordinate pos, core::Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {
    wait_time = 0;
}

void InkyModel::update(float dt, core::World& world) {
    // Check if inky can move or not
    GhostModel::update(dt, world);

    if (!waiting) {
        // use the current direction and position to determine the next ones
        core::Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto next_state = get_viable_state(current_direction, current_position, dt, world);
        set_position(next_state.second);
        set_direction(next_state.first);
    }
}

std::pair<core::Direction, Coordinate> InkyModel::get_viable_state(core::Direction& current_direction,
                                                                           Coordinate& current_location, float dt,
                                                                           core::World& world) {
    // If inky just came out frightened mode, turn around
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        core::Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        final_pos = snap_location(final_pos, reversed, false);
        return {reversed, final_pos};
    }

    // If inky is not in frightened mode, turn the was_frightened_ bool off
    if (chasing_mode) {
        was_frightened_ = false;
    }

    // Check for every possible direction if it's a viable direction
    std::vector<core::Direction> possible_directions = {core::Direction::North, core::Direction::South, core::Direction::East,
                                                         core::Direction::West};
    possible_directions.erase(
        std::remove(possible_directions.begin(), possible_directions.end(), get_opposite_direction(current_direction)),
        possible_directions.end());

    std::vector<std::pair<core::Direction, Coordinate>> viable_states;

    for (auto& direction_option : possible_directions) {
        // Calculate the position if inky takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction_option, current_location);
        auto events = world.check_entity_collision(next_pos, direction_option, speed_, true, dt);
        if (!utils::has_event(events, core::Event::WallCollide)) {
            Coordinate new_coordinate = snap_location(next_pos, direction_option,  false);
            viable_states.emplace_back(direction_option, new_coordinate);
        }
    }

    if (viable_states.empty()) {
        // Dead end, turn around
        core::Direction opposite_dir = get_opposite_direction(current_direction);
        Coordinate next_pos = calculate_new_position(dt, opposite_dir, current_location);
        // Geef de 'opposite_dir' mee aan snap_location
        Coordinate new_coordinate = snap_location(next_pos, opposite_dir, false);
        return {opposite_dir, new_coordinate};
    }

    // Choose random direction out of all the viable diections
    auto random = core::Random::getInstance();
    int new_state_index = random->getNumber(0, viable_states.size() - 1);
    return viable_states[new_state_index];
}
}