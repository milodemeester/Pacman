#ifndef PACMAN_SFMLFACTORY_H
#define PACMAN_SFMLFACTORY_H
#include "../../Logic/include/GameFactory.h"
#include "Camera.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace representation {
class EntityView;
class SfmlFactory : public logic::GameFactory {
    representation::Camera camera;
    sf::Vector2u windowSize;
    std::vector<std::unique_ptr<EntityView>> createdViews;

public:
    SfmlFactory(representation::Camera& camera, sf::Vector2u windowSize);
    ~SfmlFactory() override = default;

    std::vector<std::unique_ptr<EntityView>>& getCreatedViews();

    std::shared_ptr<logic::PacmanModel> createPacman() override;
    std::shared_ptr<logic::GhostModel> createGhost(std::string) override;
    std::shared_ptr<logic::CoinModel> createCoin() override;
    std::shared_ptr<logic::FruitModel> createFruit() override;
    std::shared_ptr<logic::WallModel> createWall() override;
};
} // namespace representation

#endif // PACMAN_SFMLFACTORY_H
