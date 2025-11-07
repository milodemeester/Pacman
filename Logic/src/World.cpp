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
    int line = -1;
    int character = 0;
    std::string maze_line;
    std::ifstream maze_file("../data/maps/map1.txt");
    while (getline(maze_file, maze_line)) {
        if (line == -1) {
            // Do the first line width height (initialise width & height)
        }
        std::vector<std::shared_ptr<Subject>> line_vector;
        line_vector.reserve(width+1);
        line++;
        character = -1;
        for (char entity : maze_line) {
            switch (entity) {
            case 'W': { // Wall
                character++;
                auto wall = game_factory->createWall();
                wall->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(wall);
                break;
            }
            case 'C': { // Coin
                character++;
                auto coin = game_factory->createCoin();
                coin->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(coin);
                break;
            }
            case 'B': { // Blinky
                character++;
                auto blink = game_factory->createGhost("Blinky");
                blink->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(blink);
                blinky = blink;
                break;
            }
            case 'P': { // Pinky
                character++;
                auto pink = game_factory->createGhost("Pinky");
                pink->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(pink);
                pinky = pink;
                break;
            }
            case 'I': { // Inky
                character++;
                auto ink = game_factory->createGhost("Inky");
                ink->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(ink);
                inky = ink;
                break;
            }
            case 'O': { // Clyde
                character++;
                auto clyd = game_factory->createGhost("Clyde");
                clyd->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.emplace_back(clyd);
                clyde = clyd;
                break;
            }
            case 'F': { // Fruit
                character++;
                auto fruit = game_factory->createFruit();
                fruit->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
                line_vector.push_back(fruit);
                break;
            }
            case 'A': { // Pacman
                character++;
                auto pac = game_factory->createPacman();
                pac->set_position({2*(float(character)/width)-1, 2*(float(line)/height)-1}); // coordinaten op [-1,1]
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
    maze_file.close();
}


void logic::World::update(double delta_time) {
    // move movable entities
    //...

    // check for each entity if they intersect ....
}