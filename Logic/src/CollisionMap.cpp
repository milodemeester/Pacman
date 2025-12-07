//
// Created by code optimization on 12/7/2025.
//

#include "../include/CollisionMap.h"
#include <algorithm>
#include <cmath>

logic::CollisionMap::CollisionMap(int width, int height) : width_(width), height_(height) {
    solid_cells_.resize(height, std::vector<bool>(width, false));
}

void logic::CollisionMap::markSolid(int grid_x, int grid_y) {
    if (grid_x >= 0 && grid_x < width_ && grid_y >= 0 && grid_y < height_) {
        solid_cells_[grid_y][grid_x] = true;
    }
}

std::pair<int, int> logic::CollisionMap::worldToGrid(const Coordinate& world_pos, int world_width,
                                                      int world_height) const {
    // World coordinates are normalized from -1 to 1
    // Convert to grid coordinates (0 to width-1, 0 to height-1)
    double normalized_x = (world_pos.getX() + 1.0) / 2.0; // 0 to 1
    double normalized_y = (world_pos.getY() + 1.0) / 2.0; // 0 to 1

    int grid_x = static_cast<int>(normalized_x * world_width);
    int grid_y = static_cast<int>(normalized_y * world_height);

    // Clamp to valid range
    grid_x = std::max(0, std::min(grid_x, width_ - 1));
    grid_y = std::max(0, std::min(grid_y, height_ - 1));

    return {grid_x, grid_y};
}

bool logic::CollisionMap::isWallAt(const Coordinate& world_pos, int world_width, int world_height) const {
    auto [grid_x, grid_y] = worldToGrid(world_pos, world_width, world_height);
    return solid_cells_[grid_y][grid_x];
}

bool logic::CollisionMap::isWallCollision(const Rectangle& rect, int world_width, int world_height) const {
    // Check all four corners of the rectangle
    Coordinate top_left = rect.get_top_left();
    Coordinate bottom_right = rect.get_bottom_right();

    // Also check center and midpoints for better accuracy
    Coordinate top_right(bottom_right.getX(), top_left.getY());
    Coordinate bottom_left(top_left.getX(), bottom_right.getY());

    double center_x = (top_left.getX() + bottom_right.getX()) / 2.0;
    double center_y = (top_left.getY() + bottom_right.getY()) / 2.0;
    Coordinate center(center_x, center_y);

    // Check all these points
    std::vector<Coordinate> points_to_check = {top_left, top_right, bottom_left, bottom_right, center};

    for (const auto& point : points_to_check) {
        if (isWallAt(point, world_width, world_height)) {
            return true;
        }
    }

    return false;
}
