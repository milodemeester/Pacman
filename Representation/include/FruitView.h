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
class FruitModel;
}

namespace representation {
class Camera;

class FruitView : public EntityView, public logic::Observer {
    bool invisible = false; // is false, the fruit will not be drawn
    sf::Sprite sprite;      // the sprite that is used to represent a fruit

public:
    // constructor
    explicit FruitView(std::shared_ptr<logic::FruitModel>& model, representation::SpriteMap& sprite_map);

    /**
     * @brief function that can notify observers of an event
     * @param entity this entity
     * @param e the event that occured
     */
    void onNotify(const logic::Subject& entity, logic::Event& e) override;

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
};
} // namespace representation
#endif // PACMAN_FRUITVIEW_H
