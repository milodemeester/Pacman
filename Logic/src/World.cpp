//
// Created by milod on 30/10/2025.
//


#include "../include/World.h"
#include "../../Representation/include/Entity.h"
#include "../include/Ghost.h"
#include "../include/Pacman.h"

World::World(int w, int h) { // initialise the width and height and create all the entities.
    width = w;
    height = h;
    Coordinate coordinate(w/2, h/2);
    auto* pacman = new Pacman{coordinate, 8};
    pacman->set_position(coordinate);
    entities.push_back(pacman);
    coordinate.set_coordinates(w/3, h/2);
    auto* blinky = new Ghost{"Blinky", coordinate, 8};
    coordinate.set_coordinates(w/2, h/3);
    auto* Pinky = new Ghost{"Pinky", coordinate, 8};
    coordinate.set_coordinates(w/3, h/3);
    auto* Inky = new Ghost{"Inky", coordinate, 8};
    coordinate.set_coordinates(w/4, h/4);
    auto* Clyde = new Ghost{"Clyde", coordinate, 8};
    entities.push_back(blinky);
    entities.push_back(Pinky);
    entities.push_back(Inky);
    entities.push_back(Clyde);
}

void World::update(double delta_time) {
    // check for each entity if they intersect ....
}