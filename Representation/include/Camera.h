//
// Created by milod on 31/10/2025.
//

#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H
#include <SFML/System/Vector2.hpp>
#include "../../Utilities/utils.h"

#include <utility>

namespace representation {
class Camera {
public:
    Camera() = default;

    /**
     * @brief Converteert wereldcoördinaten naar schermcoördinaten.
     */
    std::pair<sf::Vector2f, sf::Vector2f> worldToScreen(
        Coordinate worldPos, sf::Vector2f char_size) const;

    /**
     * @brief Berekent en update de layout-afmetingen op basis van de venstergrootte.
     * Deze functie moet worden aangeroepen bij het maken van de state en bij elke resize.
     */
    void updateScreenSize(sf::Vector2u windowSize, sf::Vector2f worldSize);

    /**
     * @brief Geeft de Y-pixelcoördinaat van de onderkant van het speelbord.
     */
    [[nodiscard]] float getBoardBottomY() const;

    [[nodiscard]] sf::Vector2f get_world_size() const { return worldSize; }

    void set_world_size(const sf::Vector2f& world_size) { worldSize = world_size; }
private:
    float board_bottom_y_ = 0.f;
    float top_offset_ = 0.f;
    float left_offset_ = 0.f;
    float board_width_in_pixels_ = 0.f;
    float board_height_in_pixels_ = 0.f;
    float block_size_ = 0.f;

    sf::Vector2f worldSize;
    sf::Vector2f center = {0.f, 0.f}; // Het middelpunt van de camera in wereldcoördinaten
    sf::Vector2f size = {2.f, 2.f};   // De 'breedte' en 'hoogte' van de view in wereldcoördinaten
};
} // namespace representation

#endif // PACMAN_CAMERA_H