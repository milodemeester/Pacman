//
// Created by milo on 11/18/25.
//

#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H
#include <memory>
#include <numeric>
#include <random>

namespace logic {
namespace core {
class Random {
protected:
    std::mt19937 mt;                               // Mersenne Twister
    inline static std::shared_ptr<Random> random_; // the singleton instance of the random class

    // constructor
    Random();

public:
    // delete the copy-constructor
    Random(Random& other) = delete;

    /**
     * @return the only instance of the Random class in this program (singleton)
     */
    static std::shared_ptr<Random> getInstance();

    /**
     * @brief computes a random integer between to integers using a Mersenne Twister
     * @param val1 the first value
     * @param val2 the second value
     * @return a random number between val1 and val2
     */
    int getNumber(int val1, int val2);
};
} // namespace core
} // namespace logic

#endif // PACMAN_RANDOM_H
