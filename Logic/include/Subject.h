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

class Subject : public std::enable_shared_from_this<Subject> {
    std::vector<Observer*> observers_; // vector with all of the observers
protected:
    /**
     * @brief notifies all the observers of a certain event
     * @param event the event that will be passed to the observers
     */
    void notify(Event event);

    Coordinate position_; // the current position of the subject
    Coordinate starting_position_; // the position where the entity spawned in
    bool is_complete = false; // waits until location is set
public:
    // constructor
    explicit Subject(Coordinate pos) : position_(pos) {}

    // destructor
    virtual ~Subject() = default;

    /**
     * @param position new position of the Subject
     */
    void set_position(const Coordinate& position);

    /**
     * @return the current position of the subject
     */
    Coordinate get_position() const { return position_; }

    /**
     * @brief adds a new observer to the observer vector
     * @param observer the new observer
     */
    void addObserver(Observer* observer) { observers_.push_back(observer); }

    /**
     * @param observer a pointer to the observer that needs to be removed
     */
    void removeObserver(Observer* observer);

    virtual void reset_();
};

class MoveableSubject : public Subject {
protected:
    int world_width_; // width of the world
    int world_height_; // height of the world
    Direction direction_; // the current direction

    /**
     * @brief computes the new position based on the delta time
     * @param dt delta time between updates
     * @param direction the direction that will be used in the calculation
     * @param position the position that will be used in the calcilation
     * @return the new position
     */
    Coordinate calculate_new_position(float dt, logic::Direction direction, Coordinate position);

    virtual double get_speed() = 0;

public:
    // constructor
    MoveableSubject(Coordinate pos, Direction dir, int world_width, int world_height) : world_width_(world_width),
        world_height_(world_height),
        Subject(pos),
        direction_(dir) {}

    /**
     * @brief changes the direction and notifies all the observers
     * @param direction the new direction of the subject
     */
    void set_direction(Direction direction);

    /**
     * @return the current direction
     */
    Direction get_direction() const { return direction_; }

    /**
     * @brief pure virtual update-function that needs to be overwritten
     * @param dt the time between this update and the previous update
     * @param world the world where the MoveableSubject lives in
     */
    virtual void update(float dt, World& world) = 0;
};
} // namespace logic

#endif // PACMAN_ENTITYMODEL_H
