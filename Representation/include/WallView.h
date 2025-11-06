//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>
#include "../../Logic/include/WallModel.h"

namespace representation {
class WallView : public representation::EntityView, public logic::Observer {
public:
    explicit WallView(const std::shared_ptr<logic::WallModel>& model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void draw(sf::RenderWindow& window, Camera& cam) override;

    void update(double dt) override {}
};
} // namespace representation

#endif // PACMAN_WALLVIEW_H
