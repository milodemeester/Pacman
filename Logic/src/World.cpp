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
#include "../include/Stopwatch.h"
#include "../include/Subject.h"
#include "../include/WallModel.h"
#include "../include/Score.h"
#include <fstream>
#include <memory>
#include <vector>

static float basic_pacman_speed = 0.016;
static float basic_ghost_speed = 0.014;

logic::World::World(const std::shared_ptr<GameFactory>& factory) {
    // initialise the width and height and create all the entities.
    level_ = 1;
    game_factory = factory;
    initialise_maze();
    initialise_values();
}

logic::World::World(const std::shared_ptr<GameFactory>& factory, int level, int pacman_lives): level_(level) {
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
    while (getline(maze_file, maze_line)) {
        // First line are the dimensions of the map (widthXheight
        if (line == 0) {
            size_t pos = maze_line.find('X');
            std::string w = maze_line.substr(0, pos);
            world_width = std::stoi(w);
            std::string h = maze_line.substr(pos + 1);
            world_height = std::stoi(h);
            line++;
        }
        else {
            std::vector<std::shared_ptr<Subject>> line_vector;
            line_vector.reserve(world_width);
            for (int char_idx = 0; char_idx < maze_line.length() && char_idx < world_width; ++char_idx) {
                // X-position from -1 (left) to +1 (right)
                float x_pos = 2.0f * (static_cast<float>(char_idx)) / static_cast<float>(world_width) - 1.0f;

                // Y-position from +1 (up) to -1 (under)
                float y_pos = 1.0f - 2.0f * (static_cast<float>(line)) / static_cast<float>(world_height);
                std::shared_ptr<Subject> crnt_entity = nullptr;
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
    maze_file.close();
}

void logic::World::initialise_values() {
    switch (level_) {
    case 1 : {
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
    pacman->set_speed(basic_pacman_speed*pacman_speed_fraction_);
    inky->set_speed(basic_ghost_speed*pacman_speed_fraction_);
    blinky->set_speed(basic_ghost_speed*pacman_speed_fraction_);
    pinky->set_speed(basic_ghost_speed*pacman_speed_fraction_);
    clyde->set_speed(basic_ghost_speed*pacman_speed_fraction_);
}

bool logic::World::check_collision(Coordinate& entity_pos, Rectangle entity2_rect, double entity_speed, float dt) {
    // TODO: colissions are still a bit weird, fix it
    float entity_half_size_x = (1.f/float(world_width));
    float entity_half_size_y = (1.f/float(world_height));

    // This value works and was found by trial and error
    const float collision_sensitivity = 0.45f;

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


bool logic::World::check_wall_collision(Coordinate& entity_pos, Direction& entity_direction, double entity_speed, bool ghost, float dt) {
    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) {
            std::shared_ptr<WallModel> wall_model = std::dynamic_pointer_cast<WallModel>(entity);
            if (wall_model) {
                // Define the wall's bounding box (remains the same).
                float entity_half_size_x = (1.f/float(world_width));
                float entity_half_size_y = (1.f/float(world_height));
                Coordinate entity2_left_upper_corner = {wall_model->get_position().getX() - entity_half_size_x,
                    wall_model->get_position().getY() - entity_half_size_y};
                Coordinate entity2_right_lower_corner = {wall_model->get_position().getX() + entity_half_size_x,
                    wall_model->get_position().getY() + entity_half_size_y};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (ghost && wall_model->has_ghost_acces() && entity_direction == Direction::North) {}
                else if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                    return true;
                }
            }
        }
    }
    return false; // No collision.
}

logic::Event logic::World::check_entity_collision(Coordinate& entity_pos, double entity_speed, float dt) {
    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) {
            std::shared_ptr<CoinModel> coin_model = std::dynamic_pointer_cast<CoinModel>(entity);
            std::shared_ptr<FruitModel> fruit_model = std::dynamic_pointer_cast<FruitModel>(entity);
            std::shared_ptr<GhostModel> ghost_model = std::dynamic_pointer_cast<GhostModel>(entity);
            if (coin_model) {
                Coordinate entity2_left_upper_corner = {coin_model->get_position().getX(),
                    coin_model->get_position().getY()};
                Coordinate entity2_right_lower_corner = {coin_model->get_position().getX(),
                    coin_model->get_position().getY()};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                    remove_entity(coin_model);
                    coin_count--;
                    return Event::CoinCollected;
                }
            }
            else if (fruit_model) {
                // Define the wall's bounding box (remains the same).
                Coordinate entity2_left_upper_corner = {fruit_model->get_position().getX(),
                    fruit_model->get_position().getY()};
                Coordinate entity2_right_lower_corner = {fruit_model->get_position().getX(),
                    fruit_model->get_position().getY()};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                    remove_entity(fruit_model);
                    auto score = Stopwatch::getInstance();
                    fear_mode_begin = std::chrono::system_clock::now();
                    fruit_count--;
                    return Event::FruitEaten;
                }
            }
            else if (ghost_model) {
                // Define the wall's bounding box (remains the same).
                Coordinate entity2_left_upper_corner = {ghost_model->get_position().getX(),
                    ghost_model->get_position().getY()};
                Coordinate entity2_right_lower_corner = {ghost_model->get_position().getX(),
                    ghost_model->get_position().getY()};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (check_collision(entity_pos, entity2_rect, entity_speed, dt)) {
                    if (pacman_dead(ghost_model)) {
                        return Event::PacmanDied;
                    }
                    else {
                        return Event::GhostEaten;
                    }
                }
            }
        }
    }
    return Event::Nothing; // No collision.
}

void logic::World::remove_entity(std::shared_ptr<CollectableSubject> model) {
    for (auto& vec : entities) {
        for (int i = 0; i < vec.size(); i++) {
            if (std::dynamic_pointer_cast<Subject>(model) == vec[i]) {
                vec.erase(vec.begin() + i);
                model->destruct();
            }
        }
    }
}

void logic::World::move_pacman(logic::Direction direction) {
    wanted_pacman_direction = direction;
}


void logic::World::update(float delta_time) {
    auto stopwatch = Stopwatch::getInstance();
    if (stopwatch->get_time_between(stopwatch->get_now(), fear_mode_begin) < frightened_mode_duration_) {
        pinky->set_fear_mode();
        inky->set_fear_mode();
        blinky->set_fear_mode();
        clyde->set_fear_mode();
    }
    else {
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

bool logic::World::pacman_dead(std::shared_ptr<logic::GhostModel> model) {
    bool fear_mode = !model->is_chasing_mode();
    if (fear_mode) {
        model->go_to_center();
        return false;
    }
    else {
        return true;
    }
}

[[nodiscard]] logic::Direction logic::World::get_pacman_direction() const {
    return pacman->get_direction();
}
[[nodiscard]] Coordinate logic::World::get_pacman_position() const {
    return pacman->get_position();
}
[[nodiscard]] int logic::World::get_pacman_lives() const {
    return pacman->get_lives();
}
[[nodiscard]] logic::WorldState logic::World::get_world_state() const {
    return world_state_;
}
[[nodiscard]] int logic::World::get_level() const {
    return level_;
}

void logic::World::begin_fear_mode() {
    fear_mode_begin = std::chrono::system_clock::now();
}

void logic::World::return_center() {
    pacman->go_to_center();
    inky->go_to_center();
    blinky->go_to_center();
    pinky->go_to_center();
    clyde->go_to_center();
}

void logic::World::set_world_state(WorldState& world_state) {
    world_state_ = world_state;
}