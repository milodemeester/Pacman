#ifndef PACMAN_SFMLFACTORY_H
#define PACMAN_SFMLFACTORY_H
#include "Camera.h"
#include "../../Logic/include/GameFactory.h"
#include <SFML/Graphics/RenderWindow.hpp>

class SfmlFactory : public GameFactory {
    Camera camera;
public:
    SfmlFactory(Camera& camera);
    ~SfmlFactory() override = default;

    std::shared_ptr<Pacman> createPacman() override;
    std::shared_ptr<Ghost> createGhost(std::string) override;
    std::shared_ptr<Coin> createCoin() override;
    std::shared_ptr<Fruit> createFruit() override;
    std::shared_ptr<Wall> createWall() override;
};

#endif // PACMAN_SFMLFACTORY_H
