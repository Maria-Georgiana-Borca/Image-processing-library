cmake_minimum_required(VERSION 3.24)
project(Image_processing_library)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Image_processing_library
        Size.cpp
        Size.h Point.h Point.cpp Rectangle.h Rectangle.cpp Image.h Image.cpp main.cpp ImageProcessing.h ImageProcessing.cpp drawing.h drawing.cpp)
