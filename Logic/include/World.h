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
    /**
     * @brief checks if there is a collision between two entities
     * @param entity_pos the position of the moving entity
     * @param entity2_rect the position of the other entity
     * @param entity_speed the speed of the moving entity (used for calculating the offset
     * @return a boolean value that determines if there is a collision between the two entities
     */
    bool check_collision(Coordinate& entity_pos, Rectangle entity2_rect, double entity_speed);

    /**
     * @brief reads a map and initializes all of the entities in this map
     */
    void initialise_maze();

    /**
     * @param model the model that needs to be removed from the world
     */
    void remove_entity(std::shared_ptr<CoinModel> model);

    std::vector<std::vector<std::shared_ptr<Subject>>> entities; // all the entities int he world
    int width; // width of the world
    int height; // height of the world
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<GhostModel> blinky;
    std::shared_ptr<GhostModel> pinky;
    std::shared_ptr<InkyModel> inky;
    std::shared_ptr<GhostModel> clyde;
    Direction wanted_pacman_direction;

public:
    // constructor
    explicit World(const std::shared_ptr<GameFactory>& factory);

    /**
     * @brief checks if there is a wall where the entity wants to go
     * @param new_pos the new position of the entity
     * @param entity_direction the direction where the entity is going
     * @param entity_speed the speed of the entity
     * @param ghost set to true if the entity is a ghost (which means the entity can pass through invisible walls)
     * @return a boolean value that determines if there is a collision
     */
    bool check_wall_collision(Coordinate& new_pos, Direction& entity_direction, double entity_speed, bool ghost);

    /**
     * @brief checks if there is a coin where the entity wants to go
     * @param new_pos the new position of the entity
     * @param entity_speed the speed of the entity
     * @return a boolean value that determines if there is a collission
     */
    bool check_coin_collision(Coordinate& new_pos, double entity_speed);

    /**
     * @brief updates every "important entity in the world"
     * @param delta_time the time difference between this update and the previous one
     */
    void update(float delta_time);

    /**
     * @brief changes the wanted direction of pacman
     * @param dir new direction of pacman
     */
    void move_pacman(logic::Direction dir);


    // getters
    [[nodiscard]] int get_width() const { return width; }
    [[nodiscard]] int get_height() const { return height; }
    [[nodiscard]] Direction get_wanted_pacman_direction() const { return wanted_pacman_direction; }

};
} // namespace logic

#endif // PACMAN_WORLD_H