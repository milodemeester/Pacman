//
// Created by milo on 11/1/25.
//

#include "../include/Score.h"
#include "../include/Stopwatch.h"
#include <fstream>
#include <string>
#include <math.h>

logic::Score::Score() {
    score = 0;
    high_scores_.reserve(5);
    std::string line_output;
    std::ifstream file("../data/high_scores.txt");
    int line_number = 0;
    while (getline(file, line_output) && line_number < 5) {
        high_scores_.push_back(line_output);
        line_number++;
    }
}

void logic::Score::onNotify(const Subject& entity, Event& e) {
    if (e == Event::CoinCollected) {
        double standard_increase = 20;
        auto stopwatch = Stopwatch::getInstance();
        auto now = stopwatch->get_now();
        if (first_coin_collected == false) {
            first_coin_collected = true;
            score += standard_increase;
        }
        else {
            double time_between = stopwatch->get_time_between(now, previous_coin_time);
            score += std::lround(standard_increase*(1/(time_between/1000)));
        }
        previous_coin_time = now;
    }
}

std::vector<std::string> logic::Score::get_high_scores() {
    return high_scores_;
}

int logic::Score::get_score() const {
    return score;
}
