//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "../../Logic/Utilities/utils.h"
#include "Subject.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

namespace representation {
class Camera;
class EntityView {
protected:
    Coordinate world_location_; // the world location of the entity
public:
    // destructor
    virtual ~EntityView() = default;

    /**
     * @brief used to draw this entity on a window
     * @param window the window that will be drawn to
     * @param cam the camera that is used to convert to pixel-coordinates
     */
    virtual void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) = 0;

    /**
     * @brief update something
     * @param dt delta time between updates
     */
    virtual void update(float dt) = 0;

    // getters
    [[nodiscard]] Coordinate get_location() const { return world_location_; }
    [[nodiscard]] virtual EntityType get_type() const { return EntityType::Undefined; }

    // setters
    void set_location(const Coordinate& location) { this->world_location_ = location; }
};
} // namespace representation

#endif // PACMAN_ENTITYVIEW_H
