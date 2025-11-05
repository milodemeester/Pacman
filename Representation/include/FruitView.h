//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_FRUITVIEW_H
#define PACMAN_FRUITVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>

namespace logic {
class FruitModel;
}
namespace representation {
class FruitView : public representation::EntityView, public logic::Observer {
public:
    explicit FruitView(std::shared_ptr<logic::FruitModel>& model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_FRUITVIEW_H
