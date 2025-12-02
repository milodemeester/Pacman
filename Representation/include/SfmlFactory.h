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
    std::shared_ptr<Camera> camera_;
    sf::Vector2u windowSize_;
    std::vector<std::shared_ptr<EntityView>> createdViews_;
    SpriteMap& sprite_map_;
    std::shared_ptr<logic::Score> score_;

public:
    // constructor
    SfmlFactory(std::shared_ptr<Camera> camera, sf::Vector2u windowSize, SpriteMap& sprite_map,
                std::shared_ptr<logic::Score> score);

    // destructor
    ~SfmlFactory() override = default;

    /**
     * @brief creates a smart pointer to a pacman model and a pacman view and links them via observer pattern
     * @param world_width the world width measured in amount of entities fitted
     * @param world_height the world height measured in amount of entities fitted
     * @return shared pointer to a PacmanModel instance
     */
    std::shared_ptr<logic::PacmanModel> createPacman(int world_width, int world_height) override;

    /**
     * @brief creates a smart pointer to a ghost model and a ghost view and links them via observer pattern
     * @param type the type of ghost that has to be created by the factory
     * @param world_width the world width measured in amount of entities fitted
     * @param world_height the world height measured in amount of entities fitted
     * @return shared pointer to a (derrived) GhostModel instance
     */
    std::shared_ptr<logic::GhostModel> createGhost(logic::GhostType type, int world_width, int world_height) override;

    /**
     * @brief creates a smart pointer to a coin model and a coin view and links them via observer pattern
     * @return shared pointer to a CoinModel instance
     */
    std::shared_ptr<logic::CoinModel> createCoin() override;

    /**
     * @brief creates a smart pointer to a fruit model and a fruit view and links them via observer pattern
     * @return shared pointer to a FruitModel instance
     */
    std::shared_ptr<logic::FruitModel> createFruit() override;

    /**
     * @brief creates a smart pointer to a wall model and a wall view and links them via observer pattern
     * @param invisible boolean value that determines if the wall is visible or not
     * @return shared pointer to a WallModel instance
     */
    std::shared_ptr<logic::WallModel> createWall(bool invisible) override;

    // getters
    std::vector<std::shared_ptr<EntityView>> getCreatedViews();
};
} // namespace representation

#endif // PACMAN_SFMLFACTORY_H
