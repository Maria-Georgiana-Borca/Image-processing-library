//
// Created by Maria Borca on 02.04.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H
#define IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H

#include "Image.h"


class ImageProcessing {
public:
    virtual void process(const Image& src, Image& dest) = 0;
};

class BrightnessContrast : public ImageProcessing{
private:
    int alpha, beta;

public:
    BrightnessContrast();
    BrightnessContrast(int alpha, int beta);
    void process(const Image& src, Image& dest) override;
};

class GamaCorrector : public ImageProcessing{
private:
    double gama;

public:
    GamaCorrector();
    GamaCorrector(double gama);
    void process(const Image& src, Image& dest) override;
};

class Convolution : public ImageProcessing {
private:
    Image kernel;
    int (*scaleFunction)(int);

public:
    Convolution();
    Convolution(Image kernel, int (*scaleFunction)(int));
    void process(const Image& src, Image& dest) override;
};


#endif //IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H
