//
// Created by milo on 11/6/25.
//

#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace representation {
// IDEE VAN CHATGPT
class SpriteMap {
public:
    /*
     *Constructor: laadt de sprite sheet vanaf een bestandspad
     */
    explicit SpriteMap(const std::string& filename);

    /*
     * Haalt een sprite op basis van een gedefinieerde rechthoek
     */
    sf::Sprite getSprite(const sf::IntRect& rect);
private:
    sf::Texture m_texture;
};

} // namespace representation

#endif // PACMAN_SPRITEMAP_H
