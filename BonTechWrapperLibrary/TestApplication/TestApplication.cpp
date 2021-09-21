// TestApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "nivision.h"

int main()
{
    int m_HistogramSize = 1 << 16;
    std::cout << "Hello World!\n";
    std::cout << sizeof(short int)<<std::endl;

    short int x= 65535;
    short int y= 32768;
    int z = x ^ y;
    std::cout << z<<std::endl;

    Image* myImage;
    PixelValue pixel;
    ImageInfo myImageInfo;
    int LVHeight, LVWidth;
    LVHeight = 2;
    LVWidth = 4096;
    pixel.grayscale = 100;
    myImage = imaqCreateImage(IMAQ_IMAGE_U16, 3);
    imaqSetImageSize(myImage, LVWidth, LVHeight);
    imaqFillImage(myImage, pixel, NULL);
    imaqGetImageInfo(myImage, &myImageInfo);

    std::cout << "ImageType = " << myImageInfo.imageType<<std::endl;
    std::cout << "PixelsPerLine = " << myImageInfo.pixelsPerLine<<std::endl;
    imaqDispose(myImage);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
