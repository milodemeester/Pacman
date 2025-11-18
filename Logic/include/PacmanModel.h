//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "../../Utilities/utils.h"
#include "Subject.h"
#include "World.h"

namespace logic {
class PacmanModel : public MoveableSubject {
public:
    PacmanModel(Coordinate pos, Direction dir, int world_width, int world_height);

    /*
     * Updates pacman
     */
    void update(float dt, World& world) override;

    [[nodiscard]] Coordinate get_position() const { return position_; }
    [[nodiscard]] Direction get_direction() const { return direction_; }

    void set_world_dimensions(int w, int h) {
        world_height_ = h;
        world_width_ = w;
    }
};
} // namespace logic

#endif // PACMAN_PACMAN_H
