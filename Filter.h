//
// Created by DrazorV on 26-Dec-18.
//
#ifndef _FILTER_H
#define _FILTER_H


#include "Image.h"
#include "Vec3.h"
#include "Array.h"
#include <math.h>
#include <vector>


using namespace std;
using namespace math;
using namespace imaging;


class Filter{
public:
    //pure virtual method
    virtual Image operator << (const Image & image) = 0;
    //constructor:

    //default
    Filter() = default;

    //copy
    Filter(const Filter &src) = default;
};


class FilterGamma: public Filter{
private:
    double gamma{};
public:
    //default constructor
    FilterGamma():Filter(){gamma = 0;};

    //copy
    FilterGamma(const FilterGamma & filtGam){};

    explicit FilterGamma(double gamma){this -> gamma = gamma;}

    void setGamma(double gamma){this -> gamma = gamma;}

    double getGamma(){return gamma;}

    Image operator << (const Image & image) override {
        Image img(image);
        for (unsigned int i = 0; i < image.getWidth(); i++)
            for (unsigned int j = 0; j < image.getHeight(); j++){
                Vec3<float> value = image.getValue(i, j);
                value.x = static_cast<float>(pow(value.x, gamma));
                value.y = static_cast<float>(pow(value.y, gamma));
                value.z = static_cast<float>(pow(value.z, gamma));
                img.setValue(i, j, value);
            }
        return img;
    }
};


class FilterLinear : public Filter {
private:
    Vec3<float> a, c;
public:
    //default constructor
    FilterLinear() :Filter(){ a = 0; c = 0; }

    FilterLinear(const Vec3<float> &a, const Vec3<float> &c){
        this->a = a;
        this->c = c;
    }
    //copy constructor
    FilterLinear(const FilterLinear & f) {}

    void setA(const Vec3<float> &a) {this->a = a;}

    Vec3<float> getA(){return a;}

    void setC(const Vec3<float> &c) {this->c = c;}

    Vec3<float> getC(){return c;}

    Image operator << (const Image & image) override {
        Image im(image);
        for (unsigned int i = 0; i < image.getWidth(); i++)
            for (unsigned int j = 0; j < image.getHeight(); j++){
                //p'(x,y) = a * p(x,y) + c
                Vec3<float> p_tone = a *image.getValue(i, j) + c;
                im.setValue(i, j, p_tone);
                Vec3<float> value = im.getValue(i, j);
                value = value.clampToUpperBound(1.0f);
                value = value.clampToLowerBound(0.0f);
                im.setValue(i, j, value);
            }
        return im;
    }

};
#endif _FILTER_H

//function<bool(string,string)> comp = [] (string& s1, string& s2) {return s1.length() > s2.length(); };
//function<bool(string&,string&)> comp = [] (string& s1, string& s2) {return s1.length() > s2.length(); };
//function<bool(string,string)> comp = [] (string&& s1, string&& s2) {return s1.length() > s2.length(); };
//function<bool(string,string)> comp = [] (const string& s1, const string& s2) {return s1.length() > s2.length(); };