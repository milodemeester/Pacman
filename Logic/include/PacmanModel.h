//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "../../Utilities/utils.h"
#include "Subject.h"
#include "World.h"

namespace logic {
class PacmanModel : public MoveableSubject {
protected:
    int lives; // the amount of lives that pacman has left

    // getters
    float get_speed() override;
public:
    /**
     * @brief constructor
     * @param pos the initial position of the model
     * @param dir the initial direction of the model
     * @param world_width the width of the world the model is in
     * @param world_height the height of the world the model is in
     */
    PacmanModel(Coordinate pos, Direction dir, int world_width, int world_height);

    /**
     * @brief updates the position and direction of pacman based on the amount of time passed between update-calls
     * @param dt the time passed since the last upate
     * @param world the world that pacman lives in
     */
    void update(float dt, World& world) override;

    // getters
    int get_lives();
    [[nodiscard]] EntityType get_type() const override {return EntityType::Pacman;};

    // setters
    void set_lives(int lives);
};
} // namespace logic

#endif // PACMAN_PACMAN_H
