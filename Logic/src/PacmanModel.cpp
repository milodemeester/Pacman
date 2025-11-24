//
// Created by milo on 11/1/25.
//

#include "../include/PacmanModel.h"

namespace logic {
class World;
}
logic::PacmanModel::PacmanModel(Coordinate pos, Direction dir, int ww, int wh) : MoveableSubject(pos, dir, ww, wh) {}

void logic::PacmanModel::update(float dt, World& world) {
    Direction current_direction = get_direction();
    Direction wanted_direction = world.get_wanted_pacman_direction();
    // Als de speler een nieuwe richting kiest, kijk of die geldig is.
    if (wanted_direction != current_direction) {
        Coordinate next_pos_if_turned = calculate_new_position(float(dt), wanted_direction, position_);

        // Als de nieuwe richting niet tot een botsing leidt, ga door met die richting.
        if (!world.check_wall_collision(next_pos_if_turned, wanted_direction, speed_, false)) {
            set_position(next_pos_if_turned);
            set_direction(wanted_direction);
            return; // Klaar voor deze frame
        }
    }

    Coordinate next_pos = calculate_new_position(float(dt), direction_, position_);

    // Beweeg alleen als dit niet tot een botsing leidt.
    // Anders stopt Pacman gewoon tegen de muur.
    if (!world.check_wall_collision(next_pos, direction_, speed_, false)) {
        set_position(next_pos);
        auto event = world.check_entity_collision(next_pos, speed_);
        if (event == Event::CoinCollected) {
            Event e = Event::CoinCollected;
            notify(e);
        }
        else if (event == Event::FruitEaten) {
            Event e = Event::FruitEaten;
            notify(e);
            world.begin_fear_mode();
        }
        else if (event == Event::PacmanDied) {
            if (lives > 0) {
                --lives;
                world.reset_();
            }
            else {
                // TODO game over
            }
        }
        else if (event == Event::GhostEaten) {
            notify(Event::GhostEaten);
        }
    }
}

double logic::PacmanModel::get_speed() {
    return speed_;
}

int logic::PacmanModel::get_lives() {
    return lives;
}