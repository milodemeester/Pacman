//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "Subject.h"
#include "../../Utilities/utils.h"

namespace logic {
class WallModel : public Subject {
    bool ghost_access_;
public:
    explicit WallModel(bool ghost_access) : Subject({0, 0}, Direction::North), ghost_access_(ghost_access) {}
    explicit WallModel(Coordinate pos, bool ghost_access) : Subject(pos, Direction::North), ghost_access_(ghost_access) {}

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& pos);
};
} // namespace logic
#endif // PACMAN_WALLMODEL_H
