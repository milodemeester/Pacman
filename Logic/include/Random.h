//
// Created by milo on 11/18/25.
//

#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H
#include <memory>
#include <numeric>
#include <random>

namespace logic {
class Random {
    std::mt19937 mt; // Mersenne Twister
protected:
    inline static std::shared_ptr<Random> random_;
    Random();

public:
    Random(Random& other) = delete;

    static std::shared_ptr<Random> getInstance();

    int getNumber(int min, int max);
};
}

#endif // PACMAN_RANDOM_H
