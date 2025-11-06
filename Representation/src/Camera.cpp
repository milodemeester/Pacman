//
// Created by milod on 31/10/2025.
//

#include "../include/Camera.h"

sf::Vector2f representation::Camera::worldToScreen(Coordinate worldPos, sf::Vector2u windowSize, sf::Vector2f worldSize) const {
    float x = worldPos.getX();
    float y = worldPos.getY();
    // Van [-1,1] -> [0,1]
    x = (x+1)/2;
    y = (y+1)/2;
    if (windowSize.x/windowSize.y < worldSize.x/worldSize.y) {
        // y is de hoofdas, dus we doen y*hoogte van de window
        y = y * windowSize.y;
        /*
         * de hoogte nodig in verhouding met de breedte (worldx/worldy = windowx/window y)
         * => windowy = (windowx*worldy)/worldx
         */
        float y_necassery = (windowSize.x * worldSize.y)/ worldSize.x;
        // de zwarte balk die nog overblijft nadat de verhouding is gecorrigeerd
        float y_balk = windowSize.y - y_necassery;
        y = x*y_necassery;
        y = y+(y_balk/2);
    }
    else {
        // x is de hoofdas, dus we doen x*breedte van de window
        x = x * windowSize.x;
        /*
         * de breedte nodig in verhouding met de hoogte (worldx/worldy = windowx/window y)
         * => windowx = (worldx*windowy)/worldy
         */
        float x_necassery = (worldSize.x*windowSize.y)/worldSize.y;
        // de zwarte balk die nog overblijft nadat de verhouding is gecorrigeerd
        float x_balk = windowSize.x - x_necassery;
        x = x*x_necassery;
        x = x+(x_balk/2);
    }
    return sf::Vector2f(x, y);
}