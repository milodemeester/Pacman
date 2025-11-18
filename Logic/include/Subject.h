//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYMODEL_H
#define PACMAN_ENTITYMODEL_H
#include "../../Utilities/utils.h"
#include "Direction.h"
#include "Event.h"
#include <memory>
#include <vector>

namespace logic {
class World;
class Observer;

class Subject {
    std::vector<Observer*> observers_;

protected:
    Coordinate position_;

public:
    explicit Subject(Coordinate pos) : position_(pos) {}
    virtual ~Subject() = default;

    void set_position(const Coordinate& position);
    Coordinate get_position() const { return position_; }

    void addObserver(Observer* o) { observers_.push_back(o); }
    void removeObserver(Observer* o);

protected:
    void notify(Event event);
};

class MoveableSubject : public Subject {
protected:
    double speed_ = 0.01; // measured in pixel/ms
    int world_width_;
    int world_height_;
    Direction direction_;

    /**
     *@brief Gives back the new coordinate to change location
     *@param dt delta time between updates
     */
    Coordinate calculate_new_position(float dt);

public:
    MoveableSubject(Coordinate pos, Direction dir, int world_width, int world_height) : world_width_(world_width),
        world_height_(world_height),
        Subject(pos),
        direction_(dir) {}

    void set_direction(Direction direction);
    Direction get_direction() const { return direction_; }

    virtual void update(float dt, World& world) = 0;
};
} // namespace logic

#endif // PACMAN_ENTITYMODEL_H
