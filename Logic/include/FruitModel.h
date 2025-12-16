//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_FRUITMODEL_H
#define PACMAN_FRUITMODEL_H
#include "../Utilities/utils.h"
#include "CollectableSubject.h"

namespace logic {
class FruitModel : public CollectableSubject {
public:
    // Constructor
    explicit FruitModel(Coordinate pos) : CollectableSubject(pos) {}
    FruitModel() : CollectableSubject({0, 0}) {}

    [[nodiscard]] EntityType get_type() const override {return EntityType::Fruit;};
};
} // namespace logic
#endif // PACMAN_FRUITMODEL_H
