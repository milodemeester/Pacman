//
// Created by milod on 30/10/2025.
//

#include "../include/World.h"
#include "../include/GhostModel.h"
#include "../include/PacmanModel.h"
#include "../include/Subject.h"
#include "../include/WallModel.h"
#include "../include/FruitModel.h"
#include "../include/CoinModel.h"

logic::World::World(const std::shared_ptr<GameFactory>& factory) { // initialise the width and height and create all the entities.
    game_factory = factory;
    initialise_maze();
}

void logic::World::initialise_maze() {
    int line = -1;
    int character = 0;
    std::string maze_line;
    std::ifstream maze_file("../data/maps/map1.txt");
    while (getline(maze_file, maze_line)) {
        if (line == -1) {
            size_t pos = maze_line.find('X');  // zoek de positie van 'X'
            std::string w = maze_line.substr(0, pos);
            width = std::stoi(w);
            std::string h = maze_line.substr(pos + 1);
            height = std::stoi(h);
            line++;
        }
        else {
            std::vector<std::shared_ptr<Subject>> line_vector;
            line_vector.reserve(width+1);
            line++;
            character = -1;
            for (char entity : maze_line) {
                switch (entity) {
                case 'W': { // Wall
                    character++;
                    auto wall = game_factory->createWall();
                    wall->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(wall);
                    break;
                }
                case 'C': { // Coin
                    character++;
                    auto coin = game_factory->createCoin();
                    coin->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(coin);
                    break;
                }
                case 'B': { // Blinky
                    character++;
                    auto blink = game_factory->createGhost("Blinky");
                    blink->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(blink);
                    blinky = blink;
                    break;
                }
                case 'P': { // Pinky
                    character++;
                    auto pink = game_factory->createGhost("Pinky");
                    pink->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(pink);
                    pinky = pink;
                    break;
                }
                case 'I': { // Inky
                    character++;
                    auto ink = game_factory->createGhost("Inky");
                    ink->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(ink);
                    inky = ink;
                    break;
                }
                case 'O': { // Clyde
                    character++;
                    auto clyd = game_factory->createGhost("Clyde");
                    clyd->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(clyd);
                    clyde = clyd;
                    break;
                }
                case 'F': { // Fruit
                    character++;
                    auto fruit = game_factory->createFruit();
                    fruit->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.push_back(fruit);
                    break;
                }
                case 'A': { // Pacman
                    character++;
                    auto pac = game_factory->createPacman();
                    pac->set_position({2*(float(character)/width)-1, 2*(float(line-1)/height)-1}); // coordinaten op [-1,1]
                    line_vector.emplace_back(pac);
                    pacman = pac;
                    break;
                }
                case 'Z': { // Niets
                    character++;
                    break;
                }
                default:;
                }
            }
            entities.emplace_back(line_vector);
        }
    }
    maze_file.close();
}

void logic::World::move_left() {
    pacman->set_direction(Direction::West);
}
void logic::World::move_right() {
    pacman->set_direction(Direction::East);
}
void logic::World::move_down() {
    pacman->set_direction(Direction::South);
}
void logic::World::move_up() {
    pacman->set_direction(Direction::North);
}

void nothing() {
    int one;
    one = 1;
    one++;
}


void logic::World::update(double delta_time) {
    auto new_pos = pacman->update(delta_time);
    bool blocked = false;
    for (auto& vec : entities) {
        for (auto& entity : vec) {
            Rectangle pac_rectangle(pacman->get_position(), {pacman->get_position().getX()+(1.f/float(width)), pacman->get_position().getY()+(1.f/float(height))});
            Rectangle entity_rectangle(entity.get()->get_position(), {entity.get()->get_position().getX()+(1.f/float(width)), entity.get()->get_position().getY()+(1.f/float(height))});
            if (utils::intersecting(pac_rectangle, entity_rectangle)) {
                if (std::dynamic_pointer_cast<WallModel>(entity)) {
                    blocked = true;
                    // Do not update location of pacman, because wall is in the way
                }
            }
        }
    }
    if (!blocked) {
        pacman->set_position(new_pos);
    }
}