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
    // Constructor
    explicit CoinModel(Coordinate pos) : Subject(pos) {}
    CoinModel() : Subject({0, 0}) {}

    /**
     * @brief this function notifies observers that it is destructed
     */
    void destruct();
};
} // namespace logic

#endif // PACMAN_COINMODEL_H
