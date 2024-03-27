//
// Created by Maria Borca on 27.03.2024.
//

#include "Point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

int Point::getX() {
    return this->x;
}

int Point::getY() {
    return this->y;
}

void Point::setX(int new_x) {
    this->x = new_x;
}

void Point::setY(int new_y) {
    this->y = new_y;
}
