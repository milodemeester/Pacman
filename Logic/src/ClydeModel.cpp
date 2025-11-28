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
    GhostModel::update(dt);

    if (!waiting) {
        Direction current_direction = direction_;
        Coordinate current_position = position_; // Gebruik de huidige positie om de volgende te bepalen

        // Bepaal de volgende staat (richting en positie) op basis van de HUIDIGE staat.
        auto next_state = get_viable_state(current_direction, current_position, dt, world);

        // Werk de positie en richting in één keer bij naar de nieuwe staat.
        set_position(next_state.second);
        set_direction(next_state.first);
    }
}

std::pair<logic::Direction,Coordinate> logic::ClydeModel::get_viable_state(logic::Direction& current_direction, Coordinate& current_location, float dt, World& world) {
    // Als we net in frightened zijn gekomen, keer dan direct om en geef die stap terug.
    if (!chasing_mode && !was_frightened_) {
        was_frightened_ = true;
        Direction reversed = get_opposite_direction(current_direction);
        Coordinate final_pos = calculate_new_position(dt, reversed, current_location);
        return {reversed, final_pos};
    }

    // Als we niet meer frightened zijn, reset de flag zodat een toekomstige overgang weer detecteerbaar is.
    if (chasing_mode) {
        was_frightened_ = false;
    }

    // 1. Bepaal het doelwit "voor" Pac-Man
    Coordinate pac_pos = world.get_pacman_position();
    Coordinate target_location = {((pac_pos.getX()+1)/2)*world_width_, ((pac_pos.getY()+1)/2)*world_height_};

    std::vector<Direction> best_directions;
    double best_manhattan;
    if (chasing_mode) {
        best_manhattan = std::numeric_limits<double>::max();
    }
    else {
        best_manhattan = std::numeric_limits<double>::min();
    }

    // 2. Evalueer alle mogelijke richtingen (behalve omkeren)
    auto possible_directions = get_other_direction(get_opposite_direction(current_direction));

    for (auto& direction : possible_directions) {
        // Simuleer een stap in deze richting
        Coordinate next_pos = calculate_new_position(dt, direction, current_location);

        // Controleer of de zet geldig is (geen muur)
        if (!world.check_wall_collision(next_pos, direction, speed_, true, dt)) {
            next_pos = {((next_pos.getX()+1)/2)*world_width_, ((next_pos.getY()+1)/2)*world_height_};
            double mnhtn_distance = utils::compute_manhattan_distance(target_location, next_pos);

            if (chasing_mode) {
                if (mnhtn_distance < best_manhattan) {
                    // Dit is een nieuwe, betere richting.
                    best_manhattan = mnhtn_distance;
                    best_directions.clear();
                    best_directions.push_back(direction);
                } else if (mnhtn_distance == best_manhattan) {
                    // Er is een gelijkspel. Voeg deze richting toe aan de opties.
                    best_directions.push_back(direction);
                }
            }
            else {
                if (mnhtn_distance > best_manhattan) {
                    // Dit is een nieuwe, betere richting.
                    best_manhattan = mnhtn_distance;
                    best_directions.clear();
                    best_directions.push_back(direction);
                } else if (mnhtn_distance == best_manhattan) {
                    // Er is een gelijkspel. Voeg deze richting toe aan de opties.
                    best_directions.push_back(direction);
                }
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

void logic::ClydeModel::go_to_center() {
    set_position(starting_position_);
}