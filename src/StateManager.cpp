//
// Created by milod on 30/10/2025.
//

#include "StateManager.h"

StateManager::StateManager() {
    state_factory = new StateFactory();
    MenuState* menu_state = state_factory->create_menu_state();
    state_stack.push(menu_state);
}

void StateManager::process_key_pressed(const sf::Event::KeyPressed* key_pressed) {
    State* crnt_state = state_stack.top();
    std::pair<bool, State*> processed = crnt_state->proces_user_input(key_pressed, state_factory);
    if (processed.first) { // pop if true
        state_stack.pop();
    }
    if (processed.second != nullptr) { // if not nullptr, push onto stack
        state_stack.push(processed.second);
    }
}
