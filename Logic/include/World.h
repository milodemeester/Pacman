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
class ClydeModel;
class BlinkyModel;
class PinkyModel;
class InkyModel;
class GhostModel;
class PacmanModel;

enum class WorldState {
    Running,
    Victory,
    Defeated,
};

class World {
    /**
     * @param model the coin model that needs to be removed from the world
     */
    void remove_entity(const std::shared_ptr<CollectableSubject>& model);

    /**
     * @brief checks if there is a collision between two entities
     * @param entity_pos the position of the moving entity
     * @param entity2_rect the position of the other entity
     * @param entity_speed the speed of the moving entity (used for calculating the offset
     * @param dt the delta time that passed since the last update
     * @return a boolean value that determines if there is a collision between the two entities
     */
    bool check_collision(Coordinate& entity_pos, Rectangle entity2_rect, float entity_speed, float dt) const;

    /**
     * @param pacman_lives the amount of lives pacman has left at this current level (default value of 3)
     * @brief reads a map and initializes all of the entities in this map
     */
    void initialise_maze(int pacman_lives = 3);

    /**
     * @brief initializes all of the level-dependant values of the entities in this world
     */
    void initialise_values();

    /**
     * @brief called when a ghost collides with pacman and checks if pacman died or the ghost died
     * @param model the model pacman collided with
     * @return true when pacman dies, false when ghost dies
     */
    bool pacman_dead(const std::shared_ptr<GhostModel>& model);

    std::vector<std::vector<std::shared_ptr<Subject>>> entities; // all the entities in the world
    int world_width;                                             // width of the world
    int world_height;                                            // height of the world
    std::shared_ptr<GameFactory> game_factory;
    std::shared_ptr<PacmanModel> pacman;
    std::shared_ptr<BlinkyModel> blinky;
    std::shared_ptr<PinkyModel> pinky;
    std::shared_ptr<InkyModel> inky;
    std::shared_ptr<ClydeModel> clyde;
    Direction wanted_pacman_direction;
    std::chrono::system_clock::time_point fear_mode_begin;
    int coin_count = 0;
    int fruit_count = 0;
    WorldState world_state_ = WorldState::Running;
    int level_;

    // level-dependant values
    int frightened_mode_duration_; // duration of ghost frightened mode in miliseconds
    float pacman_speed_fraction_;  // the fraction of the total pacman speed
    float ghost_speed_fraction_;   // the fraction of the total ghost speed

public:
    // constructor
    explicit World(const std::shared_ptr<GameFactory>& factory);
    explicit World(const std::shared_ptr<GameFactory>& factory, int level, int pacman_lives);

    /**
     * @brief checks if there is an entity where the entity wants to go
     * @param new_pos the new position of the entity
     * @param entity_speed the speed of the entity
     * @param ghost
     * @param dt the delta time that passed since the last update
     * @return a boolean value that determines if there is a collission
     */
    std::vector<Event> check_entity_collision(Coordinate& new_pos, Direction& ent_dir, float entity_speed, bool ghost,
                                              float dt);

    /**
     * @brief updates every "important entity in the world"
     * @param delta_time the time difference between this update and the previous one
     */
    void update(float delta_time);

    /**
     * @brief changes the wanted direction of pacman
     * @param dir new direction of pacman
     */
    void move_pacman(Direction dir);

    /**
     * @brief makes sure the ghosts go into fear mode when pacman eats fruit
     */
    void begin_fear_mode();

    /**
     * @brief moves every entity to their respective starting locations
     */
    void return_center();

    // setters
    void set_world_state(WorldState& world_state);

    // getters
    [[nodiscard]] int get_width() const { return world_width; }
    [[nodiscard]] int get_height() const { return world_height; }
    [[nodiscard]] Direction get_wanted_pacman_direction() const { return wanted_pacman_direction; }
    [[nodiscard]] Direction get_pacman_direction() const;
    [[nodiscard]] Coordinate get_pacman_position() const;
    [[nodiscard]] int get_pacman_lives() const;
    [[nodiscard]] WorldState get_world_state() const;
    [[nodiscard]] int get_level() const;
    [[nodiscard]] std::vector<std::shared_ptr<Subject>> get_all_subjects() const;
};
} // namespace logic

#endif // PACMAN_WORLD_H