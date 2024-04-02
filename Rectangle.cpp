//
// Created by Maria Borca on 27.03.2024.
//

#include "Rectangle.h"

Rectangle::Rectangle() {}

Rectangle::Rectangle(int x, int y, unsigned int width, unsigned int height) {
    this->topLeftCorner.setX(x);
    this->topLeftCorner.setY(y);
    this->size.setWidth(width);
    this->size.setHeight(height);
}

Rectangle::Rectangle(const Rectangle &other) {
    this->topLeftCorner = other.topLeftCorner;
    this->size = other.size;
}

Rectangle::~Rectangle() {}

Rectangle &Rectangle::operator=(const Rectangle &other) {
    this->topLeftCorner = other.topLeftCorner;
    this->size = other.size;
    return *this;
}

int Rectangle::GetXCoord() const {
    return this->topLeftCorner.getX();
}

int Rectangle::GetYCoord() const {
    return this->topLeftCorner.getY();
}

int Rectangle::GetWidth() const {
    return this->size.getWidth();
}

int Rectangle::GetHeight() const {
    return this->size.getHeight();
}

void Rectangle::SetXCoord(int newX) {
    this->topLeftCorner.setX(newX);
}

void Rectangle::SetYCoord(int newY) {
    this->topLeftCorner.setY(newY);
}

void Rectangle::SetWidth(unsigned int newWidth) {
    this->size.setWidth(newWidth);
}

void Rectangle::SetHeight(unsigned int newHeight) {
    this->size.setHeight(newHeight);
}

Rectangle Rectangle::operator+(const Point &point) const {
    int newX = this->topLeftCorner.getX() + point.getX();
    int newY = this->topLeftCorner.getY() + point.getY();
    return Rectangle(newX, newY, this->size.getWidth(), this->size.getHeight());
}

Rectangle Rectangle::operator-(const Point &point) const {
    int newX = this->topLeftCorner.getX() - point.getX();
    int newY = this->topLeftCorner.getY() - point.getY();
    return Rectangle(newX, newY, this->size.getWidth(), this->size.getHeight());
}

Rectangle Rectangle::operator&(const Rectangle &other) const {
    int xCoordIntersection = std::max(this->topLeftCorner.getX(), other.GetXCoord());
    int yCoordIntersection = std::min(this->topLeftCorner.getY(), other.GetYCoord());

    unsigned int widthIntersection = std::max(0, std::min(this->topLeftCorner.getX() + int(this->size.getWidth()),
                                                          other.GetXCoord() + other.GetWidth()) - xCoordIntersection);
    unsigned int heightIntersection = std::max(0, std::min(this->topLeftCorner.getY() + int(this->size.getHeight()),
                                                           other.GetYCoord() + other.GetHeight()) -
                                                  std::max(this->topLeftCorner.getY(), other.GetYCoord()));

    if (widthIntersection == 0 || heightIntersection == 0)
        return Rectangle(0, 0, 0, 0);
    return Rectangle(xCoordIntersection, yCoordIntersection, widthIntersection, heightIntersection);
}

Rectangle Rectangle::operator|(const Rectangle &other) const {
    int xCoordUnion = std::min(this->topLeftCorner.getX(), other.GetXCoord());
    int yCoordUnion = std::max(this->topLeftCorner.getY(), other.GetYCoord());
    int widthUnion = std::max(this->topLeftCorner.getX() + int(this->size.getWidth()),
                              other.GetXCoord() + other.GetWidth()) - xCoordUnion;
    int heightUnion = yCoordUnion - (std::min(this->topLeftCorner.getY() - int(this->size.getHeight()),
                                              other.GetYCoord() - other.GetHeight()));
    return Rectangle(xCoordUnion, yCoordUnion, widthUnion, heightUnion);
}
