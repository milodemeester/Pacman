//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "../../Utilities/utils.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace representation {
class Camera;
class EntityView {
    Coordinate world_location_;

public:
    [[nodiscard]] Coordinate get_location() const { return world_location_; }
    void set_location(const Coordinate& location) { this->world_location_ = location; }

    virtual ~EntityView() = default;

    virtual void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) = 0;

    virtual void update(double dt) = 0;
};
} // namespace representation

#endif // PACMAN_ENTITYVIEW_H
