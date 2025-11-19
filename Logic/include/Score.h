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
    bool first_coin_collected = false; // when the first coin is collected, this becomes true
    std::chrono::system_clock::time_point previous_coin_time; // the time the previous coin was collected
    std::vector<std::string> high_scores_; // all of the high scores stored in a vector with size 5
    int score; // the current score of thid game

public:
    /**
     * @brief constructor that gets all the high-scores from a data file
     */
    Score();

    /**
     * @brief event-handling
     * @param entity the entity where the event is sent from
     * @param event the event that occured
     */
    void onNotify(const Subject& entity, Event& event) override;

    /**
     * @return the high_scores
     */
    std::vector<std::string> get_high_scores();

    /**
     * @return the current score
     */
    int get_score() const;
};
} // namespace logic

#endif // PACMAN_SCORE_H
