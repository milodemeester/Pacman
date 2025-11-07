//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Subject.h"
#include "../../Utilities/utils.h"

namespace logic {
class PacmanModel : public Subject {
    double speed = 0.000061; // measured in pixel/ms

public:
    PacmanModel() = default;
    PacmanModel(Coordinate pos, Direction dir);

    /*
     * Gives back the new coordinate to change location
     */
    Coordinate update(float dt);

    [[nodiscard]] Coordinate get_position() const { return position; }
    [[nodiscard]] Direction get_direction() const { return direction; }

    void set_position(const Coordinate& pos);
    void set_direction(Direction dir);
};
} // namespace logic

#endif // PACMAN_PACMAN_H
