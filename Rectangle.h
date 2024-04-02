//
// Created by Maria Borca on 27.03.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_RECTANGLE_H
#define IMAGE_PROCESSING_LIBRARY_RECTANGLE_H

#include "Point.h"
#include "Size.h"

#include <iostream>


class Rectangle {
private:
    Point topLeftCorner;
    Size size;

public:
    Rectangle();

    Rectangle(int x, int y, unsigned int width, unsigned int height);

    Rectangle(const Rectangle &other);

    ~Rectangle();

    Rectangle &operator=(const Rectangle &other);

    int GetXCoord() const;

    int GetYCoord() const;

    int GetWidth() const;

    int GetHeight() const;

    void SetXCoord(int newX);

    void SetYCoord(int newY);

    void SetWidth(unsigned int newWidth);

    void SetHeight(unsigned int newHeight);

    Rectangle operator+(const Point &point) const;

    Rectangle operator-(const Point &point) const;

    Rectangle operator&(const Rectangle &other) const;

    Rectangle operator|(const Rectangle &other) const;
};


#endif //IMAGE_PROCESSING_LIBRARY_RECTANGLE_H
