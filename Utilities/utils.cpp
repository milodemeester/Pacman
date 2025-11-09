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
    // Check for no overlap. If any of these conditions are true, they do not overlap.

    // r1 is to the right of r2 OR r2 is to the right of r1
    if (rectangle1.get_top_left().getX() > rectangle2.get_bottom_right().getX() ||
        rectangle2.get_top_left().getX() > rectangle1.get_bottom_right().getX()) {
        return false;
        }

    // r1 is below r2 OR r2 is below r1
    // Note: In your coordinate system, a larger Y value means "lower" on the screen.
    if (rectangle1.get_top_left().getY() > rectangle2.get_bottom_right().getY() ||
        rectangle2.get_top_left().getY() > rectangle1.get_bottom_right().getY()) {
        return false;
        }

    // If none of the above are true, they must be intersecting.
    return true;
}