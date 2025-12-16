//
// Created by milo on 11/18/25.
//

#include "../include/Random.h"
#include <random>

namespace logic::core {
Random::Random() : mt(std::random_device{}()) {}

std::shared_ptr<Random> Random::getInstance() {
    if (random_ == nullptr) {
        random_ = std::shared_ptr<Random>(new Random());
    }
    return random_;
}

int Random::getNumber(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
}