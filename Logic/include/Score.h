//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"

namespace logic {
class Score : public Observer {
    int score;
public:
    Score() = default;
    void onNotify(const Subject& entity, Event& e) override;
};
} // namespace logic

#endif // PACMAN_SCORE_H
