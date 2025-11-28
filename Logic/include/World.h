//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_WORLD_H
#define PACMAN_WORLD_H
#include "GameFactory.h"
#include "Subject.h"
#include <fstream>
#include <vector>

namespace logic {
class CollectableSubject;
}
namespace logic {
class ClydeModel;
}
namespace logic {
class BlinkyModel;
}
namespace logic {
class PinkyModel;
}
namespace logic {
class InkyModel;
}
namespace logic {
class GhostModel;
class PacmanModel;

class World {
    /**
     * @param model the coin model that needs to be removed from the world
     */
    void remove_entity(std::shared_ptr<CollectableSubject> model);

    /**
     * @brief checks if there is a collision between two entities
     * @param entity_pos the position of the moving entity
     * @param entity2_rect the position of the other entity
     * @param entity_speed the speed of the moving entity (used for calculating the offset
     * @return a boolean value that determines if there is a collision between the two entities
     */
    bool check_collision(Coordinate& entity_pos, Rectangle entity2_rect, double entity_speed, float dt);

    /**
     * @brief reads a map and initializes all of the entities in this map
     */
    void initialise_maze();

    bool pacman_dead(std::shared_ptr<GhostModel> model);

    std::vector<std::vector<std::shared_ptr<Subject>>> entities; // all the entities int he world
    int width; // width of the world
    int height; // height of the world
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<BlinkyModel> blinky;
    std::shared_ptr<PinkyModel> pinky;
    std::shared_ptr<InkyModel> inky;
    std::shared_ptr<ClydeModel> clyde;
    Direction wanted_pacman_direction;
    std::chrono::system_clock::time_point fear_mode_begin;
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
    bool check_wall_collision(Coordinate& new_pos, Direction& entity_direction, double entity_speed, bool ghost, float dt);

    /**
     * @brief checks if there is an entity where the entity wants to go
     * @param new_pos the new position of the entity
     * @param entity_speed the speed of the entity
     * @return a boolean value that determines if there is a collission
     */
    logic::Event check_entity_collision(Coordinate& new_pos, double entity_speed, float dt);

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

    void begin_fear_mode();

    void reset_();


    // getters
    [[nodiscard]] int get_width() const { return width; }
    [[nodiscard]] int get_height() const { return height; }
    [[nodiscard]] Direction get_wanted_pacman_direction() const { return wanted_pacman_direction; }
    [[nodiscard]] Direction get_pacman_direction() const;
    [[nodiscard]] Coordinate get_pacman_position() const;
    [[nodiscard]] int get_pacman_lives() const;

};
} // namespace logic

#endif // PACMAN_WORLD_H