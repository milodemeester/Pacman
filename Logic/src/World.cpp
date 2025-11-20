//
// Created by milod on 30/10/2025.
//

#include <fstream>
#include <vector>
#include <memory>
#include "../include/World.h"
#include "../include/GhostModel.h"
#include "../include/PacmanModel.h"
#include "../include/Subject.h"
#include "../include/WallModel.h"
#include "../include/FruitModel.h"
#include "../include/CoinModel.h"
#include "../include/GameFactory.h"
#include "../include/InkyModel.h"
#include "../include/PinkyModel.h"
#include "../include/BlinkyModel.h"


logic::World::World(const std::shared_ptr<GameFactory>& factory) {
    // initialise the width and height and create all the entities.
    game_factory = factory;
    initialise_maze();
}
void logic::World::initialise_maze() {
    int line = 0;
    std::string maze_line;
    std::ifstream maze_file("../data/maps/map1.txt");
    while (getline(maze_file, maze_line)) {
        if (line == 0) {
            size_t pos = maze_line.find('X');  // zoek de positie van 'X'
            std::string w = maze_line.substr(0, pos);
            width = std::stoi(w);
            std::string h = maze_line.substr(pos + 1);
            height = std::stoi(h);
            line++;
        }
        else {
            std::vector<std::shared_ptr<Subject>> line_vector;
            line_vector.reserve(width);
            for (int char_idx = 0; char_idx < maze_line.length() && char_idx < width; ++char_idx) {
                // X-positie van -1 (links) naar +1 (rechts)
                float x_pos = 2.0f * (static_cast<float>(char_idx)) / static_cast<float>(width) - 1.0f;

                // Y-positie van +1 (boven) naar -1 (onder)
                float y_pos = 1.0f - 2.0f * (static_cast<float>(line)) / static_cast<float>(height);
                std::shared_ptr<Subject> crnt_entity = nullptr;
                switch (maze_line[char_idx]) {
                case 'W': { // Wall
                    crnt_entity = game_factory->createWall(false);
                    break;
                }
                case 'C': { // Coin
                    crnt_entity = game_factory->createCoin();
                    break;
                }
                case 'B': { // Blinky
                    crnt_entity = game_factory->createGhost(GhostType::Blinky, width, height);
                    blinky = std::dynamic_pointer_cast<BlinkyModel>(crnt_entity);
                    break;
                }
                case 'P': { // Pinky
                    crnt_entity = game_factory->createGhost(GhostType::Pinky, width, height);
                    pinky = std::dynamic_pointer_cast<PinkyModel>(crnt_entity);
                    break;
                }
                case 'I': { // Inky
                    crnt_entity = game_factory->createGhost(GhostType::Inky, width, height);
                    inky = std::dynamic_pointer_cast<InkyModel>(crnt_entity);
                    break;
                }
                case 'O': { // Clyde
                    crnt_entity = game_factory->createGhost(GhostType::Clyde, width, height);
                    clyde = std::dynamic_pointer_cast<GhostModel>(crnt_entity);
                    break;
                }
                case 'F': { // Fruit
                    crnt_entity = game_factory->createFruit();
                    break;
                }
                case 'A': { // Pacman
                    crnt_entity = game_factory->createPacman(width, height);
                    pacman = std::dynamic_pointer_cast<PacmanModel>(crnt_entity);
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
                    crnt_entity->set_position({x_pos, y_pos});
                }
            }
            entities.emplace_back(line_vector);
            line++;
        }
    }
    maze_file.close();
}

bool logic::World::check_collision(Coordinate& entity_pos, Rectangle entity2_rect, double entity_speed) {
    float entity_half_size_x = (1.f/float(width));
    float entity_half_size_y = (1.f/float(height));

    // Create scaled epsilon values proportional to the entity size on each axis.
    const float epsilon_x = entity_half_size_x * entity_speed*8.3;
    const float epsilon_y = entity_half_size_y * entity_speed*8.3;
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


bool logic::World::check_wall_collision(Coordinate& entity_pos, Direction& entity_direction, double entity_speed, bool ghost) {
    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) {
            std::shared_ptr<WallModel> wall_model = std::dynamic_pointer_cast<WallModel>(entity);
            if (wall_model) {
                // Define the wall's bounding box (remains the same).
                float entity_half_size_x = (1.f/float(width));
                float entity_half_size_y = (1.f/float(height));
                Coordinate entity2_left_upper_corner = {wall_model->get_position().getX() - entity_half_size_x,
                    wall_model->get_position().getY() - entity_half_size_y};
                Coordinate entity2_right_lower_corner = {wall_model->get_position().getX() + entity_half_size_x,
                    wall_model->get_position().getY() + entity_half_size_y};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (ghost && wall_model->has_ghost_acces() && entity_direction == Direction::North) {}
                else if (check_collision(entity_pos, entity2_rect, entity_speed)) {
                    return true;
                }
            }
        }
    }
    return false; // No collision.
}

bool logic::World::check_coin_collision(Coordinate& entity_pos, double entity_speed) {
    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) {
            std::shared_ptr<CoinModel> coin_model = std::dynamic_pointer_cast<CoinModel>(entity);
            if (coin_model) {
                // Define the wall's bounding box (remains the same).
                Coordinate entity2_left_upper_corner = {coin_model->get_position().getX(),
                    coin_model->get_position().getY()};
                Coordinate entity2_right_lower_corner = {coin_model->get_position().getX(),
                    coin_model->get_position().getY()};
                Rectangle entity2_rect = {entity2_left_upper_corner, entity2_right_lower_corner};
                if (check_collision(entity_pos, entity2_rect, entity_speed)) {
                    remove_entity(coin_model);
                    return true;
                }
            }
        }
    }
    return false; // No collision.
}

void logic::World::remove_entity(std::shared_ptr<CoinModel> model) {
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
    pacman->update(delta_time, *this);
    pinky->update(delta_time, *this);
    inky->update(delta_time, *this);
    blinky->update(delta_time, *this);
    clyde->update(delta_time);
}

[[nodiscard]] logic::Direction logic::World::get_pacman_direction() const {
    return pacman->get_direction();
}
[[nodiscard]] Coordinate logic::World::get_pacman_position() const {
    return pacman->get_position();
}