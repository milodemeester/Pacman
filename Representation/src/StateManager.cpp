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
    std::unique_ptr<State> crnt_state = std::move(state_stack.top());
    std::pair<int, std::unique_ptr<State>> processed = crnt_state->proces_user_input(key_pressed, window);
    int stack_pops = processed.first;
    while (stack_pops > 0) {
        state_stack.pop();
        stack_pops--;
    }
    if (processed.second != nullptr) { // if not nullptr, push onto stack
        state_stack.push(std::move(processed.second));
    }
}

void StateManager::render(sf::RenderWindow& window) {
    std::unique_ptr<State> crnt_state = std::move(state_stack.top());
    crnt_state->render(window);
}

void StateManager::update(double delta_time) {
    std::unique_ptr<State> crnt_state = std::move(state_stack.top());
    crnt_state->update(delta_time);
}