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
class GameFactory {
public:
    virtual ~GameFactory() = default;
    virtual std::shared_ptr<PacmanModel> createPacman(int world_width, int world_height) = 0;
    virtual std::shared_ptr<GhostModel> createGhost(logic::GhostType type, int world_width, int world_height) = 0;
    virtual std::shared_ptr<WallModel> createWall(bool invisible) = 0;
    virtual std::shared_ptr<FruitModel> createFruit() = 0;
    virtual std::shared_ptr<CoinModel> createCoin() = 0;
};
} // namespace logic

#endif // PACMAN_GAMEFACTORY_H
