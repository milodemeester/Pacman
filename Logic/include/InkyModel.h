//
// Created by milo on 11/18/25.
//

#ifndef PACMAN_INKYMODEL_H
#define PACMAN_INKYMODEL_H
#include "GhostModel.h"

namespace logic {
class InkyModel : public GhostModel {
    /**
     * @brief computes all the directions that are not the current direction
     * @param dir the direction that the ghost is currently travelling in
     * @return a vector of directions
     */
    std::vector<logic::Direction> get_other_direction(logic::Direction dir);

    /**
     * @brief computes the opposite direction of the direction that the ghost is currently travelling at
     * @param dir the direction that the ghost is currently travelling in
     * @return a direction
     */
    logic::Direction get_opposite_direction(logic::Direction dir);
public:
    // constructor
    InkyModel(Coordinate pos, Direction dir, int world_width, int world_height);

    /**
     * @brief updates the location (and possibly the direction) of the ghost
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     */
    void update(float dt, World& world) override;

    /**
     * @brief Calculates the next Coordinate and Direction based on the direction options
     * @param current_direction the direction that the ghost is currently travelling in
     * @param current_location the location that the ghost is currently at
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     * @return a pair of the new direction and new coordinate
     */
    std::pair<Direction,Coordinate> get_viable_state(Direction& current_direction, Coordinate& current_location, float dt, World& world);
};
}
#endif // PACMAN_INKYMODEL_H
