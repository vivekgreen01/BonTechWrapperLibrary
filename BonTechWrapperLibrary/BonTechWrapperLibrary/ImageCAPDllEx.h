#include <windows.h>
#ifndef __IMAGECAP_DLLEX_H__
#define __IMAGECAP_DLLEX_H__


#ifdef _USRDLL
#define DLLFunction  __declspec(dllexport)
#else
#define DLLFunction  __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	
/******************************************************************************
*   ERROR CODE DEFINE
*******************************************************************************/
#define IMAGECAP_SOCKET_LOAD_ERROR      0x0001
#define IMAGECAP_INVALID_SOCKET_ERROR   0x0002
#define IMAGECAP_BIND_SOCKET_ERROR      0x0003
#define IMAGECAP_SOCKET_OPTION_ERROR    0x0004
#define IMAGECAP_COMMAND_SEND_ERROR     0x0005
#define IMAGECAP_COMMAND_RECV_ERROR     0x0006
#define IMAGECAP_RECV_TIMEOUT_ERROR     0x0007
#define IMAGECAP_ACK_SEND_ERROR         0x0008
#define IMAGECAP_NO_SENSOR_ERROR        0x0009
#define IMAGECAP_REGISTER_TYPE_ERROR    0x000A
#define IMAGECAP_GET_HOST_NAME_ERROR    0x000B
#define IMAGECAP_NIC_CHECK              0x000C
#define IMAGECAP_STOP_WAIT              0x000D
#define IMAGECAP_OK					    0x0000
#define IMAGECAP_CANCEL				    0x0010
#define IMAGECAP_NEW_FRAME              0x0100
#define IMAGECAP_RECEIVING              0x0101
#define IMAGECAP_NOTREADY_RO			0x0110
#define IMAGECAP_NOTSUPPORTED			0X0111

#define IMAGECAP_FWVERSION				0x1000


#define IMAGECAP_TRIGGER_MODE				0
#define IMAGECAP_AED_MODE					1
#define IMAGECAP_SOFTTRIGGER_MODE			2
#define IMAGECAP_AVG_COUNT_MODE				3
#define IMAGECAP_AVG_AED_MODE				4
#define	IMAGECAP_CONTINUOUS_MODE			5
#define	IMAGECAP_CONTINUOUS_BINNING_MODE	7
#define	IMAGECAP_VIEWER_MODE				6


///////////////////////////// Acquisition command /////////////////////
#define ACQ_ADDR_LOW				    0x0200
#define ACQ_ADDR_HIGH				    0x0201
#define ACQ_STATUS					    0x0244
#define INIT_UPDATE	                    0x0001

#define ACQ_INIT	                    0x0000
#define DARK_MODE	                    0x0001
#define BRIGHT_MODE					    0x0002
#define SOFTTRIGGER_MODE				0x0102
#define SOFTTRIGGER_INSTANT_MODE		0x0103
#define ETHERNET_MODE					0x0001
#define WIRELESS_MODE					0x0002
#define MAX_SENSOR					    4

#define LOW_SENSITIVITY					1
#define MID_SENSITIVITY					2
#define HIGH_SENSITIVITY				3
#define OLD_SENSITIVITY					4

#define EMULATOR 0


#define MEMORYRELESE(x) {if(x) delete x; x =NULL;}
#define INIFILENAME _T("\\ImageCapture.ini")
#define INIFILENAME_CON _T("\\ImageCapture_con.ini")
#define INIFILENAME_AVG _T("\\ImageCapture_avg.ini")
#define INIFILENAME_BIN _T("\\ImageCapture_bin.ini")


typedef struct strArrayRegister
{
	unsigned int nAddress;         
	unsigned int nData;            
} STRREGISTER, *PSTRREGISTER;


typedef union unionGigaCapData
{
	unsigned char   aData[1460];
	STRREGISTER     aRegisterData[182];
} GIGACAP_DATA, *PGIGACAP_DATA;

// callback data
typedef struct
{
	unsigned int nHostIP;
	unsigned int nSensorIP;
	int nErrorCode;
	void* data;
}Event;

typedef enum
{
	EVT_START_ACQUISITION,
	EVT_DETECTOR_READY,
	EVT_XRAY_ON,
	EVT_END_ACQUISITION,
	EVT_CANCEL,
	EVT_START_DELAY,
	EVT_END_DELAY
}EventID;


// callback function
typedef void(*pEventCallback)(const EventID eventID, const Event *eventData, void* customData);

DLLFunction int __stdcall ImageCapRegiterEventCallback(pEventCallback pEventCallbackProc, void* customData=NULL);


// High level function
DLLFunction int __stdcall ImageCapConnectSensor(unsigned int nHostIP, unsigned int nSensorIP, LPCTSTR lpszDataPath);

DLLFunction int __stdcall ImageCapCheckStatus(unsigned int nSensorIP);

DLLFunction int __stdcall ImageCapImageAcquistion(unsigned int nSensorIP, unsigned short* pImage, unsigned int nMode, LPCTSTR lpszRefPath);

DLLFunction int __stdcall ImageCapImageAcquistionPreExpose(unsigned int nSensorIP, unsigned short* pImage, unsigned int nMode, int nWindowTime, LPCTSTR lpszRefPath);

DLLFunction int __stdcall ImageCapImageAcquistionMainPxpose(unsigned int nSensorIP, unsigned short* pImage, unsigned int nMode, int nWindowTime, LPCTSTR lpszRefPath);

DLLFunction int __stdcall ImageCapImageAcquistion_Dynamic(unsigned int nSensorIP, unsigned short** pRefImage, unsigned int nMode, LPCTSTR lpszRefPath);

DLLFunction int __stdcall ImageCapAcquisitionCancel(unsigned int nSensorIP);

DLLFunction int __stdcall ImageCapDisConnectSensor(unsigned int nSensorIP);

DLLFunction int __stdcall ImageCapSetLogPath(LPCTSTR lpszLogPath);

DLLFunction int __stdcall ImageCapXRayExposeOn(unsigned int nSensorIP);


// Low level function
DLLFunction int __stdcall ImageCapGetHostIP(unsigned int* pHostIP,   unsigned int* pNumberofHost);

DLLFunction int __stdcall ImageCapSearchSensor(unsigned int nHostIP, unsigned int* pSensorIP, unsigned int* pNumberofSensor);

DLLFunction int __stdcall ImageCapInitSensor(unsigned int nSensorIP, LPCTSTR lpszDataPath );

DLLFunction int __stdcall ImageCapCommandSend(unsigned int nSensorIP, int nCmd);

DLLFunction int __stdcall ImageCapStartCapture(unsigned int nSensorIP, unsigned short** pRefImage, unsigned int nMode, LPCTSTR lpszRefPath);

DLLFunction int __stdcall ImageCapStopCapture(unsigned int nSensorIP);


// Config function
DLLFunction int __stdcall ImageCapGetFrameSize(unsigned int nSensorIP, unsigned short* nWidth, unsigned short* nHeight);

DLLFunction int __stdcall ImageCapGetSAEDSensitivity(unsigned int nSensorIP, int* nSens);

DLLFunction int __stdcall ImageCapSetSAEDSensitivity(unsigned int nSensorIP, int nSens);

DLLFunction int __stdcall ImageCapGetCurrentMode(unsigned int nSensorIP, int* nMode);

DLLFunction int __stdcall ImageCapModeChange(unsigned int nSensorIP, int nMode);

DLLFunction int __stdcall ImageCapEnableLog(BOOL bEnable);

DLLFunction int __stdcall ImageCapGetSensitivity(unsigned int nSensorIP, int* nSens, int* nRefSens, double* dDev);

DLLFunction int __stdcall ImageCapGetBatteryStat(unsigned int nSensorIP, int* nBat);

DLLFunction int __stdcall ImageCapGetWirelessStrength(unsigned int nSensorIP, int* nStrength);

DLLFunction int __stdcall ImageCapSetWirelessMode(unsigned int nSensorIP, int nMode);

DLLFunction int __stdcall ImageCapSetWindowTime(unsigned int nSensorIP, int nWindowTime);

DLLFunction int __stdcall ImageCapGetWindowTime(unsigned int nSensorIP, int* nWindowTime);

DLLFunction int __stdcall ImageCapSetAVGModeFrameNum(unsigned int nSensorIP, int nFrameNum);

DLLFunction int __stdcall ImageCapGetAVGModeFrameNum(unsigned int nSensorIP, int* nFrameNum);

DLLFunction int __stdcall ImageCapGetSerialNumber(unsigned int nSensorIP, LPTSTR lpszSerialNum);

DLLFunction int __stdcall ImageCapSetViewerMode(LPCTSTR lpszDataPath, int nViewerMode);

#ifdef __cplusplus
}
#endif
#endif