//
// Created by milo on 11/1/25.
//

#include "../include/PacmanModel.h"
#include "Event.h"

namespace logic::entity {
PacmanModel::PacmanModel(Coordinate pos, core::Direction dir, int ww, int wh) : MoveableSubject(pos, dir, ww, wh) {}

void PacmanModel::update(float dt, core::World& world) {
    core::Direction current_direction = get_direction();
    core::Direction wanted_direction = world.get_wanted_pacman_direction();
    // If pacman chooses a new direction, check if it's valid
    if (wanted_direction != current_direction) {
        Coordinate next_pos_if_turned = calculate_new_position(float(dt), wanted_direction, position_);

        // If the new direction leads to a wall-collision, don't update the position
        auto events = world.check_entity_collision(next_pos_if_turned, wanted_direction, speed_, false, dt);
        if (!utils::has_event(events, core::Event::WallCollide)) {
            set_direction(wanted_direction);
        }
    }

    Coordinate next_pos = calculate_new_position(float(dt), direction_, position_);

    // Only move when it doesn't lead to a collission
    // Else pacman will just snaps against a wall
    auto events = world.check_entity_collision(next_pos, direction_, speed_, false, dt);
    if (utils::has_event(events, core::Event::WallCollide)) {
        // snap location to middle of the position
        Coordinate new_coordinate = snap_location(position_, direction_, true);
        set_position(new_coordinate);
    } else {
        Coordinate new_pos = snap_location(next_pos, direction_, false);
        set_position(new_pos);
    }
    if (utils::has_event(events, core::Event::CoinCollected)) {
        core::Event e = core::Event::CoinCollected;
        notify(e);
    }
    if (utils::has_event(events, core::Event::FruitEaten)) {
        core::Event e = core::Event::FruitEaten;
        notify(e);
        world.begin_fear_mode();
    }
    if (utils::has_event(events, core::Event::PacmanDied)) {
        if (lives > 1) {
            // if pacman dies and he still has lives left, return every entity to their starting position
            --lives;
            world.return_center();
        } else {
            // no lives left; game ends
            core::WorldState world_state = core::WorldState::Defeated;
            world.set_world_state(world_state);
        }
    }
    if (utils::has_event(events, core::Event::GhostEaten)) {
        notify(core::Event::GhostEaten);
    }
}

float PacmanModel::get_speed() { return speed_; }

int PacmanModel::get_lives() const { return lives; }

void PacmanModel::set_lives(int live) { this->lives = live; }
} // namespace logic::entity