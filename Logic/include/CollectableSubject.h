//
// Created by milo on 11/23/25.
//

#ifndef PACMAN_COLLECTABLESUBJECT_H
#define PACMAN_COLLECTABLESUBJECT_H
#include "Subject.h"

namespace logic::entity {

class CollectableSubject : public Subject {
public:
    // constructor
    explicit CollectableSubject(Coordinate position) : Subject(position, core::Direction::NoDirection) {}

    /**
     * @brief this function notifies observers that it is destructed
     */
    virtual void destruct();
};

} // namespace logic

#endif // PACMAN_COLLECTABLESUBJECT_H
