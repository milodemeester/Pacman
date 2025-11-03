//
// Created by milod on 30/10/2025.
//

#include "../include/StateManager.h"
#include "../include/MenuState.h"

StateManager::StateManager() {
    std::unique_ptr<MenuState> menu_state = std::make_unique<MenuState>();
    state_stack.push(std::move(menu_state));
}

void StateManager::process_event(const sf::Event& key_pressed, sf::RenderWindow& window) {
    if (state_stack.empty()) return;

    // get gebruiken anders krijg je seg errors
    State* crnt_state = state_stack.top().get();
    auto processed = crnt_state->proces_user_input(key_pressed, window);

    int stack_pops = processed.first;
    while (stack_pops > 0 && !state_stack.empty()) {
        state_stack.pop();
        stack_pops--;
    }

    if (processed.second) { // push nieuwe state als die er is
        state_stack.push(std::move(processed.second));
    }
}

void StateManager::render(sf::RenderWindow& window) {
    if (state_stack.empty()) return;
    state_stack.top()->render(window);
}

void StateManager::update(double delta_time) {
    if (state_stack.empty()) return;
    state_stack.top()->update(delta_time);
}