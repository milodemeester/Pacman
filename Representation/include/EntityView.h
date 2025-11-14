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
public:
    [[nodiscard]] Coordinate get_location() const { return location; }
    void set_location(const Coordinate& location) { this->location = location; }

private:
    Coordinate location;
public:
    virtual ~EntityView() = default;

    virtual void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) = 0;

    virtual void update(double dt) = 0;
};
} // namespace representation

#endif // PACMAN_ENTITYVIEW_H
