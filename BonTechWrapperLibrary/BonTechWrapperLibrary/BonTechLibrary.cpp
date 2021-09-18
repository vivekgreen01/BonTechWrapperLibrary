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
    unsigned short h, w;
    nErrorCode = ImageCapGetFrameSize(nSensorIP, &w, &h);
    *nWidth = w;
    *nHeight = h;
    return nErrorCode;
}

int __stdcall SetAcquisitionMode(unsigned int nSensorIP, int nMode)
{
    nErrorCode = ImageCapModeChange(nSensorIP, nMode);
    return nErrorCode;
}

