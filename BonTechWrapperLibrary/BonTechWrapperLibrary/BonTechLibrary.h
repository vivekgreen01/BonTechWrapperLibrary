#pragma once
#ifndef BONTECHLIBRARY_EXPORTS
#define BONTECHLIBRARY_EXPORTS
#endif // !BONTECHLIBRARY_EXPORTS


#ifdef BONTECHLIBRARY_EXPORTS
#define BONTECHLIBRARY_API __declspec(dllexport)
#else
#define BONTECHLIBRARY_API __declspec(dllimport)
#endif

typedef struct TH_PARAM
{
	unsigned short* pImage;
	int nMode;
	int nDetectorMode;
	BOOL bCal;
	int nDarkNum;

	char *strFileName;

}TH_PARAM, * PTH_PARAM;

UINT ImageAcqThread(LPVOID lpParam);
UINT ImageSaveThread(LPVOID lpParam);
UINT ImageCalThread(LPVOID lpParam);

extern "C" BONTECHLIBRARY_API int __stdcall GetSphereSAandVol(double radius, double* sa, double* vol);

extern "C" BONTECHLIBRARY_API int __stdcall Connect(unsigned int nHostIP, unsigned int nSensorIP, LPTSTR ConfigDir);

extern "C" BONTECHLIBRARY_API int __stdcall Disconnect(unsigned int nSensorIP);

extern "C" BONTECHLIBRARY_API int __stdcall GetImageSize(unsigned int nSensorIP, unsigned short* nWidth, unsigned short* nHeight);

extern "C" BONTECHLIBRARY_API int __stdcall SetAcquisitionMode(unsigned int nSensorIP, int nMode);
