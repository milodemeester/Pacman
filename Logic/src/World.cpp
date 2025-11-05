//
// Created by milod on 30/10/2025.
//

#include "../include/World.h"
#include "../include/GhostModel.h"
#include "../include/PacmanModel.h"
#include "../include/Subject.h"
#include "../include/WallModel.h"

logic::World::World(const std::shared_ptr<GameFactory>& factory, int w,
                    int h) { // initialise the width and height and create all the entities.
    width = w;
    height = h;
    auto pac = factory->createPacman();
    pacman = std::move(pac);
    auto blink = factory->createGhost("Blinky");
    blinky = std::move(blink);
    auto pink = factory->createGhost("Pinky");
    pinky = std::move(pink);
    auto ink = factory->createGhost("Inky");
    inky = std::move(ink);
    auto clyd = factory->createGhost("Clyde");
    clyde = std::move(clyd);
    game_factory = factory;

}


void logic::World::update(double delta_time) {
    // move movable entities
    //...

    // check for each entity if they intersect ....
}