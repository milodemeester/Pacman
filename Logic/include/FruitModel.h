//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_FRUITMODEL_H
#define PACMAN_FRUITMODEL_H
#include "Subject.h"
#include "../../Utilities/utils.h"

namespace logic {
class FruitModel : public Subject {
    Coordinate position;

public:
    explicit FruitModel(Coordinate pos) : Subject(pos) {}
    FruitModel() : Subject({0,0}) {}

    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& pos) { this->position = pos; }
};
} // namespace logic
#endif // PACMAN_FRUITMODEL_H
