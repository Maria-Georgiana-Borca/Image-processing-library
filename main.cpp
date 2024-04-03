//
// Created by Maria Borca on 02.04.2024.
//

#include "ImageProcessing.h"
#include "drawing.h"

std::ostream &operator<<(std::ostream &os, const Image &dt){
    os << "P2\n";
    os << dt.GetWidth() << ' ' << dt.GetHeight() << '\n';
    os << "255\n";
    for (int i = 0 ; i < dt.GetHeight(); i++) {
        for(int j = 0; j < dt.GetWidth(); j++)
            os << int(dt.m_data[i][j]) << ' ';
        os << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, Image &dt){
    is >> dt.m_width >> dt.m_height;
    dt.m_data = new unsigned char*[dt.m_height];
    for (int i = 0; i < dt.m_height; i++){
        dt.m_data[i] = new unsigned char[dt.m_width];
        for (int j = 0; j < dt.m_width; j++) {
            int pixelValue;
            is >> pixelValue;
            dt.m_data[i][j] = pixelValue;
        }
    }
    return is;
}

int meanBlur(int x){
    return x * 1/9;
}

int nothing(int x){
    return x;
}

int main(){
    Image image1(5, 5);
    Point p1(0, 1);
    Point p2(3, 4);
    drawRectangle(image1, p1, p2, 2);
    std::cout << image1;
    return 0;
}

