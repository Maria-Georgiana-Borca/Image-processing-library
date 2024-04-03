//
// Created by Maria Borca on 02.04.2024.
//

#include "ImageProcessing.h"

BrightnessContrast::BrightnessContrast() {
    this->alpha = 1;
    this->beta = 0;
}

BrightnessContrast::BrightnessContrast(int alpha, int beta) {
    this->alpha = alpha;
    this->beta = beta;
}

void BrightnessContrast::process(const Image &src, Image &dest) {
    dest.SetWidth(src.GetWidth());
    dest.SetHeight(src.GetHeight());
    for (int i = 0; i < src.GetHeight(); i++) {
        unsigned char *rowDest = dest.row(i);
        for (int j = 0; j < src.GetWidth(); j++)
            rowDest[j] = (alpha * src.at(i, j) + beta > 0) ? (alpha * src.at(i, j) + beta) % 255 : 0;
    }
}

GamaCorrector::GamaCorrector() {
    this->gama = 1;
}

GamaCorrector::GamaCorrector(double gama) {
    this->gama = gama;
}

void GamaCorrector::process(const Image &src, Image &dest) {
    for (int i = 0; i < src.GetHeight(); i++) {
        unsigned char *rowDest = dest.row(i);
        for (int j = 0; j < src.GetWidth(); j++) {
            rowDest[j] = pow(int(src.at(i, j)), this->gama);
            rowDest[j] %= 255;
        }
    }
}

Convolution::Convolution() {
    this->kernel = Image();
    this->scaleFunction = [](int x) -> int {return x;};
}

Convolution::Convolution(Image kernel, int (*scaleFunction)(int)) {
    this->kernel = kernel;
    this->scaleFunction = scaleFunction;
}

void Convolution::process(const Image &src, Image &dest) {
    Image copySrc(src);
    //dest = Image::zeros(src.GetWidth() - kernel.GetWidth() + 1, src.GetHeight() - kernel.GetHeight() + 1);
    dest.SetWidth(src.GetWidth() - kernel.GetWidth() + 1);
    dest.SetHeight(src.GetHeight() - kernel.GetHeight() + 1);
    for (unsigned int x = 0; x < src.GetHeight() - this->kernel.GetHeight(); x++){
        //unsigned char *rowDest = dest.row(x);
        for (int y = 0; y < src.GetWidth() - this->kernel.GetWidth(); y++){
            Image aux(this->kernel.GetWidth(), this->kernel.GetHeight());
            copySrc.getROI(aux, x, y, this->kernel.GetWidth(), this->kernel.GetHeight());
            if (x == 0 && y == 6)
                std::cout << aux << '\n';
            int filteredValue = 0;
            for (int u = 0; u < this->kernel.GetHeight(); u++)
                for (int v = 0; v < this->kernel.GetWidth(); v ++)
                    filteredValue += aux.at(u, v) * this->kernel.at(u, v);
            //std::cout << this->scaleFunction(filteredValue) << '\n';
            dest.at(x, y) = this->scaleFunction(filteredValue);
        }
    }

//    Image second_src(src);
//    dest = Image::zeros(src.GetWidth() - kernel.GetWidth() + 1, src.GetHeight() - kernel.GetHeight() + 1);
//    for (unsigned int i = 0; i < src.GetHeight() - kernel.GetHeight() + 1; i ++)
//        for (unsigned int j = 0; j < src.GetWidth() - kernel.GetWidth() + 1; j ++) {
//            Image aux;
//            second_src.getROI(aux, i, j, kernel.GetWidth(), kernel.GetHeight());
//            int ans = 0;
//            for (int u = 0; u < kernel.GetWidth(); u++)
//                for (int v = 0; v < kernel.GetHeight(); v ++)
//                    ans += kernel.at(u, v) * aux.at(u, v);
//            dest.at(j, i) = this->scaleFunction(ans);
//        }
}
