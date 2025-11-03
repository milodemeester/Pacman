//
// Created by milod on 30/10/2025.
//

#include "../include/StateManager.h"
#include "../include/MenuState.h"

StateManager::StateManager() {
    auto* menu_state = new MenuState();
    state_stack.push(menu_state);
}

void StateManager::process_key_pressed(const sf::Event* key_pressed, sf::RenderWindow* window) {
    State* crnt_state = state_stack.top();
    std::pair<bool, State*> processed = crnt_state->proces_user_input(key_pressed, window);
    if (processed.first) { // pop if true
        state_stack.pop();
    }
    if (processed.second != nullptr) { // if not nullptr, push onto stack
        state_stack.push(processed.second);
    }
}

void StateManager::render(sf::RenderWindow* window) {
    State* crnt_state = state_stack.top();
    crnt_state->render(std::move(window));

}

void StateManager::update(double delta_time) {
    State* crnt_state = state_stack.top();
    crnt_state->update(delta_time);
}