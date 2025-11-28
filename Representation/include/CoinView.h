//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H
#include "../../Logic/include/Observer.h"
#include "EntityView.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

namespace logic {
class CoinModel;
}
namespace representation {
class SpriteMap;
class CoinView : public representation::EntityView, public logic::Observer {
    bool invisible = false;
    Coordinate world_position;
    sf::Sprite sprite;

public:
    explicit CoinView(std::shared_ptr<logic::CoinModel> model, SpriteMap& sprite_map);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    void update(double dt) override {}
};
} // namespace representation
#endif // PACMAN_COINVIEW_H
