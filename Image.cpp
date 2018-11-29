//
// Created by DrazorV on 22-Nov-18.
//
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "ppm/ppm.h"
#include "Image.h"
#include "Color.h"

using namespace imaging;
using namespace std;

Color * Image::getRawDataPtr(){
    return buffer;
}


Color Image::getPixel(unsigned int x, unsigned int y)const{
    if (x < 0 || y < 0 || x > width || y > height) {
        return {0, 0, 0};
    }
    else {
        return buffer[width * x + y];
    }
}
void Image::setPixel(unsigned int x, unsigned int y, Color & value){
        buffer[width * x + y] = value;
}

void Image::setData(const Color * & data_ptr){
    if (width == 0 || height == 0 || buffer == nullptr ) {
        return;
    }
    *buffer = *data_ptr;

}

Image::Image()
    :width(0), height(0), buffer(nullptr){}

Image::Image(unsigned int width, unsigned int height)
        :buffer(nullptr){
        this->width = width;
        this->height = height;
    }

Image::Image(unsigned int width, unsigned int height, const Color * data_ptr){
        this->width = width;
        this->height = height;
        *buffer = *data_ptr;
    }

Image::Image(const Image & src){
        width = src.getWidth();
        height = src.getHeight();
        buffer = src.buffer;
    }

Image::~Image() = default;

Image & Image::operator = (const Image &right) {
    if(&right == this) return *this;
    width  = right.width;
    height = right.height;
    buffer = right.buffer;
    return *this;
}

bool Image::load(const string & filename, const string & format){
    unsigned int *w = &width;
    unsigned int *h = &height;
    if(tolower(filename.find(format)) != *".ppm"){
        float * ImgPointer = ReadPPM(filename.c_str(),(int*) w,(int*) h);
        if(ImgPointer == nullptr) return false;
        buffer = new Color[*w * *h * 3];
        for(unsigned int i=0; i < *w * *h * 3; i++) {
            buffer[i] = Color(ImgPointer[i],ImgPointer[i+1],ImgPointer[i+2]);
        }
        return true;
    } else return false;
}

bool Image::save(const string & filename,const string & format){
    if(tolower(filename.find(format)) != *".ppm"){
        Color * data = getRawDataPtr();
        auto * transition = new float[width * height * 3];
        for(unsigned int i = 0;i < width * height * 3; i++){
            transition[i] = data[i][0];
            transition[i+1] = data[i][1];
            transition[i+2] = data[i][2];
        }
        return WritePPM(transition,width,height,filename.c_str());
    } else{
        return false;
    }
}

