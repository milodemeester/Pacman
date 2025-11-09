//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "GameFactory.h"
#include "Subject.h"
#include <vector>
#include <fstream>

namespace logic {
class PacmanModel;
class GhostModel;

class World {
    bool check_wall_collision(Coordinate& new_pos);
    void initialise_maze();
    std::vector<std::vector<std::shared_ptr<Subject>>> entities;
    int width;
    int height;
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<GhostModel> blinky;
    std::shared_ptr<GhostModel> pinky;
    std::shared_ptr<GhostModel> inky;
    std::shared_ptr<GhostModel> clyde;
    Direction wanted_pacman_direction;

public:
    World(const std::shared_ptr<GameFactory>& factory);
    void update(double delta_time);
    [[nodiscard]] int get_width() const { return width; }
    [[nodiscard]] int get_height() const { return height; }
    void move_pacman(logic::Direction);

};
} // namespace logic

#endif // PACMAN_WORLD_H