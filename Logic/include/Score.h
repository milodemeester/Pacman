//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"
#include <string>
#include <vector>

namespace logic {
class Score : public Observer {
    std::vector<std::string> high_scores_;
    int score;
public:
    Score();
    void onNotify(const Subject& entity, Event& e) override;

    std::vector<std::string> get_high_scores();
    int get_score() const;
};
} // namespace logic

#endif // PACMAN_SCORE_H
