//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H
#include "../../Logic/include/Observer.h"
#include "EntityView.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

namespace logic::entity {
class CoinModel;
}

namespace representation {
class SpriteMap;
class CoinView : public EntityView, public logic::Observer {
    bool invisible = false; // is false, the coin will not be drawn
    sf::Sprite sprite;      // the sprite that is used to represent a coin

public:
    // constructor
    explicit CoinView(std::shared_ptr<logic::entity::CoinModel> model, SpriteMap& sprite_map);

    /**
     * @brief function that can notify observers of an event
     * @param entity this entity
     * @param e the event that occured
     */
    void onNotify(const logic::entity::Subject& entity, logic::Event& e) override;

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

    logic::entity::EntityType get_type() const override { return logic::entity::EntityType::Coin;}
};
} // namespace representation
#endif // PACMAN_COINVIEW_H
