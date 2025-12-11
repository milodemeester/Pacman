//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_COINMODEL_H
#define PACMAN_COINMODEL_H
#include "../../Utilities/utils.h"
#include "CollectableSubject.h"

namespace logic {
class CoinModel : public CollectableSubject {
public:
    // Constructor
    explicit CoinModel(Coordinate pos) : CollectableSubject(pos) {}
    CoinModel() : CollectableSubject({0, 0}) {}

    [[nodiscard]] EntityType get_type() const override {return EntityType::Coin;};
};
} // namespace logic

#endif // PACMAN_COINMODEL_H
