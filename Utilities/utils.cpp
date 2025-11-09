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

    if (click.getX() < left)
        return false;
    if (click.getX() > right)
        return false;
    if (click.getY() < top)
        return false;
    if (click.getY() > bottom)
        return false;
    return true;
}


bool utils::intersecting(Rectangle rectangle1, Rectangle rectangle2) {
    // Condition for no horizontal overlap:
    // If r1 is entirely to the left of r2, or r2 is entirely to the left of r1.
    if (rectangle1.get_bottom_right().getX() < rectangle2.get_top_left().getX() ||
        rectangle2.get_bottom_right().getX() < rectangle1.get_top_left().getX()) {
        return false;
        }

    // Condition for no vertical overlap:
    // If r1 is entirely above r2, or r2 is entirely above r1.
    if (rectangle1.get_bottom_right().getY() < rectangle2.get_top_left().getY() ||
        rectangle2.get_bottom_right().getY() < rectangle1.get_top_left().getY()) {
        return false;
        }

    // If there is overlap on both axes, the rectangles are intersecting.
    return true;
}