//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_ENTITYVIEW_H
#define PACMAN_ENTITYVIEW_H
#include "../../Logic/include/Observer.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace representation {
class EntityView {
public:
    virtual ~EntityView() = default;

    virtual void update(float dT) = 0;

    virtual void draw(sf::RenderWindow& window) = 0;
};
} // namespace representation

#endif // PACMAN_ENTITYVIEW_H
