//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "GameFactory.h"
#include "Score.h"
#include "Subject.h"
#include <memory>
#include <vector>

namespace logic {
class PacmanModel;
class GhostModel;

class World {
    std::vector<std::shared_ptr<WallModel>> walls;
    int width;
    int height;
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<GhostModel> blinky;
    std::shared_ptr<GhostModel> pinky;
    std::shared_ptr<GhostModel> inky;
    std::shared_ptr<GhostModel> clyde;

public:
    World(const std::shared_ptr<GameFactory>& factory, int width, int height);
    void update(double delta_time);
};
} // namespace logic

#endif // PACMAN_WORLD_H