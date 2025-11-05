//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_DIRECTION_H
#define PACMAN_DIRECTION_H

namespace logic {
enum class Direction {
    EntityPositionChanged,
    PacmanDirectionChanged,
    PacmanDied,
    GhostEaten,
    CoinCollected,
    FruitEaten
    // ...
};
} // namespace logic

#endif // PACMAN_DIRECTION_H
