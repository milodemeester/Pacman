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

// Enum voor alle mogelijke animatie states van Pacman
enum class PacmanSpriteState {
    CLOSED,
    OPEN_RIGHT_1,
    OPEN_RIGHT_2,
    OPEN_LEFT_1,
    OPEN_LEFT_2,
    OPEN_UP_1,
    OPEN_UP_2,
    OPEN_DOWN_1,
    OPEN_DOWN_2,
    FULL_CIRCLE
};

namespace representation {
class Camera;
class PacmanView : public EntityView, public logic::Observer {
    std::shared_ptr<logic::PacmanModel> model_;
    std::map<PacmanSpriteState, sf::Sprite> m_sprites;
    std::map<logic::Direction, std::vector<PacmanSpriteState>> animation_sequences;
    size_t current_frame_index = 0;
    PacmanSpriteState current_state = PacmanSpriteState::OPEN_UP_1;
    float last_sprite_change = 0.0f; // last sprite change timestamp
    double animation_timer = 0.0;
    const double animation_speed = 120000000; // 500 ms = 0.5s
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel>& model, SpriteMap& sprite_map);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, Camera& cam) override;

    void update(double dt) override;
};
} // namespace representation

#endif // PACMAN_PACMANVIEW_H
