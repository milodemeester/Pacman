//
// Created by milod on 31/10/2025.
//

#ifndef PACMAN_CAMERA_H
#define PACMAN_CAMERA_H
#include <SFML/System/Vector2.hpp>

namespace representation {
class Camera {
public:
    // Werkt met genormaliseerde coördinaten
    void setCenter(float normX, float normY) { center = {normX, normY}; }
    void setSize(float normWidth, float normHeight) { size = {normWidth, normHeight}; }

    // De belangrijkste functie: de conversie!
    sf::Vector2f worldToScreen(sf::Vector2f worldPos, sf::Vector2u windowSize) const;
    sf::Vector2f worldSizeToScreenSize(sf::Vector2f worldSize, sf::Vector2u windowSize) const;

private:
    sf::Vector2f center = {0.f, 0.f}; // Het middelpunt van de camera in wereldcoördinaten
    sf::Vector2f size = {2.f, 2.f};   // De 'breedte' en 'hoogte' van de view in wereldcoördinaten
};
} // namespace representation

#endif // PACMAN_CAMERA_H