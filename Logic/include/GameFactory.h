//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_GAMEFACTORY_H
#define PACMAN_GAMEFACTORY_H
#include "../../Utilities/utils.h"
#include "GhostModel.h"
#include <memory>

namespace logic {
class PacmanModel;
class GhostModel;
class WallModel;
class FruitModel;
class CoinModel;

class GameFactory { // abstract factory
public:
    // destructor
    virtual ~GameFactory() = default;
    /**
     * @brief pure virtual function that needs to be overwritten by a concrete factory
     * @param world_width the world width measured in amount of entities fitted
     * @param world_height the world height measured in amount of entities fitted
     * @return shared pointer to a PacmanModel instance
     */
    virtual std::shared_ptr<PacmanModel> createPacman(int world_width, int world_height) = 0;

    /**
     * @brief pure virtual function that needs to be overwritten by a concrete factory
     * @param type the type of ghost that has to be created by the factory
     * @param world_width the world width measured in amount of entities fitted
     * @param world_height the world height measured in amount of entities fitted
     * @return shared pointer to a (derrived) GhostModel instance
     */
    virtual std::shared_ptr<GhostModel> createGhost(logic::GhostType type, int world_width, int world_height) = 0;

    /**
     * @brief pure virtual function that needs to be overwritten by a concrete factory
     * @param invisible boolean value that determines if the wall is visible or not
     * @return shared pointer to a WallModel instance
     */
    virtual std::shared_ptr<WallModel> createWall(bool invisible) = 0;

    /**
     * @brief pure virtual function that needs to be overwritten by a concrete factory
     * @return shared pointer to a FruitModel instance
     */
    virtual std::shared_ptr<FruitModel> createFruit() = 0;

    /**
     * @brief pure virtual function that needs to be overwritten by a concrete factory
     * @return shared pointer to a CoinModel instance
     */
    virtual std::shared_ptr<CoinModel> createCoin() = 0;
};
} // namespace logic

#endif // PACMAN_GAMEFACTORY_H
