//
// Created by milo on 11/1/25.
//

#include "../include/Score.h"
#include "../include/Stopwatch.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

logic::Score::Score() {
    score_ = 0;
    high_scores_.reserve(5);

    // read top 5 highscores from a file
    std::string line_output;
    std::ifstream file("../data/high_scores.txt");
    if (file) {
        int line_number = 0;
        while (getline(file, line_output) && line_number < 5) {
            high_scores_.push_back(line_output);
            line_number++;
        }
    } else {
        std::cerr << "Could not open high score file" << std::endl;
        exit(1);
    }
}

void logic::Score::onNotify(const Subject& entity, Event& e) {
    if (e == Event::CoinCollected) {
        float standard_increase = 10;
        auto stopwatch = Stopwatch::getInstance();
        auto now = stopwatch->get_now();

        // first coin is score + 10, after this, it is calculated with the time passed
        if (first_coin_collected == false) {
            first_coin_collected = true;
            score_ += standard_increase;
        } else {
            float time_between = stopwatch->get_time_between(now, previous_coin_time);
            score_ += std::lround(standard_increase * (1 / (time_between / 1000)));
        }
        previous_coin_time = now;
    } else if (e == Event::FruitEaten) {
        score_ += 50;
    }
}

std::vector<std::string> logic::Score::get_high_scores() { return high_scores_; }

int logic::Score::get_score() const { return score_; }

void logic::Score::update_high_scores() {
    bool needs_update = false;
    int update_index = 0;
    // check if the current score is higher than any of the current high scores
    for (int i = 0; i < high_scores_.size(); i++) {
        int score = std::stoi(high_scores_[i]);
        if (score_ > score) {
            // Remember the index
            needs_update = true;
            update_index = i;
            break;
        }
    }
    // if the current score is bigger than one of the high scores, update the high_scores_ vector
    if (needs_update) {
        std::vector<std::string> copy = high_scores_;
        high_scores_[update_index] = std::to_string(score_);
        for (int i = update_index + 1; i < 5; i++) {
            high_scores_[i] = copy[i - 1];
        }
        write_to_file(high_scores_);
    }
}

void logic::Score::write_to_file(std::vector<std::string>& new_high_scores) {
    std::ofstream file("../data/high_scores.txt");
    if (file.is_open()) {
        for (auto& string : new_high_scores) {
            file << string << std::endl;
        }
    }
}

void logic::Score::reset() { score_ = 0; }