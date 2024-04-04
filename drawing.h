#ifndef IMAGE_PROCESSING_LIBRARY_DRAWING_H
#define IMAGE_PROCESSING_LIBRARY_DRAWING_H

#include "Image.h"

void drawCircle(Image& img, Point center, int radius, unsigned char color);
void drawLine(Image &img, Point p1, Point p2, unsigned char color);
void drawRectangle(Image &img, Rectangle r, unsigned char color);
void drawRectangle(Image &img, Point tl, Point br, unsigned char color);

#endif //IMAGE_PROCESSING_LIBRARY_DRAWING_H
