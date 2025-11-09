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


logic::World::World(const std::shared_ptr<GameFactory>& factory) {
    // initialise the width and height and create all the entities.
    game_factory = factory;
    initialise_maze();
}

void logic::World::initialise_maze() {
    int line_idx = -1; // Gebruik een duidelijkere naam
    std::string maze_line;
    std::ifstream maze_file("../data/maps/map1.txt");
    while (getline(maze_file, maze_line)) {
        if (line_idx == -1) {
            size_t pos = maze_line.find('X');
            std::string w = maze_line.substr(0, pos);
            width = std::stoi(w);
            std::string h = maze_line.substr(pos + 1);
            height = std::stoi(h);
            line_idx++; // Ga naar de eerste content-lijn
        }
        else {
            std::vector<std::shared_ptr<Subject>> line_vector;
            line_vector.reserve(width); // Reserveer ruimte voor de rij

            for (int char_idx = 0; char_idx < maze_line.length() && char_idx < width; ++char_idx) {
                // X-positie van -1 (links) naar +1 (rechts)
                float x_pos = 2.0f * (static_cast<float>(char_idx) + 0.5f) / static_cast<float>(width) - 1.0f;

                // Y-positie van +1 (boven) naar -1 (onder)
                float y_pos = 1.0f - 2.0f * (static_cast<float>(line_idx) + 0.5f) / static_cast<float>(height);

                std::shared_ptr<Subject> current_entity = nullptr;
                switch (maze_line[char_idx]) {
                    case 'W': current_entity = game_factory->createWall(); break;
                    case 'C': current_entity = game_factory->createCoin(); break;
                    case 'B': current_entity = game_factory->createGhost("Blinky"); blinky = std::dynamic_pointer_cast<GhostModel>(current_entity); break;
                    case 'P': current_entity = game_factory->createGhost("Pinky"); pinky = std::dynamic_pointer_cast<GhostModel>(current_entity); break;
                    case 'I': current_entity = game_factory->createGhost("Inky"); inky = std::dynamic_pointer_cast<GhostModel>(current_entity); break;
                    case 'O': current_entity = game_factory->createGhost("Clyde"); clyde = std::dynamic_pointer_cast<GhostModel>(current_entity); break;
                    case 'F': current_entity = game_factory->createFruit(); break;
                    case 'A': current_entity = game_factory->createPacman(); pacman = std::dynamic_pointer_cast<PacmanModel>(current_entity); break;
                    default: break; // Lege ruimte
                }

                if (current_entity) {
                    current_entity->set_position({x_pos, y_pos});
                }
                // Voeg de entity toe (of nullptr als het een lege ruimte is)
                line_vector.push_back(current_entity);
            }
            entities.emplace_back(line_vector);

            // VERHOOG HIER DE INDEX, AAN HET EIND VAN HET VERWERKEN VAN EEN RIJ
            line_idx++;
        }
    }
    maze_file.close();
    if (pacman) {
        pacman->set_world_dimensions(width, height);
    }
}

bool logic::World::check_collision(Coordinate& entity_pos, double entity_speed) {
    float entity_half_size_x = (1.f/float(width));
    float entity_half_size_y = (1.f/float(height));

    // Create scaled epsilon values proportional to the entity size on each axis.
    const float epsilon_x = entity_half_size_x * entity_speed*8.5;
    const float epsilon_y = entity_half_size_y * entity_speed*8.5;
    // Define the entity's bounding box, shrunk by the scaled epsilon on each axis.
    Coordinate entity_left_upper_corner = {entity_pos.getX() - entity_half_size_x + epsilon_x,
        entity_pos.getY() - entity_half_size_y + epsilon_y};
    Coordinate entity_right_lower_corner = {entity_pos.getX() + entity_half_size_x - epsilon_x,
        entity_pos.getY() + entity_half_size_y - epsilon_y};
    Rectangle entity_rect = {entity_left_upper_corner, entity_right_lower_corner};

    for (auto& entity_vector : entities) {
        for (auto& entity : entity_vector) {
            std::shared_ptr<WallModel> wall_model = std::dynamic_pointer_cast<WallModel>(entity);
            if (wall_model) {
                // Define the wall's bounding box (remains the same).
                Coordinate wall_left_upper_corner = {wall_model->get_position().getX() - entity_half_size_x,
                    wall_model->get_position().getY() - entity_half_size_y};
                Coordinate wall_right_lower_corner = {wall_model->get_position().getX() + entity_half_size_x,
                    wall_model->get_position().getY() + entity_half_size_y};
                Rectangle wall_rect = {wall_left_upper_corner, wall_right_lower_corner};
                if (utils::intersecting(wall_rect, entity_rect)) {
                    return true; // Collision detected.
                }
            }
        }
    }
    return false; // No collision.
}

void logic::World::move_pacman(logic::Direction direction) {
    wanted_pacman_direction = direction;
}


void logic::World::update(double delta_time) {
    // Probeer eerst de gewenste nieuwe richting
    Direction current_direction = pacman->get_direction();

    // Als de speler een nieuwe richting kiest, kijk of die geldig is.
    if (wanted_pacman_direction != current_direction) {
        pacman->set_direction(wanted_pacman_direction);
        Coordinate next_pos_if_turned = pacman->update(float(delta_time));

        // Als de nieuwe richting niet tot een botsing leidt, ga door met die richting.
        if (!check_collision(next_pos_if_turned, pacman->get_speed())) {
            pacman->set_position(next_pos_if_turned);
            return; // Klaar voor deze frame
        }

        // Zo niet, herstel de oude richting en ga verder.
        pacman->set_direction(current_direction);
    }

    // Ga verder met de huidige (of herstelde) richting.
    Coordinate next_pos = pacman->update(float(delta_time));

    // Beweeg alleen als dit niet tot een botsing leidt.
    // Anders stopt Pacman gewoon tegen de muur.
    if (!check_collision(next_pos, pacman->get_speed())) {
        pacman->set_position(next_pos);
    }
}