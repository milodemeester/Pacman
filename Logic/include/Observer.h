//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H
#include "Event.h"
#include <memory>

namespace logic {
namespace entity {
class Subject;
}

namespace core {
class Observer {
public:
    // destructor
    virtual ~Observer() = default;

    /**
     * @brief pure virtual function that handles an event
     * @param entity the entity that the event is sent in by
     * @param e the type of event
     */
    virtual void onNotify(const entity::Subject& entity, Event& e) = 0;
};
} // namespace core
} // namespace logic

#endif // PACMAN_OBSERVER_H
