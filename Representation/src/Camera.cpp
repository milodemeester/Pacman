//
// Created by milod on 31/10/2025.
//

#include "../include/Camera.h"
#include <algorithm>
#include <limits>

void representation::Camera::updateScreenSize(sf::Vector2u windowSize, sf::Vector2f worldSize) {
    // Define the game area (upper 90%)
    float bottom_ui_offset = windowSize.y * 0.1f;
    sf::Vector2u game_area_size(windowSize.x, windowSize.y - bottom_ui_offset);

    // Calculate the length of the biggest square that can possibly fit inside the window
    int square_length = std::min(game_area_size.x, game_area_size.y);
    int x_balk = game_area_size.x - square_length;
    int y_balk = game_area_size.y - square_length;

    // Calculate the size of one block and the game area in pixels
    block_size_ = square_length / std::max(worldSize.x, worldSize.y);
    board_width_in_pixels_ = block_size_ * worldSize.x;
    board_height_in_pixels_ = block_size_ * worldSize.y;

    // Calculate the black rectangle INSIDE the square
    float extra_x = square_length - board_width_in_pixels_;
    float extra_y = square_length - board_height_in_pixels_;

    // Calculate the total offset
    left_offset_ = x_balk / 2.0f + extra_x / 2.0f;
    top_offset_ = y_balk / 2.0f + extra_y / 2.0f;

    // Calculate the Y-position of the bottom of the game area (later used to compute the position of the lives, level
    // and score text)
    board_bottom_y_ = top_offset_ + board_height_in_pixels_;
}

std::pair<sf::Vector2f, sf::Vector2f> representation::Camera::worldToScreen(Coordinate worldPos,
                                                                            sf::Vector2f char_size) const {
    // Use the values that were calculated in the updateScreenSize() function
    float x_norm = (worldPos.getX() + 1) / 2.0f;
    float y_norm = (worldPos.getY() + 1) / 2.0f;

    float screen_x = left_offset_ + x_norm * board_width_in_pixels_;
    float screen_y = top_offset_ + y_norm * board_height_in_pixels_;

    sf::Vector2f scale(block_size_ / char_size.x, block_size_ / char_size.y);

    return {sf::Vector2f(screen_x, screen_y), scale};
}

float representation::Camera::getBoardBottomY() const { return board_bottom_y_; }

float representation::Camera::getBoardLeftX() const { return left_offset_; }

[[nodiscard]] float representation::Camera::getBlockSize() const { return block_size_; }