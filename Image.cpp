//
// Created by Maria Borca on 02.04.2024.
//

#include "Image.h"

Image::Image() {
    this->m_data = nullptr;
    this->m_width = 0;
    this->m_height = 0;
}

Image::Image(unsigned int w, unsigned int h) {
    this->m_width = w;
    this->m_height = h;
    this->m_data = new unsigned char *[h];
    for (int i = 0; i < h; i++) {
        this->m_data[i] = new unsigned char[w];
        std::memset(m_data[i], 0, w * sizeof(unsigned char));
    }
}

Image::Image(const Image &other) {
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    this->m_data = new unsigned char *[this->m_height];
    for (int i = 0; i < this->m_height; i++) {
        this->m_data[i] = new unsigned char[this->m_width];
        for (int j = 0; j < this->m_width; j++)
            this->m_data[i][j] = other.m_data[i][j];
    }
}

void Image::release() {
    for (int i = 0; i < this->m_height; i++)
        delete[] this->m_data[i];
    delete[] this->m_data;
}

Image::~Image() {
    this->release();
}

Image &Image::operator=(const Image &other) {
    if (this != &other) {
        if (this->m_data) {
            for (int i = 0; i < this->m_height; i++)
                delete[] this->m_data[i];
            delete[] this->m_data;
        }
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        this->m_data = new unsigned char *[this->m_height];
        for (int i = 0; i < this->m_height; i++) {
            this->m_data[i] = new unsigned char[this->m_width];
            for (int j = 0; j < this->m_width; j++)
                this->m_data[i][j] = other.m_data[i][j];
        }
    }
    return *this;
}

unsigned int Image::GetWidth() const {
    return this->m_width;
}

unsigned int Image::GetHeight() const {
    return this->m_height;
}

void Image::SetWidth(unsigned int newWidth) {
    this->m_width = newWidth;
}

void Image::SetHeight(unsigned int newHeight) {
    this->m_height = newHeight;
}

Size Image::size() const {
    return Size(this->m_width, this->m_height);
}

bool Image::isEmpty() const {
    return (this->m_data == nullptr && this->m_width == 0 && this->m_height == 0);
}

unsigned char &Image::at(unsigned int x, unsigned int y) const {
    return this->m_data[x][y];
}

unsigned char &Image::at(Point pt) {
    return this->m_data[pt.getX()][pt.getY()];
}

unsigned char *Image::row(int y) {
    return this->m_data[y];
}

bool Image::load(std::string imagePath) {
    std::ifstream fin(imagePath);
    if (!fin.is_open())
        return false;

    std::string magicNumber;
    unsigned int width, height, maxPixelValue;
    fin >> magicNumber >> width >> height >> maxPixelValue;
    if (magicNumber != "P2" || maxPixelValue > 255)
        return false;
    this->m_width = width;
    this->m_height = height;
    release();
    this->m_data = new unsigned char *[m_height];
    for (int i = 0; i < this->m_height; i++) {
        this->m_data[i] = new unsigned char[m_width];
        for (int j = 0; j < this->m_width; j++) {
            int val;
            fin >> val;
            if (val < 0 || val > maxPixelValue)
                return false;
            m_data[i][j] = val;
        }
    }
    fin.close();
    return true;
}

bool Image::save(std::string imagePath) const {
    std::ofstream fout(imagePath);
    if (!fout.is_open())
        return false;
    fout << "P2\n" << this->m_width << ' ' << this->m_height << '\n' << "255\n";
    for (int i = 0; i < this->m_height; i++) {
        for (int j = 0; j < this->m_width; j++)
            fout << static_cast<int>(this->m_data[i][j]) << ' ';
        fout << '\n';
    }
    fout.close();
    return true;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_data = new unsigned char *[height];
    for (int i = 0; i < height; i++) {
        img.m_data[i] = new unsigned char[width];
        for (int j = 0; j < width; j++)
            img.m_data[i][j] = 0;
    }
    return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_data = new unsigned char *[height];
    for (int i = 0; i < height; i++) {
        img.m_data[i] = new unsigned char[width];
        for (int j = 0; j < width; j++)
            img.m_data[i][j] = 1;
    }
    return img;
}


Image Image::operator+(const Image &i) {
    if (this->m_width != i.GetWidth() || this->m_height != i.GetHeight())
        throw std::invalid_argument("The widths and heights must be equal!");
    Image img(this->m_width, this->m_height);
    for (int j = 0; j < this->m_height; j++)
        for (int k = 0; k < this->m_width; k++)
            img.m_data[j][k] = this->m_data[j][k] + i.m_data[j][k];
    return img;
}

Image Image::operator-(const Image &i) {
    if (this->m_width != i.GetWidth() || this->m_height != i.GetHeight())
        throw std::invalid_argument("The widths and heights must be equal!");
    Image img(this->m_width, this->m_height);
    for (int j = 0; j < this->m_height; j++)
        for (int k = 0; k < this->m_width; k++)
            img.m_data[j][k] = abs(this->m_data[j][k] - i.m_data[j][k]);
    return img;
}

Image Image::operator*(double s) {
    Image img(this->m_width, this->m_height);
    for (int j = 0; j < this->m_height; j++)
        for (int k = 0; k < this->m_width; k++)
            img.m_data[j][k] = this->m_data[j][k] * s;
    return img;
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    if (roiRect.GetXCoord() + roiRect.GetWidth() > this->m_width ||
        roiRect.GetYCoord() + roiRect.GetHeight() > this->m_height)
        return false;
    roiImg.m_width = roiRect.GetWidth();
    roiImg.m_height = roiRect.GetHeight();
    if (roiImg.m_data)
        delete[] roiImg.m_data;
    roiImg.m_data = new unsigned char *[roiImg.m_height];
    for (int i = 0; i < roiImg.m_height; i++) {
        roiImg.m_data[i] = new unsigned char[roiImg.m_width];
        for (int j = 0; j < roiImg.m_width; j++)
            roiImg.m_data[i][j] = int(this->m_data[i + roiRect.GetXCoord()][j + roiRect.GetYCoord()]);
    }
    return true;
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width - 1 > this->m_width || y + height - 1 > this->m_height)
        return false;
    roiImg.m_width = width;
    roiImg.m_height = height;
    if (roiImg.m_data)
        delete[] roiImg.m_data;
    roiImg.m_data = new unsigned char *[roiImg.m_height];
    for (int i = 0; i < roiImg.m_height; i++) {
        roiImg.m_data[i] = new unsigned char[roiImg.m_width];
        for (int j = 0; j < roiImg.m_width; j++) {
            roiImg.m_data[i][j] = int(this->m_data[i + x][j + y]);
        }
    }
    return true;
}
