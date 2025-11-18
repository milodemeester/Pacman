//
// Created by milo on 11/18/25.
//

#include "../include/Random.h"
#include <random>

logic::Random::Random() : mt(std::random_device{}()) {}

std::shared_ptr<logic::Random> logic::Random::getInstance() {
    if (random_ == nullptr) {
        random_ = std::shared_ptr<Random>(new Random());
    }
    return random_;
}

int logic::Random::getNumber(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
