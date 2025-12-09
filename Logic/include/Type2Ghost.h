//
// Created by milo on 11/20/25.
//

#ifndef PACMAN_TYPE2GHOST_H
#define PACMAN_TYPE2GHOST_H
#include "GhostModel.h"
namespace logic {
class Type2Ghost : public GhostModel {
protected:
    /**
     * @brief computes the position in front of pacman
     * @param world
     * @param offset the amount of positions in front of pacman
     * @return
     */
    Coordinate compute_pacman_forward_pos(World& world, float offset);

    bool in_box = true;
public:
    // constructor
    Type2Ghost(Coordinate pos, Direction dir, int world_width, int world_height);

    /**
     * @brief updates the location (and possibly the direction) of the ghost
     * @param dt the delta time between this update and the previous one
     * @param target_location the target location that will be used to calculate the manhatten distance
     * @param world the world this entity lives in
     */
    void update_(float dt, World& world, Coordinate target_location);

    /**
     * @brief Calculates the next Coordinate and Direction based on the direction options
     * @param current_direction the direction that the ghost is currently travelling in
     * @param current_location the location that the ghost is currently at
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     * @param target_location the target location that will be used to calculate the manhatten distance
     * @return a pair of the new direction and new coordinate
     */
    std::pair<Direction, Coordinate> get_viable_state(Direction& current_direction, Coordinate& current_location,
                                                      float dt, World& world, Coordinate target_location);


    void go_to_center() override;
};
} // namespace logic

#endif // PACMAN_TYPE2GHOST_H
