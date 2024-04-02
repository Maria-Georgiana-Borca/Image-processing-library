//
// Created by Maria Borca on 02.04.2024.
//

#ifndef IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H
#define IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H

#include "Image.h"


class ImageProcessing {
public:
    void process(const Image& src, Image& dest);
};

class BrightnessContrast : public ImageProcessing{

};


#endif //IMAGE_PROCESSING_LIBRARY_IMAGEPROCESSING_H
