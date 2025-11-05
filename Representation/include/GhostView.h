//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>

namespace logic {
class GhostModel;
}

namespace representation {
class GhostView : public representation::EntityView, public logic::Observer{
public:
    explicit GhostView(std::shared_ptr<logic::GhostModel> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_GHOSTVIEW_H
