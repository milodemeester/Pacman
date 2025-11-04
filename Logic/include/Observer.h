//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

class Entity;

class IView {
public:
    virtual ~IView() = default;
    virtual void onEntityUpdated(const Entity& entity);
};

#endif // PACMAN_OBSERVER_H
