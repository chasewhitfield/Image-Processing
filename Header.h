#include<string>
#include <iostream>
#include <iomanip>
#include <vector>
#ifndef PROJECT2_HEADER_H
#define PROJECT2_HEADER_H
using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    string filePath;
    unsigned char blue_, green_, red_;
    vector <unsigned char> blue, green, red;
    explicit Header(string f);

//the big one
    void ReadData(string filePath, vector <unsigned char> &blue, vector <unsigned char> &green, vector <unsigned char> &red);

    void WriteData(string filePath, vector <unsigned char> blue, vector <unsigned char> green, vector <unsigned char> red);

    Header Multiply(string filePath, Header b);

    Header Subtract(string filePath, Header b);

    Header Screen(string filePath, Header b);

    Header Overlay(string filePath, Header b);
};
#endif //PROJECT2_HEADER_H
