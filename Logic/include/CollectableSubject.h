//
// Created by milo on 11/23/25.
//

#ifndef PACMAN_COLLECTABLESUBJECT_H
#define PACMAN_COLLECTABLESUBJECT_H
#include "Subject.h"

namespace logic{

class CollectableSubject : public Subject {
public:
    // constructor
    CollectableSubject(Coordinate position) : Subject(position) {}

    /**
     * @brief this function notifies observers that it is destructed
     */
    virtual void destruct();
};

} // namespace logic

#endif // PACMAN_COLLECTABLESUBJECT_H
