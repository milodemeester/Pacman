//
// Created by milod on 30/10/2025.
//
#include "../include/State.h"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <utility>

std::pair<bool, State*> MenuState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    /*if (event->is<sf::Event::MouseButtonPressed>()) {
        auto clicked = event->getIf<sf::Event::MouseButtonPressed>();
        double click_x = clicked->position.x;
        double click_y = clicked->position.y;
    }*/
    //LevelState* level_state = state_factory->create_level_state();
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    return output;
}

std::pair<bool, State*> PausedState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    // sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    /*if (key == sf::Keyboard::Key::M) { //TODO: this is not right, there should be an option, but for now it is M or L pressed
        output.first = true;
        output.second = state_factory->create_menu_state();
    }
    else if (key == sf::Keyboard::Key::L) {
        output.first = true;
        output.second = state_factory->create_level_state();
    }*/
    return output;
}


std::pair<bool, State*> LevelState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    // sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    //if (key == sf::Keyboard::Key::Escape) {
    //    output.first = true;
    //    output.second = state_factory->create_paused_state();
    //}
    return output;
}

std::pair<bool, State*> VictoryState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    // sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    return output;
}

void MenuState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.openFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text(font);
    text.setString("PLAY");
    float character_size = (window->getSize().x/16 + window->getSize().y/16); // TODO: make this dynamic
    text.setCharacterSize(character_size);
    text.setFillColor(sf::Color::Yellow);
    sf::Vector2u window_size = window->getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().size / 2.f + text.getLocalBounds().position); // set origin to center of the text
    text.setPosition({window_width/2-12, window_height-character_size}); // set position of the text to center of screen
    window->draw(text);
}


void LevelState::render(sf::RenderWindow* window) {}

void PausedState::render(sf::RenderWindow* window) {}

void VictoryState::render(sf::RenderWindow* window) {}

MenuState* StateFactory::create_menu_state() {
    auto* m = new MenuState{};
    return m;
}
LevelState* StateFactory::create_level_state() {
    LevelState* l = new LevelState{};
    return l;
}
PausedState* StateFactory::create_paused_state() {
    auto* p = new PausedState{};
    return p;
}
VictoryState* StateFactory::create_victory_state() {
    VictoryState* v = new VictoryState{};
    return v;
}
