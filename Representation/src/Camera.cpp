//
// Created by milod on 31/10/2025.
//

#include "../include/Camera.h"

std::pair<sf::Vector2f, sf::Vector2f> representation::Camera::worldToScreen(Coordinate worldPos, sf::Vector2u windowSize, sf::Vector2f worldSize) const {
    std::pair<sf::Vector2f, sf::Vector2f> output;
    sf::Vector2f scale;
    double x = worldPos.getX();
    double y = worldPos.getY();
    // Van [-1,1] -> [0,1]
    x = (x+1)/2;
    y = (y+1)/2;
    if (float(windowSize.x)/windowSize.y > worldSize.x/worldSize.y) {
        // y is de hoofdas, dus we doen y*hoogte van de window
        y = y * windowSize.y;
        /*
         * de breedte nodig in verhouding met de hoogte (worldx/worldy = windowx/window y)
         * => windowx = (worldx*windowy)/worldy
         */
        float x_necassery = (worldSize.x*windowSize.y)/worldSize.y;
        // de zwarte balk die nog overblijft nadat de verhouding is gecorrigeerd
        float x_balk = windowSize.x - x_necassery;
        x = x*x_necassery;
        x = x+(x_balk/2);
        scale.y = worldSize.y/windowSize.y;
        scale.x = worldSize.x/x_necassery;
    }
    else {
        // x is de hoofdas, dus we doen x*breedte van de window
        x = x * windowSize.x;
        /*
         * de hoogte nodig in verhouding met de breedte (worldx/worldy = windowx/window y)
         * => windowy = (windowx*worldy)/worldx
         */
        float y_necassery = (float(windowSize.x) * worldSize.y)/ worldSize.x;
        // de zwarte balk die nog overblijft nadat de verhouding is gecorrigeerd
        float y_balk = float(windowSize.y) - y_necassery;
        y = x*y_necassery;
        y = y+(y_balk/2);
        scale.x = worldSize.x/windowSize.x;
        scale.y = worldSize.y/y_necassery;
    }
    output.first = sf::Vector2f(x,y);
    output.second = scale;
    return output;
}