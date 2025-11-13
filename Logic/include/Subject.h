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
class Observer;
class Subject {
    std::vector<Observer*> observers;
protected:
    Coordinate position;
    Direction direction;
public:
    explicit Subject(Coordinate pos, Direction dir) : position(pos), direction(dir) {}
    virtual ~Subject() = default;

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& position);

    [[nodiscard]] Direction get_direction() const { return direction; }
    void set_direction(Direction direction) { this->direction = direction; }

    void addObserver(Observer* o) { observers.push_back(o); }
    void removeObserver(Observer* o);

protected:
    void notify(Event event);
};
} // namespace logic

#endif // PACMAN_ENTITYMODEL_H
