//
// Created by milo on 11/20/25.
//

#include "../include/Type2Ghost.h"
#include "../include/Random.h"
#include "../include/World.h"
#include "Event.h"
#include <map>

namespace logic::entity {
Type2Ghost::Type2Ghost(Coordinate pos, core::Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {}

void Type2Ghost::update_(float dt, core::World& world, Coordinate target) {
    if (!waiting) { // ghost is not waiting
        // use the current direction and position to determine the next ones
        core::Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto state = get_viable_state(current_direction, current_position, dt, world, target);
        set_direction(state.first);
        set_position(state.second);
    }
}

Coordinate Type2Ghost::compute_pacman_forward_pos(core::World& world, float offset) {
    Coordinate pacman_location = world.get_pacman_position();
    core::Direction pacman_direction = world.get_pacman_direction();

    float target_x = pacman_location.getX();
    float target_y = pacman_location.getY();

    switch (pacman_direction) {
    case core::Direction::East:
        target_x += offset / world.get_width();
        break;
    case core::Direction::West:
        target_x -= offset / world.get_width();
        break;
    case core::Direction::North:
        target_y -= offset / world.get_height();
        break;
    case core::Direction::South:
        target_y += offset / world.get_height();
        break;
    }
    return {target_x, target_y};
}

std::pair<core::Direction, Coordinate> Type2Ghost::get_viable_state(core::Direction& current_direction,
                                                                    Coordinate& current_location, float dt,
                                                                    core::World& world, Coordinate target_location) {
    // If the ghost just came out of frightened mode, turn around
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        core::Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        final_pos = snap_location(final_pos, reversed, false);
        return {reversed, final_pos};
    }

    // If the ghost is not in frightened mode, turn the was_frightened_ bool off
    if (chasing_mode) {
        was_frightened_ = false;
    }

    std::vector<core::Direction> best_directions;
    float best_manhattan;

    if (chasing_mode) {
        // Minimize the manhattan value
        best_manhattan = std::numeric_limits<float>::max();
    } else {
        // Maximize the manhattan value
        best_manhattan = std::numeric_limits<float>::min();
    }

    std::map<core::Direction, Coordinate> dir_cor_combis;
    std::vector<core::Direction> viable_directions;

    // Check all 4 directions
    const std::vector<core::Direction> all_directions = {
        core::Direction::North, core::Direction::East, core::Direction::South, core::Direction::West};

    for (auto direction : all_directions) {
        // Calculate the position if the ghost takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);
        snap_location(next_pos, direction, false);

        // Save this position for later
        dir_cor_combis[direction] = next_pos;

        // Check if there is a wall
        auto events = world.check_entity_collision(next_pos, direction, speed_, true, dt);
        if (!utils::has_event(events, core::Event::WallCollide)) {
            viable_directions.push_back(direction);
        }
    }

    // Exclude the opposite direction unless it's the only option
    core::Direction opposite_direction = get_opposite_direction(current_direction);
    if (viable_directions.size() > 1) {
        viable_directions.erase(std::remove(viable_directions.begin(), viable_directions.end(), opposite_direction),
                                viable_directions.end());
    }

    for (auto direction : viable_directions) {
        Coordinate next_pos = dir_cor_combis[direction];
        float mnhtn_distance = utils::compute_manhattan_distance(target_location, next_pos);

        if (chasing_mode) {
            // Minimize the manhattan value
            if (mnhtn_distance < best_manhattan) {
                best_manhattan = mnhtn_distance;
                best_directions.clear();
                best_directions.push_back(direction);
            } else if (mnhtn_distance == best_manhattan) {
                best_directions.push_back(direction);
            }
        } else {
            // Maximize the manhattan value
            if (mnhtn_distance > best_manhattan) {
                best_manhattan = mnhtn_distance;
                best_directions.clear();
                best_directions.push_back(direction);
            } else if (mnhtn_distance == best_manhattan) {
                best_directions.push_back(direction);
            }
        }
    }

    // Choose the best direction
    core::Direction chosen_direction;
    if (best_directions.empty()) {
        // This can happen if all viable directions are equally bad, or if there are no viable directions.
        // As a fallback, just pick one of the viable ones. If none, turn around.
        if (!viable_directions.empty()) {
            chosen_direction = viable_directions[0];
        } else {
            chosen_direction = get_opposite_direction(current_direction);
        }
    } else {
        // Choose a random direction among the best options
        int random_index = core::Random::getInstance()->getNumber(0, best_directions.size() - 1);
        chosen_direction = best_directions[random_index];
    }

    return {chosen_direction, dir_cor_combis[chosen_direction]};
}

void Type2Ghost::go_to_center() {
    Subject::go_to_center();
    in_box = true;
}
} // namespace logic::entity