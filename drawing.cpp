//
// Created by Maria Borca on 03.04.2024.
//

#include "drawing.h"

void drawCircle(Image &img, Point center, int radius, unsigned char color) {
    for (int x = 0; x < img.GetWidth(); x++)
        for (int y = 0; y < img.GetHeight(); y++)
            if (sqrt((x - center.getX()) * (x - center.getX()) + (y - center.getY()) * (y - center.getY())) <= radius)
                img.at(x, y) = color;
}

void drawLine(Image &img, Point p1, Point p2, unsigned char color) {
    if (p1.getX() > p2.getX())
        std::swap(p1, p2);
    else if (p1.getX() == p2.getX() && p1.getY() > p2.getY())
        std::swap(p1, p2);
    for (unsigned int x = p1.getX(), y = p1.getY(); x <= p2.getX() && y <= p2.getY(); x++, y++)
        img.at(x, y) = color;
}

void drawRectangle(Image &img, Rectangle r, unsigned char color) {
    for (int x = r.GetXCoord(); x < r.GetXCoord() + r.GetWidth() - 1; x++)
        for (int y = r.GetYCoord(); y < r.GetYCoord() + r.GetHeight() - 1; y++)
            img.at(x, y) = color;
}

void drawRectangle(Image &img, Point tl, Point br, unsigned char color) {
    for (int x = tl.getX(); x <= br.getX(); x++)
        for (int y = tl.getY(); y <= br.getY(); y++)
            img.at(x, y) = color;
}