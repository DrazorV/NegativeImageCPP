#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Color.h"
#include "Image.h"
#include "ppm/ppm.h"

using namespace std;
using namespace imaging;

string extension(const char * filename);
string rename(const char * filename);

int main(int agrc, char *argv[]) {
    string input;
    const char * filename = new char[50];
    unsigned int *w,  *h , width = 0 , height = 0;
    w = &width, h = &height;
    auto * colors = new Color[*w * *h];

    Image image(*w,*h);
	//checking if there is an argument with the name of the file
    if(agrc == 1) {
        cout << "Please insert the full path to the file you want to load:" << endl;
        getline(cin,input);
        filename = input.c_str();
    }else if(agrc > 1) {
        input = argv[1];
        filename = input.c_str();
    }
    bool isLoaded = image.load(filename, extension(filename));
    //neg img will be saved here
    Image img = image;
    // value for white image
    Color white(1, 1, 1);
	//check if image is loaded
    if (isLoaded) {
        colors = image.getRawDataPtr();
        cout << "File has been loaded successfully!" << endl;
    } else {
        cout << "File could not be loaded properly!" << endl;
    }
	//pixel = white - pixel makes the negative
    for (unsigned int i = 0; i < *w; i++) {
        for (unsigned int j = 0; i < *h; i++) {
            Color pixel = image.getPixel(i, j);
            pixel = white - pixel;
            img.setPixel(i, j, pixel);
        }
    }
	//checks if save was successfull
    bool saver = img.save(rename(filename), ".ppm");
    if (saver) {
        cout << ("The picture has been saved successfully. ");
    }
    cout << "The width is: " << image.getWidth() << " and the height is: " << image.getHeight() << endl;
	system("pause");
}


//gets the type of the file
string extension(const char * filename){
    string name = filename;
    string extension;
    for(unsigned int i = 0; i < name.size() ; i++){
        if(name[i] == '.'){
            extension.append(name,i,name.size());
            return extension;
        }
    }
    return extension;
}

//creates the name for the nagative image
string rename(const char * filename){
    string name = filename;
    string rename;
    for(unsigned int i = 0; i < name.size() ; i++){
        if(name[i] == '.'){
            rename = name;
            rename.erase(i,rename.size());
            rename.append("_neg");
            rename.append(extension(filename));
            return rename;
        }
    }
    return rename;
}