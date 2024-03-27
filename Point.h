//
// Created by Maria Borca on 27.03.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_POINT_H
#define IMAGE_PROCESSING_LIBRARY_POINT_H


class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);

    int getX();
    int getY();
    void setX(int new_x);
    void setY(int new_y);
};


#endif //IMAGE_PROCESSING_LIBRARY_POINT_H
