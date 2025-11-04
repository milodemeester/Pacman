//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H
#include "../../Utilities/utils.h"
#include "Observer.h"
#include <memory>
#include <vector>

class Entity {
    Coordinate bottom_right;
    Coordinate top_left;
    enum Direction { N = 'N', E = 'E', S = 'S', W = 'W' };
    Direction dir = N;
    //double speed; // measured in pixels/second
    std::vector<std::weak_ptr<IView>> observers;

protected:
    void notifyObservers() const {
        for (auto &w : observers) {
            if (std::shared_ptr<IView> v = w.lock()) v->onEntityUpdated(*this);
        }
    }

public:
    virtual ~Entity() = default;
    // update
    virtual void update(float dt) = 0;
    Entity() = default;
    [[nodiscard]] Coordinate get_bottom_right() const { return bottom_right; }
    void set_bottom_right(const Coordinate& bottom_right) { this->bottom_right = bottom_right; }
    [[nodiscard]] Coordinate get_top_left() const { return top_left; }
    void set_top_left(const Coordinate& top_left) { this->top_left = top_left; }
    [[nodiscard]] Direction get_direction() const { return dir; }
    void set_dir(Direction dir) { this->dir = dir; }
    [[nodiscard]] std::vector<std::weak_ptr<IView>> get_observers() const { return observers; }
    void set_observers(const std::vector<std::weak_ptr<IView>>& observers) { this->observers = observers; }
};

#endif //PACMAN_ENTITY_H
