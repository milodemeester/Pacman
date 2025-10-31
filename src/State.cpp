//
// Created by milod on 30/10/2025.
//

#include "State.h"

std::pair<bool, State*> MenuState::proces_user_input(const sf::Event::KeyPressed* event, StateFactory* state_factory) {
    LevelState* level_state = state_factory->create_level_state();
    std::pair<bool,State*> output;
    output.first = true;
    output.second = level_state;
    return output;
}

std::pair<bool, State*> LevelState::proces_user_input(const sf::Event::KeyPressed* event, StateFactory* state_factory) {
    sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (key == sf::Keyboard::Key::Escape) {
        output.first = true;
        output.second = state_factory->create_paused_state();
    }
    return output;
}

std::pair<bool, State*> PausedState::proces_user_input(const sf::Event::KeyPressed* event, StateFactory* state_factory) {
    sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (key == sf::Keyboard::Key::M) { //TODO: this is not right, there should be an option, but for now it is M or L pressed
        output.first = true;
        output.second = state_factory->create_menu_state();
    }
    else if (key == sf::Keyboard::Key::L) {
        output.first = true;
        output.second = state_factory->create_level_state();
    }
    return output;
}

std::pair<bool, State*> VictoryState::proces_user_input(const sf::Event::KeyPressed* event, StateFactory* state_factory) {
    sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    return output;
}


LevelState* StateFactory::create_level_state() {
    LevelState* l = new LevelState{};
    return l;
}
MenuState* StateFactory::create_menu_state() {
    auto* m = new MenuState{};
    return m;
}
PausedState* StateFactory::create_paused_state() {
    auto* p = new PausedState{};
    return p;
}
VictoryState* StateFactory::create_victory_state() {
    VictoryState* v = new VictoryState{};
    return v;
}
