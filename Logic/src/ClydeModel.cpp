//
// Created by milo on 11/20/25.
//
#include "../include/ClydeModel.h"
#include "../include/Random.h"
#include "../include/Stopwatch.h"
#include "../include/World.h"

logic::ClydeModel::ClydeModel(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {
    wait_time = 10000;
}

void logic::ClydeModel::update(float dt, World& world) {
    // Check if lyde can move or not
    GhostModel::update(dt);

    if (!waiting) { // if the ghost is not waiting
        // use the current direction and position to determine the next ones
        Direction current_direction = direction_;
        Coordinate current_position = position_;
        auto next_state = get_viable_state(current_direction, current_position, dt, world);
        set_position(next_state.second);
        set_direction(next_state.first);
    }
}

std::pair<logic::Direction,Coordinate> logic::ClydeModel::get_viable_state(Direction& current_direction, Coordinate& current_location, float dt, World& world) {
    // If clyde just came out frightened mode, turn around
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        return {reversed, final_pos};
    }

    // If clyde is not in frightened mode, turn the was_frightened_ bool off
    if (chasing_mode) {
        was_frightened_ = false;
    }

    // Determine the target of pacman
    Coordinate pac_pos = world.get_pacman_position();
    Coordinate target_location = {((pac_pos.getX()+1)/2)*world_width_, ((pac_pos.getY()+1)/2)*world_height_};

    // Using a vector because 2 directions could have the same manhatten distance
    std::vector<Direction> best_directions;
    double best_manhattan;

    if (chasing_mode) {
        // minimize the manhatten value
        best_manhattan = std::numeric_limits<double>::max();
    }
    else {
        // maximize the manhatten value
        best_manhattan = std::numeric_limits<double>::min();
    }

    // Check every possible direction except the opposite direction
    auto possible_directions = get_other_direction(get_opposite_direction(current_direction));

    for (auto& direction : possible_directions) {
        // Calculate the position if clyde takes a step into this direction
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);

        // Check if there is a wall
        if (!world.check_wall_collision(next_pos, direction, speed_, true, dt)) {
            // Change coordinate-system and compute manhatten distance
            next_pos = {((next_pos.getX()+1)/2)*world_width_, ((next_pos.getY()+1)/2)*world_height_};
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
            }
            else {
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
        int random_index = Random::getInstance()->getNumber(0, int(best_directions.size() - 1));
        chosen_direction = best_directions[random_index];
    }

    // Calculate the position that belongs to this direction // TODO: deze final pos werd al eens berekend, zoek een efficientere manier
    Coordinate final_pos = calculate_new_position(dt, chosen_direction, current_location);
    return {chosen_direction, final_pos};
}