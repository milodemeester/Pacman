//
// Created by milo on 11/20/25.
//

#include <vector>
#include <algorithm>
#include <limits>
#include "../include/PinkyModel.h"
#include "../include/World.h"
#include "../include/Random.h" // Nodig voor willekeur

logic::PinkyModel::PinkyModel(Coordinate pos, Direction dir, int world_width, int world_height) : Type2Ghost(pos, dir, world_width, world_height) {
    wait_time = 0;
}