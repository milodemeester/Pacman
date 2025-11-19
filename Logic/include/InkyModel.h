//
// Created by milo on 11/18/25.
//

#ifndef PACMAN_INKYMODEL_H
#define PACMAN_INKYMODEL_H
#include "GhostModel.h"

namespace logic {
class InkyModel : public GhostModel {
    std::vector<logic::Direction> get_other_direction(logic::Direction dir);
    logic::Direction get_opposite_direction(logic::Direction dir);
public:
    InkyModel(Coordinate pos, Direction dir, int world_width, int world_height);
    void update(float dt, World& world) override;
    /**
     * @brief Calculates the next Coordinate and Direction based on the direction options
     * @return
     */
    std::pair<Direction,Coordinate> get_viable_state(Direction& current_direction, Coordinate& current_location, float dt, World& world);
};
}
#endif // PACMAN_INKYMODEL_H
