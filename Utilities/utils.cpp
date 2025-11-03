//
// Created by milo on 11/3/25.
//

#include "utils.h"

bool utils::contains(Coordinate upper_left_corner, Coordinate lower_right_corner, Coordinate click) {
    // Verwachte conventie: upper_left = (left, top), lower_right = (right, bottom)
    double left = upper_left_corner.getX();
    double top = upper_left_corner.getY();
    double right = lower_right_corner.getX();
    double bottom = lower_right_corner.getY();

    if (click.getX() < left)  return false;
    if (click.getX() > right) return false;
    if (click.getY() < top)   return false;
    if (click.getY() > bottom) return false;
    return true;
}