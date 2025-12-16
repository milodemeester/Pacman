//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H
#include "../../Logic/include/Observer.h"
#include "../../Logic/include/WallModel.h"
#include "EntityView.h"
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <map>

enum class WallSpriteState { Wall };

namespace representation {
class SpriteMap;
class WallView : public EntityView, public logic::core::Observer {
    std::map<WallSpriteState, sf::Sprite> m_sprites_;
    bool invisible_;

public:
    // constructor
    explicit WallView(const std::shared_ptr<logic::entity::WallModel>& model, SpriteMap& sprite_map, bool invisible);

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

    logic::entity::EntityType get_type() const override { return logic::entity::EntityType::Wall;}
};
} // namespace representation

#endif // PACMAN_WALLVIEW_H
