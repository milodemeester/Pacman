//
// Created by milod on 30/10/2025.
//

#include "../include/World.h"
#include "../include/BlinkyModel.h"
#include "../include/ClydeModel.h"
#include "../include/CoinModel.h"
#include "../include/CollisionMap.h"
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

static float basic_pacman_speed = 0.012;
static float basic_ghost_speed = 0.01;

logic::World::World(const std::shared_ptr<GameFactory>& factory) {
    // initialise the width and height and create all the entities.
    level_ = 1;
    game_factory = factory;
    initialise_maze();
    initialise_values();
}

logic::World::World(const std::shared_ptr<GameFactory>& factory, int level, int pacman_lives) : level_(level) {
    // initialise the width and height and create all the entities.
    game_factory = factory;
    initialise_maze(pacman_lives);
    initialise_values();
}

void logic::World::initialise_maze(int pacman_lives) {
    int line = 0;
    std::string maze_line;
    // Read map from this txt file
    std::ifstream maze_file("../data/maps/map1.txt");
    if (maze_file) {
        while (getline(maze_file, maze_line)) {
            // First line are the dimensions of the map (widthXheight
            if (line == 0) {
                size_t pos = maze_line.find('X');
                std::string w = maze_line.substr(0, pos);
                world_width = std::stoi(w);
                std::string h = maze_line.substr(pos + 1);
                world_height = std::stoi(h);
                
                // Initialize the collision map for optimized wall detection
                collision_map_ = std::make_shared<CollisionMap>(world_width, world_height);
                
                line++;
            } else {
                std::vector<std::shared_ptr<Subject>> line_vector;
                line_vector.reserve(world_width);
                for (int char_idx = 0; char_idx < maze_line.length() && char_idx < world_width; ++char_idx) {
                    // X-position from -1 (left) to +1 (right)
                    float x_pos = 2.0f * (float(char_idx) / float(world_width)) - 1.0f;

                    // Y-position from +1 (up) to -1 (under)
                    float y_pos = 1.0f - 2.0f * (float(line) / float(world_height));
                    std::shared_ptr<Subject> crnt_entity = nullptr;
                    switch (maze_line[char_idx]) {
                    case 'W': { // Wall
                        crnt_entity = game_factory->createWall(false);
                        // Mark this position as solid in the collision map
                        collision_map_->markSolid(char_idx, line - 1);
                        break;
                    }
                    case 'C': { // Coin
                        crnt_entity = game_factory->createCoin();
                        // Add to collectibles list for faster iteration
                        auto coin = std::dynamic_pointer_cast<CollectableSubject>(crnt_entity);
                        if (coin) {
                            collectibles_.push_back(coin);
                        }
                        coin_count++;
                        break;
                    }
                    case 'B': { // Blinky
                        crnt_entity = game_factory->createGhost(GhostType::Blinky, world_width, world_height);
                        blinky = std::dynamic_pointer_cast<BlinkyModel>(crnt_entity);
                        break;
                    }
                    case 'P': { // Pinky
                        crnt_entity = game_factory->createGhost(GhostType::Pinky, world_width, world_height);
                        pinky = std::dynamic_pointer_cast<PinkyModel>(crnt_entity);
                        break;
                    }
                    case 'I': { // Inky
                        crnt_entity = game_factory->createGhost(GhostType::Inky, world_width, world_height);
                        inky = std::dynamic_pointer_cast<InkyModel>(crnt_entity);
                        break;
                    }
                    case 'O': { // Clyde
                        crnt_entity = game_factory->createGhost(GhostType::Clyde, world_width, world_height);
                        clyde = std::dynamic_pointer_cast<ClydeModel>(crnt_entity);
                        break;
                    }
                    case 'F': { // Fruit
                        crnt_entity = game_factory->createFruit();
                        // Add to collectibles list for faster iteration
                        auto fruit = std::dynamic_pointer_cast<CollectableSubject>(crnt_entity);
                        if (fruit) {
                            collectibles_.push_back(fruit);
                        }
                        fruit_count++;
                        break;
                    }
                    case 'A': { // Pacman
                        crnt_entity = game_factory->createPacman(world_width, world_height);
                        pacman = std::dynamic_pointer_cast<PacmanModel>(crnt_entity);
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

void logic::World::initialise_values() {
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

bool logic::World::check_collision(Coordinate& entity_pos, Rectangle entity2_rect, float entity_speed, float dt) const {
    // Use fixed collision margin instead of delta-time dependent epsilon
    // This prevents jitter and provides consistent collision feel
    float entity_half_size_x = (1.f / float(world_width));
    float entity_half_size_y = (1.f / float(world_height));

    // Fixed margin for collision detection (not dependent on frame rate)
    const float margin_x = entity_half_size_x * COLLISION_MARGIN;
    const float margin_y = entity_half_size_y * COLLISION_MARGIN;

    // Define the entity's bounding box, shrunk by the fixed margin
    Coordinate entity1_left_upper_corner = {entity_pos.getX() - entity_half_size_x + margin_x,
                                            entity_pos.getY() - entity_half_size_y + margin_y};
    Coordinate entity1_right_lower_corner = {entity_pos.getX() + entity_half_size_x - margin_x,
                                             entity_pos.getY() + entity_half_size_y - margin_y};
    Rectangle entity1_rect = {entity1_left_upper_corner, entity1_right_lower_corner};

    if (utils::intersecting(entity1_rect, entity2_rect)) {
        return true; // Collision detected.
    }
    return false;
}

std::vector<logic::Event> logic::World::check_entity_collision(Coordinate& entity_pos, Direction& entity_direction,
                                                               float entity_speed, bool ghost, float dt) {
    std::vector<logic::Event> events;
    
    // Optimized wall collision check using pre-computed collision map (O(1) instead of O(n))
    float entity_half_size_x = (1.f / float(world_width));
    float entity_half_size_y = (1.f / float(world_height));
    const float margin_x = entity_half_size_x * COLLISION_MARGIN;
    const float margin_y = entity_half_size_y * COLLISION_MARGIN;
    
    Coordinate entity_left_upper_corner = {entity_pos.getX() - entity_half_size_x + margin_x,
                                          entity_pos.getY() - entity_half_size_y + margin_y};
    Coordinate entity_right_lower_corner = {entity_pos.getX() + entity_half_size_x - margin_x,
                                           entity_pos.getY() + entity_half_size_y - margin_y};
    Rectangle entity_rect = {entity_left_upper_corner, entity_right_lower_corner};
    
    // Fast wall collision check using collision map
    if (collision_map_->isWallCollision(entity_rect, world_width, world_height)) {
        // Special case for ghosts with access to certain walls
        if (!ghost || entity_direction != Direction::North) {
            events.push_back(Event::WallCollide);
            return events; // Early exit to avoid unnecessary checks
        }
    }
    
    // Check collision with collectibles (coins and fruits) - optimized iteration
    // Instead of iterating through all entities, only check the collectibles list
    auto it = collectibles_.begin();
    while (it != collectibles_.end()) {
        auto& collectible = *it;
        if (!collectible) {
            ++it;
            continue;
        }
        
        // Create point rectangle for collectible (they are small)
        Coordinate collectible_pos = collectible->get_position();
        Rectangle collectible_rect = {collectible_pos, collectible_pos};
        
        if (check_collision(entity_pos, collectible_rect, entity_speed, dt)) {
            // Determine if it's a coin or fruit
            std::shared_ptr<CoinModel> coin_model = std::dynamic_pointer_cast<CoinModel>(collectible);
            std::shared_ptr<FruitModel> fruit_model = std::dynamic_pointer_cast<FruitModel>(collectible);
            
            if (coin_model) {
                coin_count--;
                events.push_back(Event::CoinCollected);
                collectible->destruct();
                it = collectibles_.erase(it); // Remove from list and get next iterator
                continue;
            } else if (fruit_model) {
                fruit_count--;
                events.push_back(Event::FruitEaten);
                collectible->destruct();
                it = collectibles_.erase(it); // Remove from list and get next iterator
                continue;
            }
        }
        ++it;
    }
    
    // Check collision with ghosts
    std::vector<std::shared_ptr<GhostModel>> ghosts = {blinky, pinky, inky, clyde};
    for (auto& ghost_model : ghosts) {
        if (!ghost_model) continue;
        
        Coordinate ghost_pos = ghost_model->get_position();
        Rectangle ghost_rect = {ghost_pos, ghost_pos};
        
        if (check_collision(entity_pos, ghost_rect, entity_speed, dt)) {
            if (pacman_dead(ghost_model)) {
                events.push_back(Event::PacmanDied);
            } else {
                events.push_back(Event::GhostEaten);
            }
        }
    }
    
    return events;
}

void logic::World::remove_entity(const std::shared_ptr<CollectableSubject>& model) {
    for (auto& vec : entities) {
        for (int i = 0; i < vec.size(); i++) {
            if (std::dynamic_pointer_cast<Subject>(model) == vec[i]) {
                vec.erase(vec.begin() + i);
                model->destruct();
            }
        }
    }
}

void logic::World::move_pacman(logic::Direction direction) { wanted_pacman_direction = direction; }

void logic::World::update(float delta_time) {
    auto stopwatch = Stopwatch::getInstance();
    if (stopwatch->get_time_between(stopwatch->get_now(), fear_mode_begin) < frightened_mode_duration_) {
        pinky->set_fear_mode();
        inky->set_fear_mode();
        blinky->set_fear_mode();
        clyde->set_fear_mode();
    } else {
        pinky->set_chase_mode();
        inky->set_chase_mode();
        blinky->set_chase_mode();
        clyde->set_chase_mode();
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

bool logic::World::pacman_dead(const std::shared_ptr<GhostModel>& model) {
    bool fear_mode = !model->is_chasing_mode();
    if (fear_mode) {
        model->go_to_center();
        return false;
    } else {
        return true;
    }
}

[[nodiscard]] logic::Direction logic::World::get_pacman_direction() const { return pacman->get_direction(); }
[[nodiscard]] Coordinate logic::World::get_pacman_position() const { return pacman->get_position(); }
[[nodiscard]] int logic::World::get_pacman_lives() const { return pacman->get_lives(); }
[[nodiscard]] logic::WorldState logic::World::get_world_state() const { return world_state_; }
[[nodiscard]] int logic::World::get_level() const { return level_; }

void logic::World::begin_fear_mode() { fear_mode_begin = std::chrono::system_clock::now(); }

void logic::World::return_center() {
    pacman->go_to_center();
    inky->go_to_center();
    blinky->go_to_center();
    pinky->go_to_center();
    clyde->go_to_center();
}

void logic::World::set_world_state(WorldState& world_state) { world_state_ = world_state; }

std::vector<std::shared_ptr<logic::Subject>> logic::World::get_all_subjects() const {
    std::vector<std::shared_ptr<Subject>> all_subjects;
    for (const auto& row : entities) {
        all_subjects.insert(all_subjects.end(), row.begin(), row.end());
    }
    return all_subjects;
}