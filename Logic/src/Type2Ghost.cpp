//
// Created by milo on 11/20/25.
//

#include "../include/Type2Ghost.h"
#include "../include/Random.h"
#include "../include/World.h"
#include <map>

logic::Type2Ghost::Type2Ghost(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {}

void logic::Type2Ghost::update(float dt, World& world) {
    // Check if the ghost can move or not
    GhostModel::update(dt);

    if (!waiting) { // ghost is not waiting
        // use the current direction and position to determine the next ones
        Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto state = get_viable_state(current_direction, current_position, dt, world);
        set_direction(state.first);
        set_position(state.second);
    }
}

Coordinate compute_pacman_forward_pos(logic::World& world) {
    Coordinate pacman_location = world.get_pacman_position();
    logic::Direction pacman_direction = world.get_pacman_direction();

    float target_x = ((pacman_location.getX() + 1) / 2) * world.get_width();
    float target_y = ((pacman_location.getY() + 1) / 2) * world.get_height();

    // The seconds type of ghost calculates manhatten distance to 4 blocks in front of pacman
    const float offset = 4.0f;

    switch (pacman_direction) {
    case logic::Direction::East:
        target_x += offset;
        break;
    case logic::Direction::West:
        target_x -= offset;
        break;
    case logic::Direction::North:
        target_y -= offset;
        break;
    case logic::Direction::South:
        target_y += offset;
        break;
    }
    if (target_x < 0) {
        target_x = 0;
    } else if (target_x > world.get_width()) {
        target_x = world.get_width();
    }
    if (target_y < 0) {
        target_y = 0;
    } else if (target_y > world.get_height()) {
        target_y = world.get_height();
    }
    return {target_x, target_y};
}

std::pair<logic::Direction, Coordinate> logic::Type2Ghost::get_viable_state(Direction& current_direction,
                                                                            Coordinate& current_location, float dt,
                                                                            World& world) {
    // TODO: deze is zeer gelijk aan die van ClydeModel, zorg voor een manier om duplicatie te vermijden
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
    // Determine the target in front of pacman
    Coordinate target_location = compute_pacman_forward_pos(world);

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
    auto possible_directions = get_other_direction(get_opposite_direction(current_direction));

    std::map<Direction, Coordinate> dir_cor_combis;

    for (auto& direction : possible_directions) {
        // Calculate the position if clyde takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);

        // Save this position for later
        dir_cor_combis[direction] = next_pos;

        // Check if there is a wall
        if (!world.check_wall_collision(next_pos, direction, speed_, true, dt)) {
            // Change coordinate-system and compute manhatten distance
            next_pos = {((next_pos.getX() + 1) / 2) * world_width_, ((next_pos.getY() + 1) / 2) * world_height_};
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
    if (best_directions.empty()) {
        // Dead end, turn around
        chosen_direction = get_opposite_direction(current_direction);
    } else {
        // Choose a random direction
        int random_index = Random::getInstance()->getNumber(0, static_cast<int>(best_directions.size()) - 1);
        chosen_direction = best_directions[random_index];
    }

    auto location = calculate_new_position(dt, chosen_direction, current_location);

    return {chosen_direction, location};
}