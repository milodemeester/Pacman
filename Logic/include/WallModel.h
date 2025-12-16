//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "../Utilities/utils.h"
#include "Subject.h"

namespace logic::entity {
class WallModel : public Subject {
    bool ghost_access_; // if true, ghosts can escape it, but not enter
public:
    // constructor
    explicit WallModel(bool ghost_access)
        : Subject({0, 0}, core::Direction::NoDirection), ghost_access_(ghost_access) {}
    explicit WallModel(Coordinate pos, bool ghost_access)
        : Subject(pos, core::Direction::NoDirection), ghost_access_(ghost_access) {}

    /**
     * @return bool that determines if the ghost can pass through
     */
    bool has_ghost_acces() const { return ghost_access_; }

    [[nodiscard]] EntityType get_type() const override { return EntityType::Wall; };
};
} // namespace logic::entity
#endif // PACMAN_WALLMODEL_H
