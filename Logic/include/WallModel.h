//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "Subject.h"
#include "../../Utilities/utils.h"

namespace logic {
class WallModel : public Subject {
     Coordinate position;

public:
    WallModel() = default;
    explicit WallModel(Coordinate pos) : position(pos) {}

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& pos) { this->position = pos; }
};
} // namespace logic
#endif // PACMAN_WALLMODEL_H
