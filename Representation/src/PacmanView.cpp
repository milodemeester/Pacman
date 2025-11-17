//
// Created by milo on 11/5/25.
//

#include "../include/PacmanView.h"
#include "../../Logic/include/PacmanModel.h"
#include "../include/Camera.h"
#include "../include/SpriteMap.h"
#include <SFML/Graphics/RenderWindow.hpp>

// Constructor: Sla een referentie naar de SpriteMap op en initialiseer de animaties met IntRects.
representation::PacmanView::PacmanView(const std::shared_ptr<logic::PacmanModel>& model, SpriteMap& sprite_map)
    : sprite_map_(sprite_map) {
    model->addObserver(this);
    world_direction = model->get_direction();
    world_position = model->get_position();

    // Sla alleen de texture-rechthoeken (IntRects) op, GEEN sf::Sprite objecten.
    sf::IntRect pacman_closed_rect(853, 5, 35, 35);
    sf::IntRect open_right1_rect(853, 55, 35, 35);
    sf::IntRect open_right2_rect(853, 105, 35, 35);
    sf::IntRect open_left1_rect(855, 355, 35, 35);
    sf::IntRect open_left2_rect(862, 405, 35, 35);
    sf::IntRect open_down1_rect(852, 205, 35, 35);
    sf::IntRect open_down2_rect(852, 255, 35, 35);
    sf::IntRect open_up1_rect(853, 507, 35, 35);
    sf::IntRect open_up2_rect(853, 564, 35, 35);

    animation_sequences[logic::Direction::East] = {pacman_closed_rect, open_right1_rect, open_right2_rect};
    animation_sequences[logic::Direction::West] = {pacman_closed_rect, open_left1_rect, open_left2_rect};
    animation_sequences[logic::Direction::North] = {pacman_closed_rect, open_up1_rect, open_up2_rect};
    animation_sequences[logic::Direction::South] = {pacman_closed_rect, open_down1_rect, open_down2_rect};
}

// onNotify: Gebruik dynamic_cast om veilig de methodes van PacmanModel aan te roepen.
void representation::PacmanView::onNotify(const logic::Subject& entity, logic::Event& event) {
    auto* model = dynamic_cast<const logic::PacmanModel*>(&entity);
    if (!model) {
        return; // Event is niet afkomstig van een PacmanModel, dus negeren.
    }

    switch (event) {
        case (logic::Event::EntityPositionChanged): {
            world_position = model->get_position();
            break;
        }
        case (logic::Event::EntityDirectionChanged): {
            world_direction = model->get_direction();
            break;
        }
    }
}

// update: Werk de animatie-index bij. Gebruik een referentie om kopiëren te voorkomen.
void representation::PacmanView::update(double dt) {
    animation_timer += dt;
    if (animation_timer > animation_speed) {
        animation_timer = 0.0f;
        const auto& crnt_sequence = animation_sequences.at(world_direction);
        if (!crnt_sequence.empty()) {
            current_sprite_index = (current_sprite_index + 1) % crnt_sequence.size();
        }
    }
}

// draw: Maak de sprite "just-in-time" op de stack met de opgeslagen IntRect.
void representation::PacmanView::draw(sf::RenderWindow& window, std::shared_ptr<Camera> cam) {
    bool d = false;
    if (world_direction == logic::Direction::East) {d = true;}
    if (world_direction == logic::Direction::North) {d = true;}
    if (world_direction == logic::Direction::South) {d = true;}
    if (world_direction == logic::Direction::West) {d = true;}
    if (d == false) {
        return;
    }

    // 1. Haal de vector van rechthoeken op voor de huidige richting.
    const auto& sprite_rects = animation_sequences.at(world_direction);
    if (sprite_rects.empty() || current_sprite_index >= sprite_rects.size()) {
        return; // Veiligheidscheck: doe niets als de animatiedata ongeldig is.
    }

    // 2. Haal de specifieke rechthoek op voor de huidige animatieframe.
    const sf::IntRect& current_rect = sprite_rects.at(current_sprite_index);

    // 3. Maak een nieuwe sprite op de stack. Dit is veilig en efficiënt.
    sf::Sprite sprite = sprite_map_.getSprite(current_rect);

    // 4. Bereken positie en schaal op het scherm.
    auto screen = cam->worldToScreen(world_position, {32, 32});
    sf::Vector2f new_coords = screen.first;
    sf::Vector2f sprite_size = screen.second;

    // 5. Pas de sprite aan en teken hem.
    sprite.setScale(sprite_size);
    sprite.setPosition(new_coords);
    window.draw(sprite);
}