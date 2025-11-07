//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_COINMODEL_H
#define PACMAN_COINMODEL_H
#include "../../Utilities/utils.h"
#include "Subject.h"

namespace logic {
class CoinModel : public Subject {
public:
    explicit CoinModel(Coordinate pos) : Subject(pos, Direction::North) {}
    CoinModel() : Subject({0,0}, Direction::North) {}

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& pos) { this->position = pos; }
};
} // namespace logic

#endif // PACMAN_COINMODEL_H
