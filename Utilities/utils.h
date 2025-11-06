//
// Created by milo on 11/3/25.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

struct Coordinate {
    double getX() { return x; }
    double getY() { return y; }
    Coordinate(double x, double y) : x(x), y(y) {}
    Coordinate() = default;
    void set_coordinates(double x, double y) {
        this->x = x;
        this->y = y;
    }

private:
    double x = 0;
    double y = 0;
};

struct Rectangle {
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
    /*
     * checks if a mouseclick is inside a box
     */
    static bool contains(Coordinate upper_left_corner, Coordinate lower_right_corner, Coordinate click);

    static bool intersecting(Rectangle rectangle1, Rectangle rectangle2);
};

#endif // PACMAN_UTILS_H
