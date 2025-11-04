//
// Created by milod on 30/10/2025.
//


#include "../include/World.h"
#include "../include/Entity.h"
#include "../include/Ghost.h"
#include "../include/Pacman.h"
#include "../include/Wall.h"

World::World(const std::shared_ptr<GameFactory>& factory, int w, int h) { // initialise the width and height and create all the entities.
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

    // MAP AANMAKEN EN COINS EN FRUITS
}

void World::update(double delta_time) {
    // move movable entities
    //...

    // check for each entity if they intersect ....
    Rectangle pacman_rectangle(pacman->get_top_left(), pacman->get_bottom_right());
    for (auto& wall : walls) {
        if (utils::intersecting(pacman_rectangle, Rectangle(wall->get_top_left(), wall->get_bottom_right()))) {
            // intersects; do something
        }
    }
}