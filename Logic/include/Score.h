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
namespace core {
class Score : public Observer {
    bool first_coin_collected = false;                        // when the first coin is collected, this becomes true
    std::chrono::system_clock::time_point previous_coin_time; // the time the previous coin was collected
    std::vector<std::string> high_scores_;                    // all of the high scores stored in a vector with size 5
    float score_;                                             // the current score of thid game

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
    void onNotify(const entity::Subject& entity, Event& event) override;

    /**
     * @brief function that updates the high score if necassery
     */
    void update_high_scores();

    /**
     * @brief write new high scores to the proper file
     * @param new_high_scores the new high score vector
     */
    void write_to_file(std::vector<std::string>& new_high_scores);

    /**
     * @brief resets the score
     */
    void reset();

    /**
     * @brief updates every cycle, decreasing the score over time
     */
    void update(float dt);

    /**
     * @brief gives bonus points for clearing a level
     */
    void update_on_win();

    // getters
    std::vector<std::string> get_high_scores();
    int get_score() const;
};
}
} // namespace logic

#endif // PACMAN_SCORE_H
