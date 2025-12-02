//
// Created by milo on 11/6/25.
//

#ifndef PACMAN_SPRITEMAP_H
#define PACMAN_SPRITEMAP_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace representation {
/**
 * IDEE VAN CHATGPT
 */
class SpriteMap {
    sf::Texture m_texture;
    sf::Texture wall_texture;
public:
    // constructor die de sprite inleest
    explicit SpriteMap(const std::string& filename);

    // getters
    sf::Sprite getSprite(const sf::IntRect& rect);
    sf::Sprite getWallSprite(const sf::IntRect& rect);
};

} // namespace representation

#endif // PACMAN_SPRITEMAP_H
