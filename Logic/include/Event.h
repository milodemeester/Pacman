//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_EVENT_H
#define PACMAN_EVENT_H

namespace logic {
namespace core {
/**
 * Class that is used to pass events from Subjects to Observers
 */
enum class Event {
    EntityPositionChanged,
    EntityDirectionChanged,
    PacmanDied,
    GhostEaten,
    CoinCollected,
    FruitEaten,
    EntityDestruct,
    Nothing,
    FearMode,
    ChaseMode,
    EntityReset,
    WallCollide
};
}
} // namespace logic

#endif // PACMAN_EVENT_H
