//
// Created by DrazorV on 22-Nov-18.
//
#include <iostream>
#include <fstream>
#include <string>
#include "ppm/ppm.h"
#include "Image.h"
#include "Color.h"
#include "Vec3.h"
#include <vector>
#include "Array.h"

using namespace imaging;
using namespace std;
using namespace math;


/*! Default constructor.
*
* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
*/
Image::Image():Array<Vec3<float>>(){}

/*! Constructor with width and height specification.
*
* \param width is the desired width of the new image.
* \param height is the desired height of the new image.
*/
Image::Image(unsigned int width, unsigned int height):Array<Vec3<float>>(width,height){}


/*! The Image destructor.
*/
Image::~Image() = default;

/*! Copy constructor.
*
* \param src is the source image to replicate in this object.
*/
Image::Image(const Image &src):Array<Vec3<float>>(src){}

/*!
* Loads the image data from the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
* Image object is initialized, its contents are wiped out before initializing it to the width, height and data
* read from the file.
*
* \param filename is the string of the file to read the image data from.
* \param format specifies the file format according to which the image data should be decoded from the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the loading completes successfully, false otherwise.
*/
bool Image::load(const string & filename, const string & format){
    unsigned int *w = &width;
    unsigned int *h = &height;
    if(tolower(filename.find(format)) != *".ppm"){
        float * ImgPointer = ReadPPM(filename.c_str(),(int*) w,(int*) h);
        if(ImgPointer == nullptr) return false;

        if(buffer.empty()) buffer.resize(*w * *h);

        for(unsigned int i = 0; i < *w * *h * 3; i+=3) for(unsigned int j = 0;j < *w * *h;j++) buffer[j] = Vec3<float>(ImgPointer[i],ImgPointer[i+1],ImgPointer[i+2]);

        return true;
    } else return false;
}

/*!
* Stores the image data to the specified file, if the extension of the filename matches the format string.
*
* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
* Image object is not initialized, the method should return immediately with a false return value.
*
* \param filename is the string of the file to write the image data to.
* \param format specifies the file format according to which the image data should be encoded to the file.
* Only the "ppm" format is a valid format string for now.
*
* \return true if the save operation completes successfully, false otherwise.
*/
bool Image::save(const string & filename,const string & format){
    if(tolower(filename.find(format)) != *".ppm") {

        //apodsmefsh mnhmhs na kanoume!!!
        auto *transition = new float[width * height * 3];
        for (unsigned int i = 0; i < width * height * 3; i+=3)for (unsigned int j = 0 ; j < width * height; j++) {
            transition[i] = buffer[j][0];
            transition[i + 1] = buffer[j][1];
            transition[i + 2] = buffer[j][2];
        }
        WritePPM(transition,width,height,filename.c_str());
        return !(width == 0 || height == 0 || buffer.empty());
    } else{
        return false;
    }
}

