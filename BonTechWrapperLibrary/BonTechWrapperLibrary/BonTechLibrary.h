#pragma once
#ifndef BONTECHLIBRARY_EXPORTS
#define BONTECHLIBRARY_EXPORTS
#endif // !BONTECHLIBRARY_EXPORTS


#ifdef BONTECHLIBRARY_EXPORTS
#define BONTECHLIBRARY_API __declspec(dllexport)
#else
#define BONTECHLIBRARY_API __declspec(dllimport)
#endif

//Data Structure to pass to Threads
typedef struct TH_PARAM
{
	unsigned short* pImage;
	int nMode;
	int nDetectorMode;
	BOOL bCal;
	int nDarkNum;

	char *strFileName;

}TH_PARAM, * PTH_PARAM;

/* nAcqMode is an enum that specifies the Acquisition Modes available.  
   0 - IMAGECAP_TRIGGER_MODE
	1 - IMAGECAP_AED_MODE
	2 - IMAGECAP_SOFTTRIGGER_MODE
	3 - IMAGECAP_AVG_COUNT_MODE
	4 - IMAGECAP_AVG_AED_MODE
	5 - IMAGECAP_CONTINUOUS_MODE
	6 - IMAGECAP_VIEWER_MODE
	7 - IMAGECAP_CONTINUOUS_BINNING_MODE
*/
typedef enum {
	IMAGECAP_TRIGGER_MODE,
	IMAGECAP_AED_MODE,
	IMAGECAP_SOFTTRIGGER_MODE,
	IMAGECAP_AVG_COUNT_MODE,
	IMAGECAP_AVG_AED_MODE,
	IMAGECAP_CONTINUOUS_MODE,
	IMAGECAP_VIEWER_MODE,
	IMAGECAP_CONTINUOUS_BINNING_MODE
}nAcqMode;

//Test function
extern "C" BONTECHLIBRARY_API int __stdcall GetSphereSAandVol(double radius, double* sa, double* vol);

/*Establish a connection to the X-Ray Detector
* @param nHostIP specifies the Host IP adress in the network order.
* @param nSensorIP specifies the Sensor's IP adress in the network order.
* @returns Connection Status.
*/
extern "C" BONTECHLIBRARY_API int __stdcall Connect(unsigned int nHostIP, unsigned int nSensorIP, LPTSTR ConfigDir);

/*Disconnect from the X - Ray Detector
* @param nSensorIP specifies the Sensor's IP adress in the network order.
* @returns Status whether operation is suceeded or not.
*/
extern "C" BONTECHLIBRARY_API int __stdcall Disconnect(unsigned int nSensorIP);

/*Get the Image Height and Width from the Sensor
* @param[in] nSensorIP specifies the Sensor's IP adress in the network order.
* @param[out] nWidth variable to store the width of the image.
* @param[out] nHeight variable to store the width of the image.
* @returns width and height of the image in nWidth, nHeight varaibles respectively.
*/
extern "C" BONTECHLIBRARY_API int __stdcall GetImageSize(unsigned int nSensorIP, unsigned short* nWidth, unsigned short* nHeight);

/*Set the Sensor Image Acquisition Mode
* @param nSensorIP specifies the Sensor's IP adress in the network order.
* @param nMode specifies the Acquision Mode of the Sensor. There are 7 modes available:
* 
enum{
	IMAGECAP_TRIGGER_MODE,
	IMAGECAP_AED_MODE,
	IMAGECAP_SOFTTRIGGER_MODE,
	IMAGECAP_AVG_COUNT_MODE,
	IMAGECAP_AVG_AED_MODE,
	IMAGECAP_CONTINUOUS_MODE,
	IMAGECAP_VIEWER_MODE,
	IMAGECAP_CONTINUOUS_BINNING_MODE}
* 
* @returns the Status whether operation is suceeded or not.
*/
extern "C" BONTECHLIBRARY_API int __stdcall SetAcquisitionMode(unsigned int nSensorIP, int nMode);
