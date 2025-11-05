//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "../../Logic/include/Observer.h"
#include "EntityView.h"

namespace logic {
class PacmanModel;
}
namespace representation {
class PacmanView : public representation::EntityView, public logic::Observer {
public:
    PacmanView(std::shared_ptr<logic::PacmanModel> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_PACMAN_H
