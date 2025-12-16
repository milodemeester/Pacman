//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYMODEL_H
#define PACMAN_ENTITYMODEL_H
#include "../Utilities/utils.h"
#include "Direction.h"
#include "Event.h"
#include <memory>
#include <vector>

enum class EntityType { Pacman, Ghost, Wall, Coin, Fruit, Undefined };

namespace logic {
class World;
class Observer;

class Subject {
protected:
    /**
     * @brief notifies all the observers of a certain event
     * @param event the event that will be passed to the observers
     */
    void notify(Event event);

    std::vector<std::weak_ptr<Observer>> observers_; // vector with all of the observers
    Coordinate position_;                            // the current position of the subject
    Coordinate starting_position_;                   // the position where the entity spawned in
    bool is_complete = false;                        // waits until location is set
    Direction direction_; // the current direction
public:
    // constructor
    explicit Subject(Coordinate pos, Direction dir) : position_(pos), direction_(dir){}

    // destructor
    virtual ~Subject() = default;

    /**
     * @brief adds a new observer to the observer vector
     * @param observer the new observer
     */
    void addObserver(const std::shared_ptr<Observer> observer) { observers_.push_back(observer); }

    /**
     * @param observer a pointer to the observer that needs to be removed
     */
    void removeObserver(std::shared_ptr<Observer> observer);

    /**
     * @brief puts the entity at their start_location
     */
    virtual void go_to_center();

    // setters
    void set_position(const Coordinate& position);
    void set_direction(Direction direction);

    // getters
    Coordinate get_position() const { return position_; }
    [[nodiscard]] virtual EntityType get_type() const { return EntityType::Undefined; }
    [[nodiscard]] Direction get_direction() const { return direction_; }
};

class MoveableSubject : public Subject {
protected:
    int world_width_;     // width of the world
    int world_height_;    // height of the world
    float speed_;        // measured in pixel/ms

    /**
     * @brief computes the new position based on the delta time
     * @param dt delta time between updates
     * @param direction the direction that will be used in the calculation
     * @param position the position that will be used in the calcilation
     * @return the new position
     */
    Coordinate calculate_new_position(float dt, Direction direction, Coordinate position);

    virtual float get_speed() = 0;

    Coordinate snap_location(Coordinate pos, Direction dir, bool both);

public:
    // constructor
    MoveableSubject(Coordinate pos, Direction dir, int world_width, int world_height)
        : world_width_(world_width), world_height_(world_height), Subject(pos, dir) {}

    /**
     * @brief pure virtual update-function that needs to be overwritten
     * @param dt the time between this update and the previous update
     * @param world the world where the MoveableSubject lives in
     */
    virtual void update(float dt, World& world) = 0;

    // setters
    void set_speed(float speed);
};
} // namespace logic

#endif // PACMAN_ENTITYMODEL_H
