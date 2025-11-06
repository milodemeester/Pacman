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

logic::World::World(const std::shared_ptr<GameFactory>& factory, int w,
                    int h) { // initialise the width and height and create all the entities.
    width = w;
    height = h;
    entities.reserve(h+1); // reserve space for total # of entities
    game_factory = factory;
    initialise_maze();
}

void logic::World::initialise_maze() {
    int line = 0;
    int character = 1;
    std::string maze_line;
    std::ifstream maze_file("../data/maps/map1.txt");
    while (getline(maze_file, maze_line)) {
        if (line == 0) {
            // Do the first line width height (initialise width & height)
        }
        std::vector<std::shared_ptr<Subject>> line_vector;
        line_vector.reserve(width+1);
        line++;
        for (char entity : maze_line) {
            switch (entity) {
            case 'W': { // Wall
                auto wall = game_factory->createWall();
                wall->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(wall);
                break;
            }
            case 'O': { // Coin
                auto coin = game_factory->createCoin();
                coin->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(coin);
                break;
            }
            case 'B': { // Blinky
                auto blink = game_factory->createGhost("Blinky");
                blink->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(blink);
                blinky = blink;
                break;
            }
            case 'P': { // Pinky
                auto pink = game_factory->createGhost("Pinky");
                pink->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(pink);
                pinky = pink;
                break;
            }
            case 'I': { // Inky
                auto ink = game_factory->createGhost("Inky");
                ink->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(ink);
                inky = ink;
                break;
            }
            case 'C': { // Clyde
                auto clyd = game_factory->createGhost("Clyde");
                clyd->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(clyd);
                clyde = clyd;
                break;
            }
            case 'F': { // Fruit
                auto fruit = game_factory->createFruit();
                fruit->set_position({float(character)/width, float(line)/height});
                line_vector.push_back(fruit);
                break;
            }
            case 'A': { // Pacman
                auto pac = game_factory->createPacman();
                pac->set_position({float(character)/width, float(line)/height});
                line_vector.emplace_back(pac);
                pacman = pac;
                break;
            }
            case 'Z': { // Niets
                break;
            }
            default:;
                }
        }
        entities.emplace_back(line_vector);
    }
    maze_file.close();
}


void logic::World::update(double delta_time) {
    // move movable entities
    //...

    // check for each entity if they intersect ....
}