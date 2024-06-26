//
// Created by Maria Borca on 27.03.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_SIZE_H
#define IMAGE_PROCESSING_LIBRARY_SIZE_H


class Size {
private:
    unsigned int width;
    unsigned int height;

    unsigned int getArea() const;

public:
    Size();

    Size(unsigned int width, unsigned int height);

    Size(const Size &other);

    ~Size();

    Size& operator=(const Size &other);

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    void setWidth(unsigned int width);

    void setHeight(unsigned int height);

    bool operator==(const Size &other) const;

    bool operator<=(const Size &other) const;

    bool operator<(const Size &other) const;

    bool operator>(const Size &other) const;

    bool operator>=(const Size &other) const;

    bool operator!=(const Size &other) const;
};


#endif //IMAGE_PROCESSING_LIBRARY_SIZE_H
