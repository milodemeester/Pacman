//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "../../Logic/include/Direction.h"
#include "../../Logic/include/Observer.h"
#include "EntityView.h"
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <memory>

namespace logic {
namespace entity {
class GhostModel;

enum class GhostType;
} // namespace entity
} // namespace logic

/**
 * @brief every possible animation-state of a ghost
 */
enum class GhostSpriteState {
    // BLINKY
    BLINKY_RIGHT_1,
    BLINKY_RIGHT_2,
    BLINKY_LEFT_1,
    BLINKY_LEFT_2,
    BLINKY_DOWN_1,
    BLINKY_DOWN_2,
    BLINKY_UP_1,
    BLINKY_UP_2,
    // INKY
    INKY_RIGHT_1,
    INKY_RIGHT_2,
    INKY_LEFT_1,
    INKY_LEFT_2,
    INKY_DOWN_1,
    INKY_DOWN_2,
    INKY_UP_1,
    INKY_UP_2,
    // PINKY
    PINKY_RIGHT_1,
    PINKY_RIGHT_2,
    PINKY_DOWN_1,
    PINKY_DOWN_2,
    PINKY_LEFT_1,
    PINKY_LEFT_2,
    PINKY_UP_1,
    PINKY_UP_2,
    // CLYDE
    CLYDED_RIGHT_1,
    CLYDED_RIGHT_2,
    CLYDED_LEFT_1,
    CLYDED_LEFT_2,
    CLYDED_DOWN_1,
    CLYDED_DOWN_2,
    CLYDED_UP_1,
    CLYDED_UP_2,
    // FEAR
    FEAR_MODE_1,
    FEAR_MODE_2
};

namespace logic {
namespace core {
enum class Direction;
}
namespace entity {
class GhostModel;
}
} // namespace logic

namespace representation {
class SpriteMap;

namespace view {
class GhostView : public EntityView, public logic::core::Observer {
    std::map<logic::core::Direction, std::vector<sf::Sprite>>
        animation_sequences;                // map with direction key and corresponding animation sequence
    size_t current_sprite_index = 0;        // the index of the current animation sequence
    logic::core::Direction world_direction; // the current direction of the ghost
    float last_sprite_change = 0.0f;        // last sprite change timestamp
    float animation_timer = 0.0;            // the time passed after the previous sprite change
    const float animation_speed = 100;      // 100 ms = 0.100s
    Coordinate world_pos_;                  // the world position of the ghost
    bool fear_mode = false;                 // if true, ghost is in fear mode and has to change its sprite accordingly

public:
    // constructor
    explicit GhostView(std::shared_ptr<logic::entity::GhostModel>& model, SpriteMap& sprite_map,
                       logic::entity::GhostType ghost_type);

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

    logic::entity::EntityType get_type() const override { return logic::entity::EntityType::Ghost; }
};
} // namespace view
} // namespace representation

#endif // PACMAN_GHOSTVIEW_H
