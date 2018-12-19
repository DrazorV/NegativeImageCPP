//
// Created by DrazorV on 21-Nov-18.
//
#include <iostream>
#include <fstream>
#include <string>
#include "ppm.h"
using namespace std;

static const int MAX_PIXEL_VALUE = 255;

namespace imaging {

	//Reads the file and checks if the header of ppm file is correct.
    float * ReadPPM(const char *filename, int * w, int * h) {
        string format;
        int depth;
        ifstream file(filename, ios::in | ios::binary);
        float *imgPointer = nullptr;

        if (!file) {
            cout << "File could not be opened!" << endl;
            return nullptr;
        }

        file >> format;
        if (format != "P6") {
            cout << "Image Format wrong or missing!" << endl;
            return nullptr;
        }
        file >> *w;
        if (*w <= 0) {
            cout << "Width wrong or missing!" << endl;
        }
        file >> *h;
        if (*h <= 0) {
            cout << "Height wrong or missing!" << endl;
        }
        file >> depth;
        if (depth > MAX_PIXEL_VALUE || depth < 0) {
            cout << "Color depth wrong or missing!" << endl;
        }
        file.get();
        float buffer;
        auto *pixels = new float[*w * *h * 3];
        imgPointer = pixels;
        for (int i = 0; i < *w * *h * 3; i++) {
            buffer = float(file.get());
			//devide by 255
            pixels[i] = buffer / MAX_PIXEL_VALUE;
        }
        file.close();
        return imgPointer;
    }

	//writes the file and its header
    bool WritePPM(const float *data, int w, int h, const char *filename) {
        if (data == nullptr) return false;
        ofstream file(filename, ios::out | ios::binary);
        unsigned char buffer;
        if (!file.is_open()) {
            cout << "File could not be opened!" << endl;
            return false;
        } else {
            file << "P6" << " " << w << " " << h << " " << MAX_PIXEL_VALUE << " ";
            for (int i = 0; i < w * h * 3; i++) {
				// (1 - pixel value) * 255
                buffer = static_cast<unsigned char>((1 - data[i]) * MAX_PIXEL_VALUE);
                file << buffer;
            }
            file.close();
        }
        return true;
    }
}