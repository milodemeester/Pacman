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

// Enum voor alle mogelijke animatie-frames/states van Pacman
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
    PacmanSpriteState currentState = PacmanSpriteState::OPEN_UP_1;
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel>& model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, Camera& cam) override;
};
} // namespace representation

#endif // PACMAN_PACMANVIEW_H
