//
// Created by milo on 11/5/25.
//

#include "../include/Subject.h"
#include "../include/Observer.h"
#include <cmath>
#include <algorithm>
#include <mutex>

namespace logic::entity {
void Subject::set_position(const Coordinate& position) {
    // If the object wasn't initialised yet, register starting pos and mark as complete
    if (!is_complete) {
        starting_position_ = position;
        is_complete = true;
    }

    // Store position
    position_ = position;

    // notify observers
    notify(Event::EntityPositionChanged);
}

void Subject::set_direction(Direction direction) {
    this->direction_ = direction;
    Event event = Event::EntityDirectionChanged;
    notify(event);
}

void Subject::removeObserver(std::shared_ptr<Observer> observer_to_remove) {
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
                                    [&](const std::weak_ptr<Observer>& weak_obs) {
                                        // Verwijder als de weak_ptr verlopen is of als het de observer is die we willen
                                        // verwijderen
                                        if (weak_obs.expired()) {
                                            return true;
                                        }
                                        std::shared_ptr<Observer> shared_obs = weak_obs.lock();
                                        return shared_obs == observer_to_remove;
                                    }),
                     observers_.end());
}
void Subject::notify(Event event) {
    if (!is_complete) {
        return;
    }

    // Delete all the expired observers
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
                                    [](const std::weak_ptr<Observer>& o) { return o.expired(); }),
                     observers_.end());

    for (auto& weak_obs : observers_) {
        if (auto shared_obs = weak_obs.lock()) { // Check if the observer still exists
            shared_obs->onNotify(*this, event);
        }
    }
}

Coordinate MoveableSubject::calculate_new_position(float dt, Direction direction, Coordinate position) {
    float epsx = 1 / float(world_width_);
    float epsy = 1 / float(world_height_);
    float increase = dt * get_speed();
    float new_x = 0;
    float new_y = 0;
    switch (direction) {
    case (Direction::North): {
        new_x = position.getX();
        new_y = position.getY() - increase * epsy;
        break;
    }
    case (Direction::East): {
        new_x = position.getX() + increase * epsx;
        new_y = position.getY();
        break;
    }
    case (Direction::South): {
        new_x = position.getX();
        new_y = position.getY() + increase * epsy;
        break;
    }
    case (Direction::West): {
        new_x = position.getX() - increase * epsx;
        new_y = position.getY();
        break;
    }
    }
    return {new_x, new_y};
}

void MoveableSubject::set_speed(float speed) { speed_ = speed; }

void Subject::go_to_center() {
    set_position(starting_position_);
}

Coordinate MoveableSubject::snap_location(Coordinate pos, Direction snap_direction, bool both) {
    Coordinate snapped_location = pos;
    if (snap_direction == Direction::East || snap_direction == Direction::West || both) {
        float world_location_y = std::round(pos.getY() * world_height_);
        snapped_location.set_coordinates(pos.getX(), world_location_y / world_height_);
    }
    if (snap_direction == Direction::North || snap_direction == Direction::South || both) {
        float world_location_x = std::round(pos.getX() * world_width_);
        snapped_location.set_coordinates(world_location_x / world_width_, pos.getY());
    }
    return snapped_location;
}
}