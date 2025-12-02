//
// Created by milo on 11/20/25.
//

#ifndef PACMAN_CLYDEMODEL_H
#define PACMAN_CLYDEMODEL_H
#include "GhostModel.h"

namespace logic {
class ClydeModel : public logic::GhostModel {
public:
    // constructor
    ClydeModel(Coordinate pos, logic::Direction dir, int world_width, int world_height);

    /**
     * @brief updates the location (and possibly the direction) of the ghost
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     */
    void update(float dt, logic::World& world) override;

    /**
     * @brief Calculates the next Coordinate and Direction based on the direction options
     * @param current_direction the direction that the ghost is currently travelling in
     * @param current_location the location that the ghost is currently at
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     * @return a pair of the new direction and new coordinate
     */
    std::pair<logic::Direction, Coordinate> get_viable_state(logic::Direction& current_direction,
                                                             Coordinate& current_location, float dt,
                                                             logic::World& world);
};
} // namespace logic
#endif // PACMAN_CLYDEMODEL_H
