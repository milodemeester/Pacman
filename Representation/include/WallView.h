//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H
#include "EntityView.h"

namespace logic {
class WallView;
}
namespace representation {
class WallView : public representation::EntityView {
    WallView(std::shared_ptr<logic::WallView> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_WALL_H
