//
// Created by Maria Borca on 27.03.2024.
//

#include "Point.h"
#include "Size.h"
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

int main() {
    testPoint();
    testSize();
    return 0;
}
