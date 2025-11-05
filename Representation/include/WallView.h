//
// Created by milo on 11/5/25.
//

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H
#include "EntityView.h"
#include "../../Logic/include/Observer.h"
#include <memory>

namespace logic {
class WallModel;
}
namespace representation {
class WallView : public representation::EntityView, public logic::Observer {
public:
    explicit WallView(std::shared_ptr<logic::WallModel> model);

    void onNotify(const logic::Subject& entity, logic::Event& e) override;

    void update(float dT) override;

    void draw(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_WALLVIEW_H
