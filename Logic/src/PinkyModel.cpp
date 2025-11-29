//
// Created by milo on 11/20/25.
//

#include "../include/PinkyModel.h"
#include "../include/Random.h" // Nodig voor willekeur
#include "../include/Stopwatch.h"
#include "../include/World.h"
#include <algorithm>
#include <limits>
#include <vector>

logic::PinkyModel::PinkyModel(Coordinate pos, Direction dir, int world_width, int world_height) : Type2Ghost(pos, dir, world_width, world_height) {
    wait_time = 0;
}