//
// Created by milo on 11/5/25.
//

#include "../include/Subject.h"
#include "../include/Observer.h"

#include <algorithm>
#include <mutex>

void logic::Subject::set_position(const Coordinate& position) {
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

void logic::MoveableSubject::set_direction(Direction direction) {
    this->direction_ = direction;
    Event event = Event::EntityDirectionChanged;
    notify(event);
}

void logic::Subject::removeObserver(std::shared_ptr<Observer> observer_to_remove) {
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
        [&](const std::weak_ptr<Observer>& weak_obs) {
            // Verwijder als de weak_ptr verlopen is of als het de observer is die we willen verwijderen
            if (weak_obs.expired()) {
                return true;
            }
            std::shared_ptr<Observer> shared_obs = weak_obs.lock();
            return shared_obs == observer_to_remove;
        }),
    observers_.end());
}
void logic::Subject::notify(Event event) {
    if (!is_complete) {
        return;
    }

    // Delete all the expired observers
    observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
        [](const std::weak_ptr<Observer>& o) {
            return o.expired();
        }),
    observers_.end());

    for (auto& weak_obs : observers_) {
        if (auto shared_obs = weak_obs.lock()) { // Check if the observer still exists
            shared_obs->onNotify(*this,event);
        }
    }
}

Coordinate logic::MoveableSubject::calculate_new_position(float dt, Direction direction, Coordinate position) {
    double epsx = 1 / double(world_width_);
    double epsy = 1 / double(world_height_);
    double increase = dt * get_speed();
    double new_x = 0;
    double new_y = 0;
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

void logic::MoveableSubject::set_speed(float speed) {
    speed_ = speed;
}

void logic::Subject::go_to_center() {
    set_position(starting_position_);
}