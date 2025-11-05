//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYMODEL_H
#define PACMAN_ENTITYMODEL_H
#include "Event.h"
#include <memory>
#include <vector>

namespace logic {
class Observer;
class Subject {
    std::vector<Observer*> observers;

public:
    Subject() = default;
    virtual ~Subject() = default;

    void addObserver(Observer* o) { observers.push_back(o); }
    void removeObserver(Observer* o);

protected:
    void notify(Event event);
};
} // namespace logic

#endif // PACMAN_ENTITYMODEL_H
