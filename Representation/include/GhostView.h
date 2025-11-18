//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>
#include <map>
#include "../../Logic/include/Direction.h"

namespace logic {
enum class GhostType;
}
namespace sf {
class Sprite;
}
// Enum voor alle mogelijke animatie-frames/states van Ghost
enum class GhostSpriteState {
    // BLINKY
    BLINKY_RIGHT_1, BLINKY_RIGHT_2,
    BLINKY_LEFT_1, BLINKY_LEFT_2,
    BLINKY_DOWN_1, BLINKY_DOWN_2,
    BLINKY_UP_1, BLINKY_UP_2,
    // INKY
    INKY_RIGHT_1, INKY_RIGHT_2,
    INKY_LEFT_1, INKY_LEFT_2,
    INKY_DOWN_1, INKY_DOWN_2,
    INKY_UP_1, INKY_UP_2,
    // PINKY
    PINKY_RIGHT_1, PINKY_RIGHT_2,
    PINKY_DOWN_1, PINKY_DOWN_2,
    PINKY_LEFT_1, PINKY_LEFT_2,
    PINKY_UP_1, PINKY_UP_2,
    // CLYDE
    CLYDED_RIGHT_1, CLYDED_RIGHT_2,
    CLYDED_LEFT_1, CLYDED_LEFT_2,
    CLYDED_DOWN_1, CLYDED_DOWN_2,
    CLYDED_UP_1, CLYDED_UP_2,
};

namespace logic {
enum class Direction;
class GhostModel;
}

namespace representation {
class SpriteMap;
class GhostView : public representation::EntityView, public logic::Observer{
    logic::GhostType type_;
    std::map<logic::Direction, std::vector<sf::Sprite>> animation_sequences;
    size_t current_sprite_index = 0;
    logic::Direction current_state = logic::Direction::North;
    float last_sprite_change = 0.0f; // last sprite change timestamp
    double animation_timer = 0.0;
    const double animation_speed = 125; // 125 ms = 0.125s
    Coordinate world_pos_;
    logic::Direction world_direction_;
public:
    explicit GhostView(std::shared_ptr<logic::GhostModel>& model, SpriteMap& sprite_map, logic::GhostType ghost_type);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    void update(double dt) override;

};
} // namespace representation

#endif // PACMAN_GHOSTVIEW_H
