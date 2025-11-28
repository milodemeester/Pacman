//
// Created by milo on 11/5/25.
//

#include "../include/Subject.h"
#include "../include/Observer.h"

void logic::Subject::set_position(const Coordinate& position) {
    this->position_ = position;
    if (!is_complete) {
        starting_position_ = position;
        is_complete = true;
    }
    Event event = Event::EntityPositionChanged;
    notify(event);
}

void logic::MoveableSubject::set_direction(Direction direction) {
    this->direction_ = direction;
    Event event = Event::EntityDirectionChanged;
    notify(event);
}

void logic::Subject::removeObserver(Observer* o) {
    for (int i = 0; i < observers_.size(); i++) {
        if (observers_[i] == o) {
            observers_.erase(observers_.begin() + i);
        }
    }
}

void logic::Subject::notify(Event event) {
    for (auto observer : observers_) {
        observer->onNotify(*this, event);
    }
}

Coordinate logic::MoveableSubject::calculate_new_position(float dt, logic::Direction direction, Coordinate position) {
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