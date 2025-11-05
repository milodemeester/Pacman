//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H
#include "EntityView.h"

#include <memory>

namespace logic {
class FruitView;
}
namespace representation {
class FruitView : public representation::EntityView {
    FruitView(std::shared_ptr<logic::FruitView> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_FRUIT_H
