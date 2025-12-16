//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_FRUITVIEW_H
#define PACMAN_FRUITVIEW_H
#include "../../Logic/include/Observer.h"
#include "EntityView.h"
#include "SpriteMap.h"
#include <memory>

namespace logic {
namespace entity {
class FruitModel;
}
} // namespace logic

namespace representation {
class Camera;

namespace view {
class FruitView : public EntityView, public logic::core::Observer {
    bool invisible = false; // is false, the fruit will not be drawn
    sf::Sprite sprite;      // the sprite that is used to represent a fruit

public:
    // constructor
    explicit FruitView(std::shared_ptr<logic::entity::FruitModel>& model, SpriteMap& sprite_map);

    /**
     * @brief function that can notify observers of an event
     * @param entity this entity
     * @param e the event that occured
     */
    void onNotify(const logic::entity::Subject& entity, logic::core::Event& e) override;

    /**
     * @brief used to draw this entity on a window
     * @param window the window that will be drawn to
     * @param cam the camera that is used to convert to pixel-coordinates
     */
    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    /**
     * @brief does nothing
     * @param dt delta-time between updates
     */
    void update(float dt) override {}

    logic::entity::EntityType get_type() const override { return logic::entity::EntityType::Fruit; }
};
} // namespace view
} // namespace representation
#endif // PACMAN_FRUITVIEW_H
