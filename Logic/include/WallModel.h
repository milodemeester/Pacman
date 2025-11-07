//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "Subject.h"
#include "../../Utilities/utils.h"

namespace logic {
class WallModel : public Subject {
public:
    WallModel() : Subject({0, 0}, Direction::North) {}
    explicit WallModel(Coordinate pos) : Subject(pos, Direction::North) {}

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& pos) { this->position = pos; }
};
} // namespace logic
#endif // PACMAN_WALLMODEL_H
