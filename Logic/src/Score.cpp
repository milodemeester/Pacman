//
// Created by milo on 11/1/25.
//

#include "../include/Score.h"

#include <fstream>
#include <string>

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

}

std::vector<std::string> logic::Score::get_high_scores() {
    return high_scores_;
}

int logic::Score::get_score() const {
    return score;
}
