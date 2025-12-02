//
// Created by milod on 30/10/2025.
//

#include "../include/StateManager.h"
#include "../include/Camera.h"
#include "../include/MenuState.h"

representation::StateManager::StateManager(sf::Vector2u windowSize, std::shared_ptr<logic::Score> score)
    : currentWindowSize(windowSize) {
    std::unique_ptr<MenuState> menu = std::make_unique<MenuState>(*this, currentWindowSize, score);
    push_state(std::move(menu));
}

void representation::StateManager::process_event(const sf::Event& key_pressed, sf::RenderWindow& window) {
    state_stack.top()->proces_user_input(key_pressed, window);
}

bool representation::StateManager::pop_state() {
    if (state_stack.empty()) {
        return false;
    }
    state_stack.pop();
    return true;
}

bool representation::StateManager::double_pop_state() {
    if (state_stack.empty()) {
        return false;
    }
    state_stack.pop();
    if (state_stack.empty()) {
        return false;
    }
    state_stack.pop();
    return true;
}

void representation::StateManager::push_state(std::unique_ptr<State> state) { state_stack.push(std::move(state)); }

void representation::StateManager::render(sf::RenderWindow& window) {
    if (state_stack.empty())
        return;
    state_stack.top()->render(window);
}

void representation::StateManager::update(double delta_time) {
    if (state_stack.empty())
        return;
    state_stack.top()->update(delta_time);
}