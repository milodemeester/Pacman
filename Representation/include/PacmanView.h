//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_PACMANVIEW_H
#define PACMAN_PACMANVIEW_H
#include "../../Logic/include/Observer.h"
#include "EntityView.h"

namespace logic {
class PacmanModel;
}
namespace representation {
class PacmanView : public EntityView, public logic::Observer {
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel>& model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_PACMANVIEW_H
