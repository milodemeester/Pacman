//
// Created by milo on 11/3/25.
//

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

struct Coordinate {
    double getX() {return x;}
    double getY() {return y;}
    Coordinate(double x, double y) : x(x), y(y) {}
    void set_coordinates(double x, double y) {this->x = x; this->y = y;}
private:
    double x = 0;
    double y = 0;
};

class utils {
public:
    /*
     * checks if a mouseclick is inside a box
     */
    static bool contains(Coordinate upper_left_corner, Coordinate lower_right_corner, Coordinate click);
};

#endif // PACMAN_UTILS_H
