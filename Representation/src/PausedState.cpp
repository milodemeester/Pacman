//
// Created by milo on 11/1/25.
//

#include "../include/PausedState.h"
#include "../../Utilities/utils.h"
#include "../include/StateManager.h"
#include "SFML/Graphics/Text.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

representation::PausedState::PausedState(StateManager& sm, sf::Vector2u windowsize) : State(sm) {
    if (!texture_.loadFromFile("../data/textures/paused_state_img.png")) {
        std::cerr << "Error loading texture in pausedstate" << std::endl;
        exit(1);
    }
}

void representation::PausedState::render(sf::RenderWindow& window) {
    // load the image and set right position and scale
    sf::Sprite sprite;
    sprite.setTexture(texture_);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    auto winSize = window.getSize();
    auto local = sprite.getLocalBounds();

    float scaleX = winSize.x / local.width;
    float scaleY = winSize.y / local.height;

    float scale = std::min(scaleX, scaleY);

    sprite.setPosition(winSize.x / 2.f, winSize.y / 2.f);
    sprite.setScale(scale, scale);
    window.draw(sprite);

    float imgW = local.width;
    float imgH = local.height;

    auto size = window.getSize();

    float scaledW = imgW * scale;
    float scaledH = imgH * scale;

    float spriteLeft = (size.x - scaledW) / 2.f;
    float spriteTop  = (size.y - scaledH) / 2.f;

    // ---- button 1 ----
    button1_.btnLeft_   = spriteLeft + scaledW * 0.19f;
    button1_.btnTop_    = spriteTop  + scaledH * 0.79f;
    button1_.btnRight_  = spriteLeft + scaledW * 0.81f;
    button1_.btnBottom_ = spriteTop  + scaledH * 0.87f;

    // ---- button 2 ----
    button2_.btnLeft_   = spriteLeft + scaledW * 0.15f;
    button2_.btnTop_    = spriteTop  + scaledH * 0.67f;
    button2_.btnRight_  = spriteLeft + scaledW * 0.85f;
    button2_.btnBottom_ = spriteTop  + scaledH * 0.76f;
}

void representation::PausedState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseCoords = {float(event.mouseButton.x), float(event.mouseButton.y)};
        // check if the click is inside the button boundries
        Coordinate ulc1{button1_.btnLeft_, button1_.btnTop_};
        Coordinate ulc2{button2_.btnLeft_, button2_.btnTop_};
        Coordinate lrc1{button1_.btnRight_, button1_.btnBottom_};
        Coordinate lrc2{button2_.btnRight_, button2_.btnBottom_};
        Coordinate click{mouseCoords.x, mouseCoords.y};
        if (utils::contains(ulc1, lrc1, click)) {
            // resume button, pop this pausedstate to go back to the game
            manager_.pop_state();
        }
        else if (utils::contains(ulc2, lrc2, click)) {
            // back to menu button, pop this pausedstate and the levelstate to go back to the main menu
            manager_.double_pop_state();
        }
    }
}