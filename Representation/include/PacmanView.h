//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H
#include "../../Logic/Utilities/utils.h"
#include "../../Logic/include/Observer.h"
#include "../../Logic/include/PacmanModel.h"
#include "EntityView.h"
#include "SpriteMap.h"

#include <map>
#include <memory>

namespace logic::entity {
class PacmanModel;
}

namespace representation {
class Camera;

namespace view {
class PacmanView : public EntityView, public logic::core::Observer {
    std::map<logic::core::Direction, std::vector<sf::IntRect>>
        animation_sequences; // map with direction key and corresponding animation sequence
    SpriteMap& sprite_map_;
    Coordinate world_position;              // the world position of pacman
    logic::core::Direction world_direction; // the world direction of pacman
    size_t current_sprite_index = 0;        // the index of the current animation sequence
    float last_sprite_change = 0.0f;        // last sprite change timestamp
    float animation_timer = 0.0;            // the time passed after the previous sprite change
    const float animation_speed = 125;      // 125 ms = 0.125s
public:
    // constructor
    explicit PacmanView(const std::shared_ptr<logic::entity::PacmanModel>& model, SpriteMap& sprite_map);

    /**
     * @brief function that can notify observers of an event
     * @param entity this entity
     * @param e the event that occured
     */
    void onNotify(const logic::entity::Subject& entity, logic::core::Event& e) override;

    /**
     * @brief used to draw this ghost on a window
     * @param window the window that will be drawn to
     * @param cam the camera that is used to convert to pixel-coordinates
     */
    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    /**
     * @brief does nothing
     * @param dt delta-time between updates
     */
    void update(float dt) override;

    // getter
    logic::entity::EntityType get_type() const override { return logic::entity::EntityType::Pacman; }
};
} // namespace view
} // namespace representation

#endif // PACMAN_PACMANVIEW_H
