#include "pch.h"
#include<fstream>
#include "math.h"
#include "BonTechLibrary.h"
#include "ImageCAPDllEx.h"
using namespace std;
#define M_PI 3.14

static int nErrorCode;

//Test Function
double GetSA(double radius)
//Calculate surface area of a Sphere for given radius
{
    return 4 * M_PI * radius * radius;
}

double GetVol(double radius)
//Calculate volume of a Sphere for given radius
{
    return 4.0 / 3.0 * M_PI * pow(radius, 3.0);
}

int __stdcall GetSphereSAandVol(double radius, double* sa, double* vol)
//Calculate the surface area and volume of a sphere with given radius
{
    if (radius < 0)
        return false; //return false (0) if radius is negative
    *sa = GetSA(radius);
    *vol = GetVol(radius);
    return true;
}


int __stdcall Connect(unsigned int nHostIP, unsigned int nSensorIP, LPTSTR ConfigDir)
{
    nErrorCode = ImageCapConnectSensor(nHostIP, nSensorIP, ConfigDir);
    return nErrorCode;
}

int __stdcall Disconnect(unsigned int nSensorIP)
{
    nErrorCode = ImageCapDisConnectSensor(nSensorIP);
    return nErrorCode;
}

int __stdcall GetImageSize(unsigned int nSensorIP, unsigned short* nWidth, unsigned short* nHeight)
{
    unsigned short height, width;
    nErrorCode = ImageCapGetFrameSize(nSensorIP, &width, &height);
    *nWidth = width;
    *nHeight = height;
    return nErrorCode;
}

int __stdcall SetAcquisitionMode(unsigned int nSensorIP, int nMode)
{
    nErrorCode = ImageCapModeChange(nSensorIP, nMode);
    return nErrorCode;
}

int __stdcall StartContinuousAcquisition(unsigned int nSensorIP)
{//Send ImageCapCommandSend and then call ImageCapStartCapture
    //TODO: Launch a Thread
    return nErrorCode;

}

int __stdcall StopContinuousAcquisition(unsigned int nSensorIP)
{
    nErrorCode = ImageCapStopCapture(nSensorIP);
    return nErrorCode;
}

int __stdcall CaptureSingleImage(unsigned int nSensorIP)
{//Capture using ImageCap
    //TODO: Capture Single Image and pass it to LabVIEW
    //nErrorCode = ImageCapImageAcquistion(nSensorIP, unsigned short *pImage)
    return nErrorCode;
}

int __stdcall CancelSingleImageCapture(unsigned int nSensorIP)
{
    nErrorCode = ImageCapAcquisitionCancel(nSensorIP);
    return nErrorCode;
}

int readRawFile(char* pSrc, int width, int height)
{
    ifstream file;
    file.open("test.raw", ios::in | ios::binary);
    if (file.is_open() == true)
    {
        file.read(pSrc, width * height * 2);
        file.close();
        return 1;
    }
    else return 0;
}


int __stdcall CopyImageToLV(IMAQ_Image *LVImage) 
{
    Image *lvImage, *myImage;
    PixelValue pixel;
    ImageInfo lvImageInfo, myImageInfo;
    int y, LVHeight, LVWidth;
    lvImage = LVImage->address;
    pixel.grayscale = 32000;
    
    myImage = imaqCreateImage(IMAQ_IMAGE_U16, 3);
    imaqGetImageSize(lvImage, &LVWidth, &LVHeight);
    imaqSetImageSize(myImage, LVWidth, LVHeight);
    imaqFillImage(myImage,pixel, NULL);

    char* pSrc = new char[LVHeight * LVWidth * 2];
    readRawFile(pSrc, LVWidth, LVHeight);

    imaqGetImageInfo(myImage, &myImageInfo);
    imaqGetImageInfo(lvImage, &lvImageInfo);
    

    for (y = 0; y < LVHeight; ++y)
    {
        memcpy((unsigned short*)lvImageInfo.imageStart + y * lvImageInfo.pixelsPerLine,
            pSrc + y * LVHeight, LVWidth*2);
    }
    LVImage->address = lvImage;
    delete[] pSrc;
    return 0;
}

int __stdcall Copy_C_Image_To_LabVIEW_Image(char* LVImagePtr, int LVLineWidth, int LVWidth, int LVHeight)
{
    ImageInfo testImageInfo;
    Image* testImage;
    int y;
    PixelValue pixelValue;

    char* pSrc = new char[LVHeight * LVWidth * 2];
    readRawFile(pSrc, LVWidth, LVHeight);

    // Create the image as IMAQ_IMAGE_U8
    testImage = imaqCreateImage(IMAQ_IMAGE_U16, 3);

    // Set the image size
    imaqSetImageSize(testImage, LVWidth, LVHeight);

    // Fill the image with 128's
    pixelValue.grayscale = 32000;
    imaqFillImage(testImage, pixelValue, NULL);

    // Get the image info -- this should be that same as the height and width 
    // the image was created from
    imaqGetImageInfo(testImage, &testImageInfo);

    // Copy, line by line, the C image into the LV image.
    for (y = 0; y < LVHeight*2; ++y) {
        memcpy(LVImagePtr + y * LVLineWidth, (unsigned short*)testImageInfo.imageStart+testImageInfo.pixelsPerLine*y, LVWidth*2);
    }

    // Dispose of the C image
    imaqDispose(testImage);
    delete[] pSrc;
    return 0;
}
