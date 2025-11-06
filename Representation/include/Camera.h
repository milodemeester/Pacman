//
// Created by milod on 31/10/2025.
//

#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H
#include <SFML/System/Vector2.hpp>
#include "../../Utilities/utils.h"

namespace representation {
class Camera {
public:
    // Werkt met genormaliseerde coördinaten
    void setCenter(float normX, float normY) { center = {normX, normY}; }
    void setSize(float normWidth, float normHeight) { size = {normWidth, normHeight}; }

    // De belangrijkste functie: de conversie!
    [[nodiscard]] sf::Vector2f worldToScreen(Coordinate worldPos, sf::Vector2u windowSize, sf::Vector2f worldSize) const;
    [[nodiscard]] sf::Vector2f get_world_size() const { return worldSize; }
    void set_world_size(const sf::Vector2f& world_size) { worldSize = world_size; }

private:
    sf::Vector2f worldSize;
    sf::Vector2f center = {0.f, 0.f}; // Het middelpunt van de camera in wereldcoördinaten
    sf::Vector2f size = {2.f, 2.f};   // De 'breedte' en 'hoogte' van de view in wereldcoördinaten
};
} // namespace representation

#endif // PACMAN_CAMERA_H