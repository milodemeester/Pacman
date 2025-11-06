//
// Created by milo on 11/6/25.
//

#include "../include/SpriteMap.h"
#include <iostream>

representation::SpriteMap::SpriteMap(const std::string& filename) {
    // Laad de textuur vanuit het bestand
    if (!m_texture.loadFromFile(filename)) {
        // Geef een foutmelding als het laden mislukt
        std::cerr << "Error: Kan de sprite sheet niet laden: " << filename << std::endl;
        // In een echte game zou je hier de fout op een robuustere manier afhandelen
        exit(1);
    }
}

sf::Sprite representation::SpriteMap::getSprite(const sf::IntRect& rect) {
    // Maak een sprite, geef het de 'master' textuur mee
    sf::Sprite sprite(m_texture);
    // Definieer welk deel van de textuur deze sprite moet tonen
    sprite.setTextureRect(rect);
    return sprite;
}