#ifndef PACMAN_SFMLFACTORY_H
#define PACMAN_SFMLFACTORY_H
#include "../../Logic/include/GameFactory.h"
#include "../../Logic/include/Score.h"
#include "Camera.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace logic {
enum class GhostType;
}
namespace representation {
class SpriteMap;
class EntityView;
class SfmlFactory : public logic::GameFactory {
    std::shared_ptr<representation::Camera> camera;
    sf::Vector2u windowSize;
    std::vector<std::shared_ptr<EntityView>> createdViews;
    SpriteMap& sprite_map_;
    std::shared_ptr<logic::Score> score_;

public:
    SfmlFactory(std::shared_ptr<representation::Camera> camera, sf::Vector2u windowSize, SpriteMap& sprite_map,
                std::shared_ptr<logic::Score> score);
    ~SfmlFactory() override = default;

    std::vector<std::shared_ptr<EntityView>> getCreatedViews();

    std::shared_ptr<logic::PacmanModel> createPacman(int world_width, int world_height) override;
    std::shared_ptr<logic::GhostModel> createGhost(logic::GhostType type, int world_width, int world_height) override;
    std::shared_ptr<logic::CoinModel> createCoin() override;
    std::shared_ptr<logic::FruitModel> createFruit() override;
    std::shared_ptr<logic::WallModel> createWall(bool invisible) override;
};
} // namespace representation

#endif // PACMAN_SFMLFACTORY_H
