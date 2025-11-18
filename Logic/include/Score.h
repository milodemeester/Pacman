//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H
#include "Observer.h"
#include <chrono>
#include <string>
#include <vector>

namespace logic {
class Score : public Observer {
    bool first_coin_collected = false;
    std::chrono::system_clock::time_point previous_coin_time;
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
