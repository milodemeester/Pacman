//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "EntityView.h"

namespace logic {
class GhostView;
}

namespace representation {
class GhostView : public representation::EntityView {
    GhostView(std::shared_ptr<logic::GhostView> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_GHOST_H
