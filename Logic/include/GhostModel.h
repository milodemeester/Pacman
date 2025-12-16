//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../Utilities/utils.h"
#include "Direction.h"
#include "Subject.h"

#include <chrono>
#include <string>
#include <utility>

namespace logic::entity {
enum class GhostType { Inky, Blinky, Pinky, Clyde };

class GhostModel : public MoveableSubject {
protected:
    /**
     * @brief computes all the directions that are not the current direction
     * @param dir the direction that the ghost is currently travelling in
     * @return a vector of all the directions that are not equal to the current one
     */
    static std::vector<core::Direction> get_other_direction(core::Direction dir);

    /**
     * @brief computes the opposite direction of the direction that the ghost is currently travelling at
     * @param dir the direction that the ghost is currently travelling in
     * @return the direction opposite to the current direction
     */
    static core::Direction get_opposite_direction(core::Direction dir);

    // getters
    float get_speed() override;

    std::chrono::system_clock::time_point initialize_time; // the time_point where this object was initialized
    float wait_time = 0;         // the time the ghost has to wait before it can escape the center
    bool chasing_mode = true;     // false = fear mode, true = chasing mode
    bool was_frightened_ = false; // determines the previous frightened state so a transition can be detected
    bool waiting = true;          // determines if the ghost is waiting in the center of the game
public:
    // constructor
    GhostModel(Coordinate pos, core::Direction dir, int world_width, int world_height);

    /**
     * @brief takes care of the wait_time and puts chasing_mode on true if the wait_time is over
     * @param dt the delta time between this update and the update prior to this one
     */
    void update(float dt, core::World& world);

    /**
     * @brief checks if the ghost is in chasing mode
     * @return a boolean that determines if the ghost is in chasing mode or fear mode
     */
    bool is_chasing_mode();

    [[nodiscard]] EntityType get_type() const override {return EntityType::Ghost;};

    // setters
    void set_fear_mode();
    void set_chase_mode();
};
} // namespace logic

#endif // PACMAN_GHOST_H
