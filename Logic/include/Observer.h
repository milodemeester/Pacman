//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H
#include "Event.h"

namespace logic {
class Subject;
}

namespace logic {
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const Subject& entity, Event& e) = 0;
};
} // namespace logic

#endif // PACMAN_OBSERVER_H
