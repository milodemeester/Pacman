//
// Created by milo on 11/20/25.
//

#include "../include/Type2Ghost.h"
#include "../include/World.h"
#include "../include/Random.h"

logic::Type2Ghost::Type2Ghost(Coordinate pos, Direction dir, int ww, int wh) : GhostModel(pos, dir, ww, wh) {}

void logic::Type2Ghost::update(float dt, World& world) {
    GhostModel::update(dt);
    if (!waiting) {
        // Bepaal de volgende staat en werk de position en direction bij.
        auto state = get_viable_state(direction_, position_, dt, world);
        set_direction(state.first);
        set_position(state.second);
    }
}


Coordinate compute_pacman_forward_pos(logic::World& world) {
    Coordinate pacman_location = world.get_pacman_position();
    logic::Direction pacman_direction = world.get_pacman_direction();

    float target_x = ((pacman_location.getX()+1)/2)*world.get_width();
    float target_y = ((pacman_location.getY()+1)/2)*world.get_height();

    // De "4" is de offset. Deze moet misschien worden aangepast aan de schaal van je wereld.
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
    }
    else if (target_x > world.get_width()) {
        target_x = world.get_width();
    }
    if (target_y < 0) {
        target_y = 0;
    }
    else if (target_y > world.get_height()) {
        target_y = world.get_height();
    }
    return {target_x, target_y};
}

double compute_manhattan_distance(Coordinate& pos1, Coordinate& pos2) {
    double distance = std::abs(pos1.getX() - pos2.getX()) + std::abs(pos1.getY() - pos2.getY());
    return distance;
}

std::pair<logic::Direction,Coordinate> logic::Type2Ghost::get_viable_state(logic::Direction& current_direction, Coordinate& current_location, float dt, World& world) {
    // 1. Bepaal het doelwit "voor" Pac-Man
    Coordinate target_location = compute_pacman_forward_pos(world);

    std::vector<Direction> best_directions;
    double smallest_manhattan = std::numeric_limits<double>::max();

    // 2. Evalueer alle mogelijke richtingen (behalve omkeren)
    auto possible_directions = get_other_direction(get_opposite_direction(current_direction));

    for (auto& direction : possible_directions) {
        // Simuleer een stap in deze richting
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);

        // Controleer of de zet geldig is (geen muur)
        if (!world.check_wall_collision(next_pos, direction, speed_, true)) {
            next_pos = {((next_pos.getX()+1)/2)*world_width_, ((next_pos.getY()+1)/2)*world_height_};
            double mnhtn_distance = compute_manhattan_distance(target_location, next_pos);

            if (mnhtn_distance < smallest_manhattan) {
                // Dit is een nieuwe, betere richting.
                smallest_manhattan = mnhtn_distance;
                best_directions.clear();
                best_directions.push_back(direction);
            } else if (mnhtn_distance == smallest_manhattan) {
                // Er is een gelijkspel. Voeg deze richting toe aan de opties.
                best_directions.push_back(direction);
            }
        }
    }

    // 3. Kies de beste richting
    Direction chosen_direction;
    if (best_directions.empty()) {
        // Gevangen in een doodlopende weg, dus omkeren is de enige optie.
        chosen_direction = get_opposite_direction(current_direction);
    } else {
        // Kies willekeurig uit de beste opties (als er 1 is, wordt die gekozen)
        int random_index = Random::getInstance()->getNumber(0, static_cast<int>(best_directions.size()) - 1);
        chosen_direction = best_directions[random_index];
    }

    // 4. Bereken de uiteindelijke nieuwe positie en retourneer de staat.
    Coordinate final_pos = calculate_new_position(dt, chosen_direction, current_location);
    return {chosen_direction, final_pos};
}
