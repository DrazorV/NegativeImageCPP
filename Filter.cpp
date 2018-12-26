//
// Created by DrazorV on 26-Dec-18.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Color.h"
#include "Image.h"
#include "Filter.h"
#include "ppm\ppm.h"


using namespace std;
using namespace imaging;

string extension(const char * filename);
string rename(const char * filename);


int main(int argc,char *argv[]){
    string filterG = "gamma";
    string filterL = "linear";
    string filterF = "-f";
    Image im;
    bool check = true;

    if (argc < 5) {cout << "Please check the program parameters and try again!" << endl; return 0;}

    if(!im.load(argv[argc - 1], extension(argv[argc - 1]))) {cout << "File:" << argv[argc - 1] << "could not be found. Please try again!" << endl; return 0; }

    for(unsigned int i = 0;i< argc;i++){
        string arg = argv[i];
        if(arg.find('-') == 0 && arg[1] == 'f'){
            arg = argv[i + 1];
            if(arg != filterG && arg != filterL) {cout << "Something is wrong with the filter name. Please try again!" << endl; return 0; }
            char *ptr;
            if(strtod(argv[i + 2], &ptr) == 0.0) {cout << "This parameter needs to be a number. Please try again!" << endl; check = false; return 0; }
            check = true;
        }
        if(arg.find('-') != 0 || isdigit(arg[1]) == 0) {cout << "Expected -f as parameter but didn't find it. Please try again!" << endl; check = false; return 0; }
        check = true;
    }

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