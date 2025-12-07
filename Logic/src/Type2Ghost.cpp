//
// Created by milo on 11/20/25.
//

#include "../include/Type2Ghost.h"
#include "../include/Random.h"
#include "../include/World.h"
#include <map>

logic::Type2Ghost::Type2Ghost(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {}

void logic::Type2Ghost::update_(float dt, World& world, Coordinate target) {
    // Check if the ghost can move or not
    update(dt);

    if (!waiting) { // ghost is not waiting
        // use the current direction and position to determine the next ones
        Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto state = get_viable_state(current_direction, current_position, dt, world, target);
        set_direction(state.first);
        set_position(state.second);
    }
}

Coordinate logic::Type2Ghost::compute_pacman_forward_pos(World& world, float offset) {
    Coordinate pacman_location = world.get_pacman_position();
    Direction pacman_direction = world.get_pacman_direction();

    float target_x = pacman_location.getX();
    float target_y = pacman_location.getY();

    switch (pacman_direction) {
    case Direction::East:
        target_x += offset/world.get_width();
        break;
    case Direction::West:
        target_x -= offset/world.get_width();
        break;
    case Direction::North:
        target_y -= offset/world.get_height();
        break;
    case Direction::South:
        target_y += offset/world.get_height();
        break;
    }
    return {target_x, target_y};
}

std::pair<logic::Direction, Coordinate> logic::Type2Ghost::get_viable_state(Direction& current_direction,
                                                                            Coordinate& current_location, float dt,
                                                                            World& world, Coordinate target_location) {
    // If the ghost just came out frightened mode, turn around
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        return {reversed, final_pos};
    }

    // If the ghost is not in frightened mode, turn the was_frightened_ bool off
    if (chasing_mode) {
        was_frightened_ = false;
    }
    // Using a vector because 2 directions could have the same manhatten distance
    std::vector<Direction> best_directions;
    double best_manhattan;

    if (chasing_mode) {
        // minimize the manhatten value
        best_manhattan = std::numeric_limits<double>::max();
    } else {
        // maximize the manhatten value
        best_manhattan = std::numeric_limits<double>::min();
    }

    // Check every possible direction except the opposite direction
    auto possible_directions = {Direction::East, Direction::North, Direction::South, Direction::West};

    std::map<Direction, Coordinate> dir_cor_combis;

    for (auto direction : possible_directions) {
        // Calculate the position if clyde takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);

        // Save this position for later
        dir_cor_combis[direction] = next_pos;

        // Check if there is a wall
        auto events = world.check_entity_collision(next_pos, direction, speed_, true, dt);
        if (!utils::has_event(events, Event::WallCollide)) {
            double mnhtn_distance = utils::compute_manhattan_distance(target_location, next_pos);

            if (chasing_mode) {
                // minimize the manhatten value
                if (mnhtn_distance < best_manhattan) {
                    // This direction is better than the other directions up to this point
                    best_manhattan = mnhtn_distance;
                    best_directions.clear();
                    best_directions.push_back(direction);
                } else if (mnhtn_distance == best_manhattan) {
                    // This direction is equally good as another direction
                    best_directions.push_back(direction);
                }
            } else {
                // maximize the manhatten value
                if (mnhtn_distance > best_manhattan) {
                    // This direction is better than the other directions up to this point
                    best_manhattan = mnhtn_distance;
                    best_directions.clear();
                    best_directions.push_back(direction);
                } else if (mnhtn_distance == best_manhattan) {
                    // This direction is equally good as another direction
                    best_directions.push_back(direction);
                }
            }
        }
    }

    // Choose the best direction
    Direction chosen_direction;
    if (best_directions.empty()) { // no viable directions, turn around
        chosen_direction = get_opposite_direction(current_direction);
    }
    else {
        // Choose a random direction
        int random_index = Random::getInstance()->getNumber(0, static_cast<int>(best_directions.size()) - 1);
        chosen_direction = best_directions[random_index];
    }
    auto location = calculate_new_position(dt, chosen_direction, current_location);

    return {chosen_direction, location};
}