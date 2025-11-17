#ifndef PACMAN_SFMLFACTORY_H
#define PACMAN_SFMLFACTORY_H
#include "../../Logic/include/GameFactory.h"
#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace representation {
class SpriteMap;
class EntityView;
class SfmlFactory : public logic::GameFactory {
    std::shared_ptr<representation::Camera> camera;
    sf::Vector2u windowSize;
    std::vector<std::shared_ptr<EntityView>> createdViews;
    SpriteMap& sprite_map_;

public:
    SfmlFactory(std::shared_ptr<representation::Camera> camera, sf::Vector2u windowSize, SpriteMap& sprite_map);
    ~SfmlFactory() override = default;

    std::vector<std::shared_ptr<EntityView>> getCreatedViews();

    std::shared_ptr<logic::PacmanModel> createPacman() override;
    std::shared_ptr<logic::GhostModel> createGhost(std::string) override;
    std::shared_ptr<logic::CoinModel> createCoin() override;
    std::shared_ptr<logic::FruitModel> createFruit() override;
    std::shared_ptr<logic::WallModel> createWall() override;
};
} // namespace representation

#endif // PACMAN_SFMLFACTORY_H
