//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

struct Coordinate {
    double getX() {return x;}
    double getY() {return y;}
    Coordinate(double x, double y) : x(x), y(y) {}
    void set_coordinates(double x, double y) {this->x = x; this->y = y;}
private:
    double x = 0;
    double y = 0;
};

class Entity {
    Coordinate position;
    enum Direction { N = 'N', E = 'E', S = 'S', W = 'W' };
    Direction dir = N;
    double speed; // measured in pixels/second

public:
    Entity(Coordinate coordinate, double s) : position(coordinate), speed(s) {}
    [[nodiscard]] Coordinate get_position() const { return position; }
    void set_position(const Coordinate& position) { this->position = position; }
};

#endif //PACMAN_ENTITY_H
