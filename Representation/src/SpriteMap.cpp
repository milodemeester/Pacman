//
// Created by milo on 11/6/25.
//

#include "../include/SpriteMap.h"
#include <iostream>

representation::SpriteMap::SpriteMap(const std::string& filename) {
    // Load the texture from the file
    if (!m_texture.loadFromFile(filename)) {
        std::cerr << "Error: Kan de sprite sheet niet laden: " << filename << std::endl;
        exit(1);
    }
    if (!wall_texture.loadFromFile("../data/textures/wall.png")) {
        std::cerr << "Error: Kan de sprite sheet niet laden: " << filename << std::endl;
        exit(1);
    }
}

sf::Sprite representation::SpriteMap::getSprite(const sf::IntRect& rect) {
    sf::Sprite sprite(m_texture);
    sprite.setTextureRect(rect);
    return sprite;
}

sf::Sprite representation::SpriteMap::getWallSprite(const sf::IntRect& rect) {
    sf::Sprite sprite(wall_texture);
    sprite.setTextureRect(rect);
    return sprite;
}