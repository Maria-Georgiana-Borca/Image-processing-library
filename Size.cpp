//
// Created by Maria Borca on 27.03.2024.
//

#include "Size.h"

Size::Size(){}

Size::Size(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

unsigned int Size::getWidth() {
    return this->width;
}

unsigned int Size::getHeight() {
    return this->height;
}

void Size::setWidth(unsigned int width) {
    this->width = width;
}

void Size::setHeight(unsigned int height) {
    this->height = height;
}

unsigned int Size::getArea() const {
    return this->width * this->height;
}

bool Size::operator==(const Size& other) const {
    return getArea() == other.getArea();
}

bool Size::operator<=(const Size& other) const {
    return getArea() <= other.getArea();
}

bool Size::operator<(const Size& other) const {
    return getArea() < other.getArea();
}

bool Size::operator>=(const Size& other) const {
    return getArea() >= other.getArea();
}

bool Size::operator>(const Size& other) const {
    return getArea() > other.getArea();
}

bool Size::operator!=(const Size& other) const {
    return getArea() != other.getArea();
}
