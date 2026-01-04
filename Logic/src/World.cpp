//
// Created by milod on 30/10/2025.
//

#include "../include/World.h"
#include "../include/BlinkyModel.h"
#include "../include/ClydeModel.h"
#include "../include/CoinModel.h"
#include "../include/FruitModel.h"
#include "../include/GameFactory.h"
#include "../include/GhostModel.h"
#include "../include/InkyModel.h"
#include "../include/PacmanModel.h"
#include "../include/PinkyModel.h"
#include "../include/Score.h"
#include "../include/Stopwatch.h"
#include "../include/Subject.h"
#include "../include/WallModel.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

static float basic_pacman_speed = 0.014;
static float basic_ghost_speed = 0.01;

namespace logic::core {

World::World(const std::shared_ptr<GameFactory>& factory) {
    // initialise the width and height and create all the entities.
    level_ = 1;
    game_factory = factory;
    initialise_maze();
    initialise_values();
}

World::World(const std::shared_ptr<GameFactory>& factory, int level, int pacman_lives) : level_(level) {
    // initialise the width and height and create all the entities.
    game_factory = factory;
    initialise_maze(pacman_lives);
    initialise_values();
}

void World::initialise_maze(int pacman_lives) {
    float line = 0.f;
    std::string maze_line;
    // Read map from this txt file
    std::ifstream maze_file("../data/maps/map1.txt");
    if (!maze_file) {
        std::cerr << "Failed to load map in world" << std::endl;
        exit(1);
    }
    if (maze_file) {
        while (getline(maze_file, maze_line)) {
            // First line are the dimensions of the map (widthXheight
            if (line == 0) {
                size_t pos = maze_line.find('X');
                std::string w = maze_line.substr(0, pos);
                world_width = std::stoi(w);
                std::string h = maze_line.substr(pos + 1);
                world_height = std::stoi(h);
                line++;
            } else {
                std::vector<std::shared_ptr<entity::Subject>> line_vector;
                line_vector.reserve(world_width);
                for (float char_idx = 0; char_idx < maze_line.length() && char_idx < world_width; ++char_idx) {
                    // X-position from -1 (left) to +1 (right)
                    float x_pos = 2.0f * (char_idx / float(world_width)) - 1.0f;

                    // Y-position from +1 (up) to -1 (under)
                    float y_pos = 1.0f - 2.0f * (line / float(world_height));
                    std::shared_ptr<entity::Subject> crnt_entity = nullptr;
                    switch (maze_line[char_idx]) {
                    case 'W': { // Wall
                        crnt_entity = game_factory->createWall(false);
                        break;
                    }
                    case 'C': { // Coin
                        crnt_entity = game_factory->createCoin();
                        coin_count++;
                        break;
                    }
                    case 'B': { // Blinky
                        blinky = game_factory->createGhost(entity::GhostType::Blinky, world_width, world_height);
                        crnt_entity = blinky;
                        break;
                    }
                    case 'P': { // Pinky
                        pinky = game_factory->createGhost(entity::GhostType::Pinky, world_width, world_height);
                        crnt_entity = pinky;
                        break;
                    }
                    case 'I': { // Inky
                        inky = game_factory->createGhost(entity::GhostType::Inky, world_width, world_height);
                        crnt_entity = inky;
                        break;
                    }
                    case 'O': { // Clyde
                        clyde = game_factory->createGhost(entity::GhostType::Clyde, world_width, world_height);
                        crnt_entity = clyde;
                        break;
                    }
                    case 'F': { // Fruit
                        crnt_entity = game_factory->createFruit();
                        fruit_count++;
                        break;
                    }
                    case 'A': { // Pacman
                        pacman = game_factory->createPacman(world_width, world_height);
                        crnt_entity = pacman;
                        pacman->set_lives(pacman_lives);
                        break;
                    }
                    case 'Z': { // Niets
                        crnt_entity = game_factory->createWall(true);
                        break;
                    }
                    default:;
                    }
                    if (crnt_entity) {
                        line_vector.push_back(crnt_entity);
                        crnt_entity->set_position({x_pos, -y_pos});
                    }
                }
                entities.emplace_back(line_vector);
                line++;
            }
        }
    } else {
        std::cerr << "Could not open maze file" << std::endl;
        exit(1);
    }
    maze_file.close();
}

void World::initialise_values() {
    switch (level_) {
    case 1: {
        frightened_mode_duration_ = 6000;
        ghost_speed_fraction_ = 0.5f;
        pacman_speed_fraction_ = 0.5f;
        break;
    }
    case 2: {
        frightened_mode_duration_ = 5000;
        ghost_speed_fraction_ = 0.6f;
        pacman_speed_fraction_ = 0.6f;
        break;
    }
    case 3: {
        frightened_mode_duration_ = 4000;
        ghost_speed_fraction_ = 0.7f;
        pacman_speed_fraction_ = 0.7f;
        break;
    }
    case 4: {
        frightened_mode_duration_ = 3000;
        ghost_speed_fraction_ = 0.8f;
        pacman_speed_fraction_ = 0.8f;
        break;
    }
    case 5: {
        frightened_mode_duration_ = 2000;
        ghost_speed_fraction_ = 0.9f;
        pacman_speed_fraction_ = 0.9f;
        break;
    }
    case 6: {
        frightened_mode_duration_ = 1000;
        ghost_speed_fraction_ = 1.0f;
        pacman_speed_fraction_ = 1.0f;
        break;
    }
    default: {
        frightened_mode_duration_ = 0;
        ghost_speed_fraction_ = 1.2f;
        pacman_speed_fraction_ = 1.1f;
        break;
    }
    }
    pacman->set_speed(basic_pacman_speed * pacman_speed_fraction_);
    inky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
    blinky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
    pinky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
    clyde->set_speed(basic_ghost_speed * ghost_speed_fraction_);
}

bool World::check_collision(Coordinate& entity_pos, Rectangle entity2_rect, float entity_speed, float dt) const {
    float entity_half_size_x = (1.f / float(world_width));
    float entity_half_size_y = (1.f / float(world_height));

    // This value works and was found by trial and error
    const float collision_sensitivity = 0.5f;

    const float epsilon_x = entity_half_size_x * entity_speed * dt * collision_sensitivity;
    const float epsilon_y = entity_half_size_y * entity_speed * dt * collision_sensitivity;

    // Define the entity's bounding box, shrunk by the scaled epsilon on each axis.
    Coordinate entity1_left_upper_corner = {entity_pos.getX() - entity_half_size_x + epsilon_x,
                                            entity_pos.getY() - entity_half_size_y + epsilon_y};
    Coordinate entity1_right_lower_corner = {entity_pos.getX() + entity_half_size_x - epsilon_x,
                                             entity_pos.getY() + entity_half_size_y - epsilon_y};
    Rectangle entity1_rect = {entity1_left_upper_corner, entity1_right_lower_corner};

    if (utils::intersecting(entity1_rect, entity2_rect)) {
        return true; // Collision detected.
    }
    return false;
}

std::vector<logic::core::Event> World::check_entity_collision(Coordinate& entity_pos, Direction& entity_direction,
                                                              float entity_speed, bool ghost, float dt) {
    // In this method, it is safe to do static_casts, because there are checks done first for the entity_type
    std::vector<Event> events;
    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) { // loop through every entity
            Rectangle entity2_rect;
            if (!entity) {
            } else {
                Coordinate entity2_left_upper_corner = {entity->get_position().getX(), entity->get_position().getY()};
                Coordinate entity2_right_lower_corner = {entity->get_position().getX(), entity->get_position().getY()};
                entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};

                if (entity->get_type() == entity::EntityType::Wall) {
                    auto wall_model = std::static_pointer_cast<entity::WallModel>(entity);
                    // Define the wall's bounding box
                    float entity_half_size_x = (1.f / float(world_width));
                    float entity_half_size_y = (1.f / float(world_height));
                    entity2_left_upper_corner = {wall_model->get_position().getX() - entity_half_size_x,
                                                 wall_model->get_position().getY() - entity_half_size_y};
                    entity2_right_lower_corner = {wall_model->get_position().getX() + entity_half_size_x,
                                                  wall_model->get_position().getY() + entity_half_size_y};
                    entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                    if (ghost && wall_model->has_ghost_acces() && entity_direction == Direction::North) {
                    } else if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                        events.push_back(Event::WallCollide);
                    }
                }
                if (entity->get_type() == entity::EntityType::Coin && !ghost) {
                    auto coin_model = std::static_pointer_cast<entity::CoinModel>(entity);
                    if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                        remove_entity(coin_model);
                        coin_count--;
                        events.push_back(Event::CoinCollected);
                    }
                }
                if (entity->get_type() == entity::EntityType::Fruit && !ghost) {
                    auto fruit_model = std::static_pointer_cast<entity::CoinModel>(entity);
                    float entity_half_size_x = (1.f / float(world_width));
                    float entity_half_size_y = (1.f / float(world_height));
                    entity2_left_upper_corner = {fruit_model->get_position().getX() - entity_half_size_x,
                                                 fruit_model->get_position().getY() - entity_half_size_y};
                    entity2_right_lower_corner = {fruit_model->get_position().getX() + entity_half_size_x,
                                                  fruit_model->get_position().getY() + entity_half_size_y};
                    entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                    if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                        remove_entity(fruit_model);
                        auto score = Stopwatch::getInstance();
                        fear_mode_begin = std::chrono::system_clock::now();
                        fruit_count--;
                        events.push_back(Event::FruitEaten);
                    }
                } else if (entity->get_type() == entity::EntityType::Ghost && !ghost) {
                    auto ghost_model = std::static_pointer_cast<entity::GhostModel>(entity);
                    if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                        if (pacman_dead(ghost_model)) {
                            events.push_back(Event::PacmanDied);
                        } else {
                            events.push_back(Event::GhostEaten);
                        }
                    }
                }
            }
        }
    }
    return events;
}

void World::remove_entity(const std::shared_ptr<entity::CollectableSubject>& model) {
    if (model->get_type() != entity::EntityType::Fruit && model->get_type() != entity::EntityType::Coin) {
        return;
    }
    for (auto& vec : entities) {
        for (int i = 0; i < vec.size(); i++) {
            if (model == vec[i]) {
                vec.erase(vec.begin() + i);
                model->destruct();
            }
        }
    }
}

void World::move_pacman(Direction direction) { wanted_pacman_direction = direction; }

void World::update(float delta_time) {
    auto stopwatch = Stopwatch::getInstance();
    if (stopwatch->get_time_between(stopwatch->get_now(), fear_mode_begin) < frightened_mode_duration_) {
        pinky->set_fear_mode();
        pinky->set_speed(basic_ghost_speed * ghost_speed_fraction_ * 0.7f);
        inky->set_fear_mode();
        inky->set_speed(basic_ghost_speed * ghost_speed_fraction_ * 0.7f);
        blinky->set_fear_mode();
        blinky->set_speed(basic_ghost_speed * ghost_speed_fraction_ * 0.7f);
        clyde->set_fear_mode();
        clyde->set_speed(basic_ghost_speed * ghost_speed_fraction_ * 0.7f);
    } else {
        pinky->set_chase_mode();
        pinky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
        inky->set_chase_mode();
        inky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
        blinky->set_chase_mode();
        blinky->set_speed(basic_ghost_speed * ghost_speed_fraction_);
        clyde->set_chase_mode();
        clyde->set_speed(basic_ghost_speed * ghost_speed_fraction_);
    }
    pinky->update(delta_time, *this);
    inky->update(delta_time, *this);
    blinky->update(delta_time, *this);
    clyde->update(delta_time, *this);
    pacman->update(delta_time, *this);
    if (fruit_count == 0 && coin_count == 0) {
        WorldState world_state = WorldState::Victory;
        set_world_state(world_state);
    }
}

bool World::pacman_dead(const std::shared_ptr<entity::GhostModel>& model) {
    bool fear_mode = !model->is_chasing_mode();
    if (fear_mode) {
        model->go_to_center();
        return false;
    } else {
        return true;
    }
}

[[nodiscard]] Direction World::get_pacman_direction() const { return pacman->get_direction(); }
[[nodiscard]] Coordinate World::get_pacman_position() const { return pacman->get_position(); }
[[nodiscard]] int World::get_pacman_lives() const { return pacman->get_lives(); }
[[nodiscard]] WorldState World::get_world_state() const { return world_state_; }
[[nodiscard]] int World::get_level() const { return level_; }

void World::begin_fear_mode() { fear_mode_begin = std::chrono::system_clock::now(); }

void World::return_center() {
    pacman->go_to_center();
    inky->go_to_center();
    blinky->go_to_center();
    pinky->go_to_center();
    clyde->go_to_center();
}

void World::set_world_state(WorldState& world_state) { world_state_ = world_state; }

std::vector<std::shared_ptr<entity::Subject>> World::get_all_subjects() const {
    std::vector<std::shared_ptr<entity::Subject>> all_subjects;
    for (const auto& row : entities) {
        all_subjects.insert(all_subjects.end(), row.begin(), row.end());
    }
    return all_subjects;
}
} // namespace logic::core