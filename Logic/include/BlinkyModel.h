//
// Created by milo on 11/20/25.
//

#ifndef PACMAN_BLINKYMODEL_H
#define PACMAN_BLINKYMODEL_H
#include "Direction.h"
#include "Type2Ghost.h"
#include "World.h"

namespace logic {
class BlinkyModel : public Type2Ghost {
public:
    BlinkyModel(Coordinate pos, Direction dir, int world_width, int world_height);

    void reset_() override;

    void go_to_center() override;
};
}

#endif // PACMAN_BLINKYMODEL_H
