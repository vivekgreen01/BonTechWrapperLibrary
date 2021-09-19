#include "pch.h"
#include "math.h"
#include "BonTechLibrary.h"
#include "ImageCAPDllEx.h"
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

int __stdcall CopyImageToLV(IMAQ_Image *LVImage) 
{
    Image* myImage, *lvImage;
    PixelValue pixel;
    ImageInfo myImageInfo, lvImageInfo;
    int y, LVHeight, LVWidth;
    lvImage = LVImage->address;
    pixel.grayscale = 16000;
    myImage = imaqCreateImage(IMAQ_IMAGE_U16, 3);
    imaqGetImageSize(lvImage, &LVWidth, &LVHeight);
    imaqSetImageSize(myImage, LVWidth, LVHeight);
    imaqFillImage(myImage,pixel, NULL);

    imaqGetImageInfo(myImage, &myImageInfo);
    imaqGetImageInfo(lvImage, &lvImageInfo);
    //LVImage->address = myImage;

    for (y = 0; y < LVHeight; ++y)
    {
        memcpy((unsigned short*)lvImageInfo.imageStart + (long long)y * (lvImageInfo.pixelsPerLine),
            (unsigned short*)myImageInfo.imageStart + (long long)y * (myImageInfo.pixelsPerLine), LVWidth);
    }
    imaqDispose(myImage);
    return 0;
}