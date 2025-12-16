//
// Created by milo on 11/3/25.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H
#include <vector>

namespace logic {
namespace core {
enum class Event;
}
} // namespace logic

struct Coordinate {
    float getX() { return x; }
    float getY() { return y; }
    Coordinate(float x, float y) : x(x), y(y) {}
    Coordinate() = default;
    void set_coordinates(float x, float y) {
        this->x = x;
        this->y = y;
    }

private:
    float x = 0;
    float y = 0;
};

struct Rectangle {
    Rectangle() = default;
    Rectangle(Coordinate top_left, Coordinate bottom_right) : top_left(top_left), bottom_right(bottom_right) {}
    [[nodiscard]] Coordinate get_top_left() const { return top_left; }
    void set_top_left(const Coordinate& top_left) { this->top_left = top_left; }
    [[nodiscard]] Coordinate get_bottom_right() const { return bottom_right; }
    void set_bottom_right(const Coordinate& bottom_right) { this->bottom_right = bottom_right; }

private:
    Coordinate top_left;
    Coordinate bottom_right;
};

class utils {
public:
    /**
     * @brief checks if a Coordinate falls inside a rectangle
     * @param upper_left_corner upper left corner of the rectangle
     * @param lower_right_corner lower right corner of the rectangle
     * @param coordinate coordinate that is checked
     * @return bool if it falls in the rectangle or not
     */
    static bool contains(Coordinate& upper_left_corner, Coordinate& lower_right_corner, Coordinate& coordinate);

    /**
     * @brief checks if two rectangles are intersecting
     * @param rectangle1 first rectangle
     * @param rectangle2 second rectangle
     * @return true if the rectangles are intersecting
     */
    static bool intersecting(Rectangle& rectangle1, Rectangle& rectangle2);

    /**
     * @brief compute the manhatten distance between two coordinates
     * @param pos1 the first coordinate
     * @param pos2 the second coordinate
     * @return a float that represents the manhatten distance
     */
    static float compute_manhattan_distance(Coordinate& pos1, Coordinate& pos2);

    static bool has_event(std::vector<logic::core::Event> events, logic::core::Event event);
};

#endif // PACMAN_UTILS_H
