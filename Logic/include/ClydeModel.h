//
// Created by milo on 11/20/25.
//

#ifndef PACMAN_CLYDEMODEL_H
#define PACMAN_CLYDEMODEL_H
#include "GhostModel.h"
#include "Type2Ghost.h"

namespace logic::entity {
class ClydeModel : public Type2Ghost {
public:
    // constructor
    ClydeModel(Coordinate pos, core::Direction dir, int world_width, int world_height);

    /**
     * @brief updates the location (and possibly the direction) of the ghost
     * @param dt the delta time between this update and the previous one
     * @param world the world this entity lives in
     */
    void update(float dt, core::World& world) override;
};
} // namespace logic::entity
#endif // PACMAN_CLYDEMODEL_H
