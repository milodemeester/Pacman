//
// Created by milo on 11/3/25.
//

#include "utils.h"

bool utils::contains(Coordinate upper_left_corner, Coordinate lower_right_corner, Coordinate click) {
    if (click.getX() > lower_right_corner.getX()) {
        return false;
    }
    if (click.getX() < upper_left_corner.getX()) {
        return false;
    }
    if (click.getY() > upper_left_corner.getY()) {
        return false;
    }
    if (click.getY() < lower_right_corner.getY()) {
        return false;
    }
    return true;
}