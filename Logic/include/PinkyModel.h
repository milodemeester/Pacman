//
// Created by milo on 11/20/25.
//

#ifndef PACMAN_PINKYMODEL_H
#define PACMAN_PINKYMODEL_H
#include "Direction.h"
#include "GhostModel.h"
#include "Type2Ghost.h"

namespace logic {
class World;
class PinkyModel : public Type2Ghost {
public:
    PinkyModel(Coordinate pos, Direction dir, int world_width, int world_height);

    void reset_() override;

    void go_to_center() override;
};
};
#endif // PACMAN_PINKYMODEL_H
