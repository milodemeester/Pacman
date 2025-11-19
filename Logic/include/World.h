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
class InkyModel;
}
namespace logic {
class PacmanModel;
class GhostModel;

class World {
    bool check_collision(Coordinate& entity_pos, Rectangle entity2_rect, double entity_speed);
    void initialise_maze();
    void remove_entity(std::shared_ptr<CoinModel> model);
    std::vector<std::vector<std::shared_ptr<Subject>>> entities;
    int width;
    int height;
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<GhostModel> blinky;
    std::shared_ptr<GhostModel> pinky;
    std::shared_ptr<InkyModel> inky;
    std::shared_ptr<GhostModel> clyde;
    Direction wanted_pacman_direction;

public:
    bool check_wall_collision(Coordinate& new_pos, Direction& entity_direction, double entity_speed, bool wall);
    bool check_coin_collision(Coordinate& new_pos, double entity_speed);
    World(const std::shared_ptr<GameFactory>& factory);
    void update(float delta_time);
    [[nodiscard]] int get_width() const { return width; }
    [[nodiscard]] int get_height() const { return height; }
    void move_pacman(logic::Direction);
    [[nodiscard]] Direction get_wanted_pacman_direction() const { return wanted_pacman_direction; }
    void set_wanted_pacman_direction(Direction wanted_pacman_dir) {
        this->wanted_pacman_direction = wanted_pacman_dir;
    }
};
} // namespace logic

#endif // PACMAN_WORLD_H