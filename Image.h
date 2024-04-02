//
// Created by Maria Borca on 02.04.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_IMAGE_H
#define IMAGE_PROCESSING_LIBRARY_IMAGE_H

#include <iostream>
#include <fstream>
#include "Rectangle.h"
#include <cstring>


class Image {
private:
    unsigned char **m_data;
    unsigned int m_width;
    unsigned int m_height;

public:
    Image();

    Image(unsigned int w, unsigned int h);

    Image(const Image &other);

    Image &operator=(const Image &other);

    ~Image();

    unsigned int GetWidth() const;

    unsigned int GetHeight() const;

    void SetWidth(unsigned int newWidth);

    void SetHeight(unsigned int newHeight);

    bool load(std::string imagePath);

    bool save(std::string imagePath) const;

    Image operator+(const Image &i);

    Image operator-(const Image &i);

    Image operator*(double s);

    bool getROI(Image &roiImg, Rectangle roiRect);

    bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int
    width, unsigned int height);

    bool isEmpty() const;

    Size size() const;

    unsigned char &at(unsigned int x, unsigned int y) const;

    unsigned char &at(Point pt);

    unsigned char *row(int y);

    void release();

    friend std::ostream &operator<<(std::ostream &os, const Image &dt);

    friend std::istream &operator>>(std::istream &is, Image &dt);

    static Image zeros(unsigned int width, unsigned int height);

    static Image ones(unsigned int width, unsigned int height);
};


#endif //IMAGE_PROCESSING_LIBRARY_IMAGE_H
