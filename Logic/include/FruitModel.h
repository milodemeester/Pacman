//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_FRUITMODEL_H
#define PACMAN_FRUITMODEL_H
#include "../../Utilities/utils.h"
#include "Subject.h"

namespace logic {
class FruitModel : public Subject {
    Coordinate position;

public:
    // Constructor
    explicit FruitModel(Coordinate pos) : Subject(pos) {}
    FruitModel() : Subject({0, 0}) {}
};
} // namespace logic
#endif // PACMAN_FRUITMODEL_H
