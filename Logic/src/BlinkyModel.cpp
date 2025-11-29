//
// Created by milo on 11/20/25.
//

#include "../include/BlinkyModel.h"
#include "../include/Stopwatch.h"

logic::BlinkyModel::BlinkyModel(Coordinate pos, Direction dir, int ww, int wh) : Type2Ghost(pos, dir, ww, wh) {
    wait_time = 5000; // 5 seconden voor blinky
}