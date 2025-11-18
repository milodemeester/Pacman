//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>
#include "../../Logic/include/WallModel.h"

#include <SFML/Graphics/Sprite.hpp>
#include <map>

enum class WallSpriteState {
    Wall
};

namespace representation {
class SpriteMap;
class WallView : public representation::EntityView, public logic::Observer {
    std::map<WallSpriteState, sf::Sprite> m_sprites;
    bool invisible_;
public:
    explicit WallView(const std::shared_ptr<logic::WallModel>& model, SpriteMap& sprite_map, bool invisible);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) override;

    void update(double dt) override {}
};
} // namespace representation

#endif // PACMAN_WALLVIEW_H
