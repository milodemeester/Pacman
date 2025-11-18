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
    explicit CoinModel(Coordinate pos) : Subject(pos) {}
    CoinModel() : Subject({0, 0}) {}

    void destruct();
};
} // namespace logic

#endif // PACMAN_COINMODEL_H
