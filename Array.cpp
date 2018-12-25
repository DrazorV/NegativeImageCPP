//
// Created by DrazorV on 19-Dec-18.
//

#include "Array.h"
using namespace math;

template<typename T>
vector<T> *Array<T>::getRawDataPtr() {return buffer;}

template<typename T>
T Array<T>::getValue(unsigned int x, unsigned int y) const {
    T color = buffer[x + width*y];
    if (x > getWidth() || y > getHeight()) return T(0, 0, 0);
    unsigned int first = (x + y * width);
    color.r = color[first];
    color.g = color[first + 1];
    color.b = color[first + 2];
    return color;
}

template<typename T>
void Array<T>::setValue(unsigned int x, unsigned int y, T &value) {
    T color = buffer[x + width*y];
    if (x > getWidth() || y > getHeight()) return;
    unsigned int first = (x + y * width);
    color[first] = value.r;
    color[first + 1] = value.g;
    color[first + 2] = value.b;
    buffer[x + width*y] = color;
}

template<typename T>
void Array<T>::setData(const vector<T> *&data_ptr) {
    if (width == 0 || height == 0 || buffer.empty()) return;
    for (unsigned int i = 0; i<width*height; i++) buffer.push_back(data_ptr[i]);
}

template<typename T>
Array<T>::Array():width(0), height(0), buffer(nullptr){}

template<typename T>
Array<T>::Array(unsigned int width, unsigned int height):buffer(nullptr){
    this->width = width;
    this->height = height;
}

template<typename T>
Array<T>::Array(unsigned int width, unsigned int height, const vector<T> *data_ptr) {
    this->width = width;
    this->height = height;
    vector<T> buffer(width*height);
    for (unsigned int i = 0; i<width*height; i++) buffer.push_back(data_ptr[i]);
}

template<typename T>
Array<T>::Array(const Array &src) {
    width = src.width;
    height = src.height;
    for (unsigned int i = 0; i < width*height; i++) buffer.push_back(src.buffer[i]);
}

template<typename T>
Array<T>::~Array(){if (!buffer.empty()) delete(buffer);}

template<typename T>
Array<T> &Array<T>::operator=(const Array &right) {
    if (&right == this) return *this;
    if (!buffer.empty()) buffer.erase(buffer.begin(), buffer.end());
    width = right.width;
    height = right.height;
    for (unsigned int i = 0; i< width*height; i++) buffer.push_back(right.buffer[i]);
    return *this;
}

template<typename T>
T &Array<T>::operator()(unsigned int i, unsigned int j) {
    if (j < getWidth() && i < getHeight()) return (unsigned int)buffer[j * getHeight() + i];
    else return -1;
}

