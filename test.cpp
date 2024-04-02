//
// Created by Maria Borca on 27.03.2024.
//

#include "Point.h"
#include "Size.h"
#include "Rectangle.h"
#include <iostream>
#include <cassert>

void testPoint(){
    Point point1;
    point1.setX(1);
    assert(point1.getX() == 1);
    point1.setY(12);
    assert(point1.getY() == 12);
}

void testSize(){
    Size size1(1, 2);
    Size size2;
    size2.setWidth(2);
    assert(size2.getWidth() == 2);
    size2.setHeight(4);
    assert(size2.getHeight() == 4);
    assert(size1 != size2);
    assert(size1 < size2);
}

void testRectangle(){
    Rectangle rectangle1(1, 3, 3, 2);
    Rectangle rectangle2(2, 4, 4, 2);
    Rectangle rectangle3(0, 2, 1, 1);
    Point p1(2, 4);
    Rectangle r = rectangle1 + p1;
    assert(r.GetXCoord() == 3);
    assert(r.GetYCoord() == 7);
    r = rectangle1 - p1;
    assert(r.GetXCoord() == -1);
    assert(r.GetYCoord() == -1);
    Rectangle intersection = rectangle1 & rectangle2;
    assert(intersection.GetXCoord() == 2);
    assert(intersection.GetYCoord() == 3);
    assert(intersection.GetWidth() == 2);
    assert(intersection.GetHeight() == 1);

    Rectangle Union = rectangle1 | rectangle3;
    assert(Union.GetXCoord() == 0);
    assert(Union.GetYCoord() == 3);
    assert(Union.GetWidth() == 4);
    assert(Union.GetHeight() == 2);

    Union = rectangle2 | rectangle3;
    assert(Union.GetXCoord() == 0);
    assert(Union.GetYCoord() == 4);
    assert(Union.GetWidth() == 6);
    assert(Union.GetHeight() == 3);
}

int main() {
    testPoint();
    testSize();
    testRectangle();
    return 0;
}
