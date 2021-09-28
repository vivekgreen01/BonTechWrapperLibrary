// TestApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "nivision.h"
#include <fstream>
using namespace std;

int readRawFile(unsigned short* pSrc, int width, int height)
{
    ifstream file;
    file.open("test.raw", ios::in | ios::binary);
    if (file.is_open() == true)
    {
        file.read(reinterpret_cast<char*>(pSrc), width * height * 2);
        file.close();
        return 1;
    }
    else return 0;
}

int main()
{
    /*int m_HistogramSize = 1 << 16;
    std::cout << "Hello World!\n";
    std::cout << sizeof(short int)<<std::endl;

    short int x= 65535;
    short int y= 32768;
    int z = x ^ y;
    std::cout << z<<std::endl;*/

    Image* myImage;
    PixelValue pixel;
    ImageInfo myImageInfo;
    int LVHeight, LVWidth, handle,y;
    LVHeight = 3052;
    LVWidth = 2500;
    pixel.grayscale = 65535;

    unsigned short* pSrc = new unsigned short[LVWidth * LVHeight * 2];
    readRawFile(pSrc, LVWidth, LVHeight);

    myImage = imaqCreateImage(IMAQ_IMAGE_U16, 3);
    imaqSetImageSize(myImage, LVWidth, LVHeight);
    imaqFillImage(myImage, pixel, NULL);
    imaqGetImageInfo(myImage, &myImageInfo);
    
    imaqGetWindowHandle(&handle);
    imaqSetWindowSize(handle, 1280, 720);
    imaqSetWindowZoomToFit(handle, 1);
    imaqDisplayImage(myImage, handle, 1);

    cin >> y;

    std::cout << "ImageType = " << myImageInfo.imageType<<std::endl;
    std::cout << "PixelsPerLine = " << myImageInfo.pixelsPerLine<<std::endl;
    for (y = 0; y < LVHeight; ++y)
    {
        memcpy((unsigned short*)myImageInfo.imageStart + myImageInfo.pixelsPerLine * y, pSrc + LVWidth * y, LVWidth*2);
    }

    imaqDisplayImage(myImage, handle, 1);
    cin >> y;

    imaqDispose(myImage);
    delete[] pSrc;

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
