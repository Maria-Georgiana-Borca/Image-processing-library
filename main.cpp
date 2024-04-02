//
// Created by Maria Borca on 02.04.2024.
//

#include "Image.h"

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

int main(){
    Image image1;
    std::cin>>image1;
    Image roi;
    Rectangle roiR(1, 1, 2, 2);
    if (image1.getROI(roi, roiR))
        std::cout << roi;
    return 0;
}

