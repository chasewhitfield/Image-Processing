#include <iostream>
#include <iomanip>
#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;
#include "Header.h"

//set all header data to default, create object specific vectors holding all RGB values
Header ::Header(string f)
{
    this->filePath = f;
    this->idLength = 0;
    this->colorMapType = 0;
    this->dataTypeCode = 0;
    this->colorMapOrigin = 0;
    this->colorMapLength = 0;
    this->colorMapDepth = 0;
    this->xOrigin = 0;
    this->yOrigin = 0;
    this->width = 0;
    this->height = 0;
    this->bitsPerPixel = 0;
    this->imageDescriptor = 0;
    this->blue_ = 0;
    this->green_ = 0;
    this->red_ = 0;
    vector <unsigned char> red;
    vector <unsigned char> green;
    vector <unsigned char> blue;
}

//Read in from desired file location and fill each vector with RGB values respectively for each pixel
void Header::ReadData(string filePath, vector <unsigned char> &blue, vector <unsigned char> &green, vector <unsigned char> &red) {
    ifstream inFile(filePath, ios_base::binary);
    if (inFile.is_open()) {
        inFile.read(&idLength, sizeof(idLength));

        inFile.read(&colorMapType, sizeof(colorMapType));

        inFile.read(&dataTypeCode, sizeof(dataTypeCode));

        inFile.read((char *) &colorMapOrigin, sizeof(colorMapOrigin));

        inFile.read((char *) &colorMapLength, sizeof(colorMapLength));

        inFile.read(&colorMapDepth, sizeof(colorMapDepth));

        inFile.read((char *) &xOrigin, sizeof(xOrigin));

        inFile.read((char *) &yOrigin, sizeof(yOrigin));

        inFile.read((char *) &width, sizeof(width));

        inFile.read((char *) &height, sizeof(height));

        inFile.read(&bitsPerPixel, sizeof(bitsPerPixel));

        inFile.read(&imageDescriptor, sizeof(imageDescriptor));

        for (unsigned int n = 0; n < (unsigned int) (width * height); n++)
        {
            inFile.read(reinterpret_cast<char *>(&blue_), sizeof(blue_));
            blue.push_back(blue_);

            inFile.read(reinterpret_cast<char *>(&green_), sizeof(green_));
            green.push_back(green_);

            inFile.read(reinterpret_cast<char *>(&red_), sizeof(red_));
            red.push_back(red_);
        }

        inFile.close();
    }
}

//write data from RGB vectors to a specific filepath
void Header::WriteData(string filePath, vector<unsigned char> blue, vector<unsigned char> green,vector<unsigned char> red)
{
    ofstream file(filePath, ios_base::binary);
    file.write(&idLength, sizeof(idLength));

    file.write(&colorMapType, sizeof(colorMapType));

    file.write(&dataTypeCode, sizeof(dataTypeCode));

    file.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));

    file.write((char*)&colorMapLength, sizeof(colorMapLength));

    file.write(&colorMapDepth, sizeof(colorMapDepth));

    file.write((char*)&xOrigin, sizeof(xOrigin));

    file.write((char*)&yOrigin, sizeof(yOrigin));

    file.write((char*)&width, sizeof(width));

    file.write((char*)&height, sizeof(height));

    file.write(&bitsPerPixel, sizeof(bitsPerPixel));

    file.write(&imageDescriptor, sizeof(imageDescriptor));

    for (unsigned int n = 0; n < (unsigned)green.size(); n++)
    {
        file.write(reinterpret_cast<const char *>(&blue.at(n)), sizeof(blue.at(n)));
        file.write(reinterpret_cast<const char *>(&green.at(n)), sizeof(green.at(n)));
        file.write(reinterpret_cast<const char *>(&red.at(n)), sizeof(red.at(n)));
    }
    file.close();
}

//multiply given object's RGB values by parameter object's RGB values and enter a filePath to rename original to
Header Header::Multiply(string filePath_, Header b)
{

    filePath = filePath_;

    for (unsigned int n = 0; n < (unsigned)green.size(); n++)
    {
        //C = A * B (A & B reduced to range 0-1)
        float hold;
        hold = (255.0f * ((blue.at(n) / 255.0f) * (b.blue.at(n) / 255.0f))+ 0.5f);
        blue.at(n) = (unsigned char) hold;
        hold = (255.0f * ((green.at(n) / 255.0f) * (b.green.at(n) / 255.0f))+ 0.5f);
        green.at(n) = (unsigned char) hold;
        hold = (255.0f * ((red.at(n) / 255.0f) * (b.red.at(n) / 255.0f))+ 0.5f);
        red.at(n) = (unsigned char) hold;
    }
    return *this;
}

//subtract parameter object's RGB values from original object's. Set to 0 if result < 0
Header Header::Subtract(string filePath_, Header b)
{
    filePath = filePath_;

    for (unsigned int n = 0; n < (unsigned)green.size(); n++)
    {
        //C = B1 - B2
        int hold;
        hold = blue.at(n);
        hold -= b.blue.at(n);
        if(hold < 0)
        {
            blue.at(n) = 0;
        }
        else
        {
            blue.at(n) = (unsigned char)hold;
        }

        hold = green.at(n);
        hold -= b.green.at(n);
        if(hold < 0)
        {
            green.at(n) = 0;
        }
        else
        {
            green.at(n) = (unsigned char)hold;
        }

        hold = red.at(n);
        hold -= b.red.at(n);
        if(hold < 0)
        {
            red.at(n) = 0;
        }
        else
        {
            red.at(n) = (unsigned char)hold;
        }
    }
    return *this;
}

//C = 1-(1-A)*(1-B)
Header Header::Screen(string filePath_, Header b)
{
    filePath = filePath_;
    for (unsigned int n = 0; n < (unsigned)green.size(); n++)
    {
        float hold = ((1.0f - (1.0f - blue.at(n) / 255.0f) * (1.0f - b.blue.at(n) / 255.0f)) * 255.0f) + 0.5f;
        blue.at(n) = (unsigned char)hold;

        hold = ((1.0f - (1.0f - green.at(n) / 255.0f) * (1.0f - b.green.at(n) / 255.0f)) * 255.0f) + 0.5f;
        green.at(n) = (unsigned char)hold;

        hold = ((1.0f - (1.0f - red.at(n) / 255.0f) * (1.0f - b.red.at(n) / 255.0f)) * 255.0f) + 0.5f;
        red.at(n) = (unsigned char)(hold);
    }
    return *this;
}

//If b > 0.5 (on scale 0-1) C = 1 - 2 * (1 - A) * (1 - B)
//Otherwise, C = 2 * A * B
Header Header::Overlay(string filePath_, Header b)
{
    filePath = filePath_;
    for(unsigned int n = 0; n < (unsigned)green.size(); n++)
    {
        float hold1 = blue.at(n) / 255.0f;
        float hold2 = b.blue.at(n) / 255.0f;
        if(hold2 > 0.5)
        {
            hold1 = 1.0f - 2.0f * (1.0f - hold1) * (1.0f - hold2);
        }
        else
        {
            hold1 = 2.0f * hold1 * hold2;
        }
        hold1 *= 255.0f;
        hold1 += 0.5f;
        blue.at(n) = (unsigned char)hold1;


        hold1 = green.at(n) / 255.0f;
        hold2 = b.green.at(n) / 255.0f;
        if(hold2 > 0.5)
        {
            hold1 = 1.0f - 2.0f * (1.0f - hold1) * (1.0f - hold2);
        }
        else
        {
            hold1 = 2.0f * hold1 * hold2;
        }
        hold1 *= 255.0f;
        hold1 += 0.5f;
        green.at(n) = (unsigned char)hold1;

        hold1 = red.at(n) / 255.0f;
        hold2 = b.red.at(n) / 255.0f;
        if(hold2 > 0.5)
        {
            hold1 = 1.0f - 2.0f * (1.0f - hold1) * (1.0f - hold2);
        }
        else
        {
            hold1 = 2.0f * hold1 * hold2;
        }
        hold1 *= 255.0f;
        hold1 += 0.5f;
        red.at(n) = (unsigned char)hold1;
    }
    return *this;
}



