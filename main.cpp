#include "ImageProcessing.h"
#include "drawing.h"

std::ostream &operator<<(std::ostream &os, const Image &dt) {
    os << "P2\n";
    os << dt.GetWidth() << ' ' << dt.GetHeight() << '\n';
    os << "255\n";
    for (int i = 0; i < dt.GetHeight(); i++) {
        for (int j = 0; j < dt.GetWidth(); j++)
            os << int(dt.m_data[i][j]) << ' ';
        os << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, Image &dt) {
    is >> dt.m_width >> dt.m_height;
    dt.m_data = new unsigned char *[dt.m_height];
    for (int i = 0; i < dt.m_height; i++) {
        dt.m_data[i] = new unsigned char[dt.m_width];
        for (int j = 0; j < dt.m_width; j++) {
            int pixelValue;
            is >> pixelValue;
            dt.m_data[i][j] = pixelValue;
        }
    }
    return is;
}

int normalScaleFunction(int x) {
    return x;
}

int meanBlurScaleFunction(int x) {
    return 1 / 9 * x;
}

int gaussianScaleFunction(int x) {
    return 1 / 16 * x;
}

int ScaleFunction(int x) {
    return (x + 4 * 255) % 255;
}

void printMenu() {
    std::cout << "0. Exit\n";
    std::cout << "1. Adjust brightness and contrast\n";
    std::cout << "2. Correct the overall brightness\n";
    std::cout << "3. Convolutions\n";
    std::cout << "4. Draw a circle\n";
    std::cout << "5. Draw a line\n";
    std::cout << "6. Draw a rectangle\n\n";
    std::cout << "Please choose an option: ";
}

int correctOption() {
    int option;
    while (true) {
        std::cin >> option;
        if (option < 0 || option > 6) {
            std::cout << "The option must be an integer between 0 and 6!\n\n";
            std::cout << "Please choose an option: ";
        } else
            return option;
    }
}

int correctGain() {
    while (true) {
        std::cout << "Please introduce a value greater than 0 for the gain: ";
        int alpha;
        std::cin >> alpha;
        if (alpha <= 0)
            std::cout << "The gain must be greater than 0!\n\n";
        else
            return alpha;
    }
}

int chooseKernel() {
    std::cout << "1. Identity kernel\n";
    std::cout << "2. Mean blur kernel\n";
    std::cout << "3. 3x3 Gaussian blur kernel\n";
    std::cout << "4. Horizontal Sobel kernel\n";
    std::cout << "5. Vertical Sobel kernel\n";
    while (true) {
        std::cout << "Please choose a kernel: ";
        int k = 0;
        std::cin >> k;
        if (k < 1 || k > 5)
            std::cout << "The kernel must be between 1 and 5!\n\n";
        else
            return k;
    }
}

void run() {
    std::ifstream fin("baboon.ascii.pgm");
    std::ofstream fout("photo.pgm");

    Image image(512, 512);
    image.load("baboon.ascii.pgm");

    Image result(512, 512);
    while (true) {
        printMenu();
        int option = correctOption();
        if (option == 0)
            break;
        if (option == 1) {
            int alpha = correctGain();
            int beta;
            std::cout << "Please introduce a value for the bias: ";
            std::cin >> beta;
            BrightnessContrast b(alpha, beta);
            b.process(image, result);
            result.save("photo.pgm");
            image = result;
            std::cout << "\n\n";

        } else if (option == 2) {
            double gama;
            std::cout << "Please introduce the value for gama: ";
            std::cin >> gama;
            GamaCorrector g(gama);
            g.process(image, result);
            result.save("photo.pgm");
            image = result;
            std::cout << "\n\n";

        } else if (option == 3) {
            int k = chooseKernel();
            Image kernel(3, 3);
            if (k == 1) {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        if (i == j && i == 2)
                            kernel.at(i, j) = 1;
                        else kernel.at(i, j) = 0;
                Convolution c(kernel, normalScaleFunction);
                c.process(image, result);
            } else if (k == 2) {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        kernel.at(i, j) = 1;
                Convolution c(kernel, ScaleFunction);
                c.process(image, result);
            } else if (k == 3) {
                int ker[4][4] = {{1, 2, 1},
                                 {2, 4, 2},
                                 {1, 2, 1}};
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        kernel.at(i, j) = ker[i][j];
                Convolution c(kernel, ScaleFunction);
                c.process(image, result);
            } else if (k == 4) {
                int ker[4][4] = {{1,  2,  1},
                                 {0,  0,  0},
                                 {-1, -2, -1}};
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        kernel.at(i, j) = ker[i][j];
                Convolution c(kernel, ScaleFunction);
                c.process(image, result);
            } else {
                int ker[4][4] = {{-1, 0, 1},
                                 {-2, 0, 2},
                                 {-1, 0, 1}};
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        kernel.at(i, j) = ker[i][j];
                Convolution c(kernel, ScaleFunction);
                c.process(image, result);
            }
            result.save("photo.pgm");
            image = result;
            std::cout << "\n\n";

        } else if (option == 4) {
            result = image;
            std::cout << "Please introduce the x coordinate for the center for the circle: ";
            int x;
            std::cin >> x;
            std::cout << "Please introduce the y coordinate for the center for the circle: ";
            int y;
            std::cin >> y;
            Point center(x, y);
            std::cout << "Please introduce a value for the radius of the circle: ";
            int radius;
            std::cin >> radius;
            std::cout << "Please introduce a value between 0 and 255 for the color of the circle: ";
            int color;
            std::cin >> color;
            drawCircle(result, center, radius, color);
            result.save("photo.pgm");
            image = result;
            std::cout << "\n\n";

        } else if (option == 5) {
            result = image;

            std::cout << "Please introduce the x coordinate for the first point: ";
            int x;
            std::cin >> x;
            std::cout << "Please introduce the y coordinate for the first point: ";
            int y;
            std::cin >> y;
            Point point1(x, y);
            std::cout << "Please introduce the x coordinate for the second point: ";
            std::cin >> x;
            std::cout << "Please introduce the y coordinate for the second point: ";
            std::cin >> y;
            Point point2(x, y);
            std::cout << "Please introduce a value between 0 and 255 for the color of the line: ";
            int color;
            std::cin >> color;
            drawLine(result, point1, point2, color);
            std::cout << "\n\n";

        } else if (option == 6) {
            result = image;

            std::cout
                    << "Press 1 if you want to give the coordinates of the top-left corner and the width and height of the rectangle\n";
            std::cout
                    << "Press 2 if you want to give the coordinates of the top-left and right-bottom points of the rectangle\n";
            int answer;
            std::cin >> answer;

            int x, y;

            std::cout << "Please introduce the x coordinate of the top-left point: ";
            std::cin >> x;
            std::cout << "Please introduce the y coordinate of the top-left point: ";
            std::cin >> y;
            Point topLeft(x, y);


            if (answer == 1) {
                int width, height;
                std::cout << "Introduce the value for width: ";
                std::cin >> width;
                std::cout << "Introduce the value for height: ";
                std::cin >> height;
                std::cout << "Please introduce a value between 0 and 255 for the color of the rectangle: ";
                int color;
                std::cin >> color;
                Rectangle rectangle(x, y, width, height);
                drawRectangle(result, rectangle, color);
                result.save("photo.pgm");
                image = result;
            } else {
                std::cout << "Please introduce the x coordinate of the right-bottom point: ";
                std::cin >> x;
                std::cout << "Please introduce the y coordinate of the right-bottom point: ";
                std::cin >> y;
                Point rightBottom(x, y);
                std::cout << "Please introduce a value between 0 and 255 for the color of the rectangle: ";
                int color;
                std::cin >> color;
                drawRectangle(result, topLeft, rightBottom, color);
                result.save("photo.pgm");
                image = result;
            }

            std::cout << "\n\n";
        }
    }
}

int main() {
    run();
    return 0;
}

