//
// Created by code optimization on 12/7/2025.
//

#ifndef PACMAN_COLLISIONMAP_H
#define PACMAN_COLLISIONMAP_H

#include "../../Utilities/utils.h"
#include <vector>

namespace logic {

/**
 * @brief Pre-computed collision map for static entities (walls)
 * This provides O(1) wall collision detection instead of O(n) iteration
 */
class CollisionMap {
private:
    std::vector<std::vector<bool>> solid_cells_; // true if cell contains a wall
    int width_;
    int height_;

public:
    /**
     * @brief Constructor
     * @param width Grid width in cells
     * @param height Grid height in cells
     */
    CollisionMap(int width, int height);

    /**
     * @brief Mark a cell as solid (contains a wall)
     * @param grid_x X coordinate in grid space
     * @param grid_y Y coordinate in grid space
     */
    void markSolid(int grid_x, int grid_y);

    /**
     * @brief Check if a position collides with a wall
     * @param world_pos Position in world coordinates (normalized -1 to 1)
     * @param world_width Width of the world in cells
     * @param world_height Height of the world in cells
     * @return true if position is inside a solid cell
     */
    bool isWallAt(const Coordinate& world_pos, int world_width, int world_height) const;

    /**
     * @brief Check if a rectangle collides with any wall
     * @param rect Rectangle in world coordinates
     * @param world_width Width of the world in cells
     * @param world_height Height of the world in cells
     * @return true if rectangle intersects any solid cell
     */
    bool isWallCollision(const Rectangle& rect, int world_width, int world_height) const;

private:
    /**
     * @brief Convert world coordinates to grid coordinates
     * @param world_pos Position in world space
     * @param world_width Width of the world in cells
     * @param world_height Height of the world in cells
     * @return Grid coordinates (x, y)
     */
    std::pair<int, int> worldToGrid(const Coordinate& world_pos, int world_width, int world_height) const;
};

} // namespace logic

#endif // PACMAN_COLLISIONMAP_H
