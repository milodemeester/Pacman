//
// Created by milod on 31/10/2025.
//

#include "../include/Camera.h"

#include <algorithm>
std::pair<sf::Vector2f, sf::Vector2f> representation::Camera::worldToScreen(
    Coordinate worldPos,
    sf::Vector2u windowSize,
    sf::Vector2f worldSize,
    sf::Vector2f char_size) const
{
    // Square in window
    int square_length = std::min(windowSize.x, windowSize.y);
    int x_balk = windowSize.x - square_length;
    int y_balk = windowSize.y - square_length;

    // Grootste dimensie voor vierkante blocks
    float block_size = square_length / std::max(worldSize.x, worldSize.y);

    // Gehele speelbord in pixels
    float board_width_in_pixels = block_size * worldSize.x;
    float board_height_in_pixels = block_size * worldSize.y;

    // Extra ruimte in vierkant (centering)
    float extra_x = square_length - board_width_in_pixels;
    float extra_y = square_length - board_height_in_pixels;

    // Offsets inclusief balk én centering binnen vierkant
    float offset_x = x_balk / 2 + extra_x / 2;
    float offset_y = y_balk / 2 + extra_y / 2;

    // Overzetting van [-1,1] naar [0,1]
    float x_norm = (worldPos.getX()+1)/2;
    float y_norm = (worldPos.getY()+1)/2;

    float screen_x = offset_x + x_norm * board_width_in_pixels;
    float screen_y = offset_y + y_norm * board_height_in_pixels;

    // Scale voor entities
    sf::Vector2f scale(block_size / char_size.x, block_size / char_size.y);

    return {sf::Vector2f(screen_x, screen_y), scale};
}