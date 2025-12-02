//
// Created by milod on 31/10/2025.
//

#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H
#include "../../Utilities/utils.h"
#include <SFML/System/Vector2.hpp>

#include <utility>

namespace representation {
class Camera {
public:
    // constructor
    Camera() = default;

    /**
     * @brief converts word-coordinates to screen-coordinates
     * @param worldPos the position of something in a world
     * @param char_size the size of the entity
     * @return a screen-coordinate
     */
    std::pair<sf::Vector2f, sf::Vector2f> worldToScreen(Coordinate worldPos, sf::Vector2f char_size) const;

    /**
     * @brief calculates and updates the layout-size using the window size (this function need to be called on
     * construction of level and on every resize event)
     * @param windowSize the size of the window
     * @param worldSize the size of the world
     */
    void updateScreenSize(sf::Vector2u windowSize, sf::Vector2f worldSize);

    // getters
    [[nodiscard]] float getBoardBottomY() const;
    [[nodiscard]] float getBoardLeftX() const;
    [[nodiscard]] float getBlockSize() const;
    [[nodiscard]] sf::Vector2f get_world_size() const { return worldSize; }

    // setters
    void set_world_size(const sf::Vector2f& world_size) { worldSize = world_size; }

private:
    float board_bottom_y_ = 0.f;         // the bottom of the world on (screen coordinate)
    float top_offset_ = 0.f;             // the offset in pixels from window-top to world-top
    float left_offset_ = 0.f;            // the offset in pixels from window-left to world-left
    float board_width_in_pixels_ = 0.f;  // the width of the world in pixels on the scren
    float board_height_in_pixels_ = 0.f; // the height of the world in pixels on the scren
    float block_size_ = 0.f;             // the size of one entity

    sf::Vector2f worldSize;           // the size of the world
    sf::Vector2f center = {0.f, 0.f}; // the middlepoint of the camera in world-coordinates
    sf::Vector2f size = {2.f, 2.f};   // The width and height of the view in world-coordinates
};
} // namespace representation

#endif // PACMAN_CAMERA_H