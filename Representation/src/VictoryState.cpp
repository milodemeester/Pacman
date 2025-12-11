//
// Created by milo on 11/1/25.
//

#include "../include/VictoryState.h"

#include "../../Utilities/utils.h"
#include "../include/StateManager.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

representation::VictoryState::VictoryState(StateManager& sm) : State(sm) {
    texture_.loadFromFile("../data/textures/victory_state_img.png");
}

void representation::VictoryState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    } else if (event.type == sf::Event::MouseButtonPressed) {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        sf::Vector2f mouseCoords = {x, y};
        // check if the click is inside the button boundries
        Coordinate ulc = {button_.btnLeft_, button_.btnTop_};
        Coordinate lrc = {button_.btnRight_, button_.btnBottom_};
        Coordinate click = {mouseCoords.x, mouseCoords.y};
        if (utils::contains(ulc, lrc, click)) {
            manager_.pop_state();
        }
    }
}

void representation::VictoryState::render(sf::RenderWindow& window) {
    // Load and draw the image
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
    float spriteTop = (size.y - scaledH) / 2.f;

    // button boundries (used to calculate if a mouse click falls inside these boundries
    button_.btnLeft_ = spriteLeft + scaledW * 0.13f;
    button_.btnTop_ = spriteTop + scaledH * 0.67f;
    button_.btnRight_ = spriteLeft + scaledW * 0.87f;
    button_.btnBottom_ = spriteTop + scaledH * 0.74f;

    sf::RectangleShape rect;
    rect.setPosition(button_.btnLeft_, button_.btnTop_);
    rect.setSize(sf::Vector2f(button_.btnRight_ - button_.btnLeft_, button_.btnBottom_ - button_.btnTop_));
    rect.setFillColor(sf::Color::Transparent); // geen fill
    rect.setOutlineColor(sf::Color::Yellow);   // rode outline
    rect.setOutlineThickness(5.f);             // wat dikker

    window.draw(rect);
}
