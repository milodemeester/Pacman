//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "EntityView.h"
#include <memory>

namespace logic {
class CoinView;
}
namespace representation {
class CoinView : public representation::EntityView {
    CoinView(std::shared_ptr<logic::CoinView> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_COIN_H
