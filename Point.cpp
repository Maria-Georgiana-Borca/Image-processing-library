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

Point::Point(const Point &other) {
    this->x = other.x;
    this->y = other.y;
}

Point::~Point() {}

Point& Point::operator=(const Point &other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

int Point::getX() const {
    return this->x;
}

int Point::getY() const {
    return this->y;
}

void Point::setX(int new_x) {
    this->x = new_x;
}

void Point::setY(int new_y) {
    this->y = new_y;
}
