//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>

namespace logic {
class CoinModel;
}
namespace representation {
class CoinView : public representation::EntityView, public logic::Observer {
public:
    explicit CoinView(std::shared_ptr<logic::CoinModel> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_COINVIEW_H
