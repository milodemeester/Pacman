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
        set_direction(wanted_direction);
        Coordinate next_pos_if_turned = calculate_new_position(float(dt));

        // Als de nieuwe richting niet tot een botsing leidt, ga door met die richting.
        if (!world.check_wall_collision(next_pos_if_turned, direction_, speed_, false)) {
            set_position(next_pos_if_turned);
            return; // Klaar voor deze frame
        }

        // Zo niet, herstel de oude richting en ga verder.
        set_direction(current_direction);
    }

    // Ga verder met de huidige (of herstelde) richting.
    Coordinate next_pos = calculate_new_position(float(dt));

    // Beweeg alleen als dit niet tot een botsing leidt.
    // Anders stopt Pacman gewoon tegen de muur.
    if (!world.check_wall_collision(next_pos, direction_, speed_, false)) {
        set_position(next_pos);
        if (world.check_coin_collision(next_pos, speed_)) {
            Event e = Event::CoinCollected;
            notify(e);
        }
    }
}