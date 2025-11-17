//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H
#include "../../Logic/include/Observer.h"
#include "../../Utilities/utils.h"
#include "EntityView.h"
#include "SpriteMap.h"
#include "../../Logic/include/PacmanModel.h"

#include <map>
#include <memory>

namespace sf {
class Sprite;
}
namespace logic {
class PacmanModel;
}

namespace representation {
class Camera;
class PacmanView : public EntityView, public logic::Observer {
    SpriteMap& sprite_map_;
    Coordinate world_position;
    logic::Direction world_direction;
    std::map<logic::Direction, std::vector<sf::IntRect>> animation_sequences;
    size_t current_sprite_index = 0;
    float last_sprite_change = 0.0f; // last sprite change timestamp
    double animation_timer = 0.0;
    const double animation_speed = 125; // 125 ms = 0.125s
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel>& model, SpriteMap& sprite_map);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    void update(double dt) override;
};
} // namespace representation

#endif // PACMAN_PACMANVIEW_H
