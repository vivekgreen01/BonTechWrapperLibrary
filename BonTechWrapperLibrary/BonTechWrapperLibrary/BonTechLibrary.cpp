#include "pch.h"
#include "math.h"
#include "BonTechLibrary.h"
#include "ImageCAPDllEx.h"
#define M_PI 3.14

static int nErrorCode;

UINT ImageSaveThread(LPVOID lpParam)
{
	g_bFileSave = TRUE;
	PTH_PARAM pParam = (PTH_PARAM)lpParam;
	CImageCAP_sampleDlg* pDlg = (CImageCAP_sampleDlg*)pParam->pDlg;

	int nWidth = pDlg->m_nWidth;
	int nHeight = pDlg->m_nHeight;

	CString strFileName = pParam->strFileName;
	WriteRawImage(strFileName, pParam->pImage, nWidth, nHeight, 16);
	g_bFileSave = FALSE;

	return 0;
}

UINT ImageAcqThread(LPVOID lpParam)
{
	PTH_PARAM pParam = (PTH_PARAM)lpParam;
	unsigned short* pImage = pParam->pImage;
	int nAcqMode = pParam->nMode;
	
	unsigned short* refImg = NULL;
	int nErrorCode = 0;

	CString strFileName;
	SYSTEMTIME cur_time;
	CString year;
	CTime time;

	year.Format(_T("%d"), time.GetYear());
	year = year.Mid(2, 2);

	if (pParam->nDetectorMode == IMAGECAP_CONTINUOUS_MODE || pParam->nDetectorMode == IMAGECAP_CONTINUOUS_BINNING_MODE)
	{
		g_bDynStat = TRUE;
		nErrorCode = ImageCapCommandSend(pDlg->m_SensorIP, nAcqMode);
		if (nErrorCode != IMAGECAP_OK)
		{
			ImageCapStopCapture(pDlg->m_SensorIP);
			SendMessage(pDlg->GetSafeHwnd(), WM_IMAGERECV, (WPARAM)pParam, nErrorCode);
			return 0;
		}

		while (g_bDynStat)
		{
			nErrorCode = ImageCapStartCapture(pDlg->m_SensorIP, &refImg, nAcqMode, pDlg->m_strCalReferencePath);
			memcpy(pImage, refImg, pDlg->m_nWidth * pDlg->m_nHeight * 2);

			if (nErrorCode != IMAGECAP_NEW_FRAME)
				continue;

			// do something				
			time = CTime::GetCurrentTime();
			GetLocalTime(&cur_time);

			strFileName.Format(_T(".\\Image_%s%02d%02d_%02d%02d%02d_%03ld.raw"), year, time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), cur_time.wMilliseconds);
			pParam->strFileName = strFileName;
			AfxBeginThread(ImageSaveThread, pParam, THREAD_PRIORITY_HIGHEST);

		}
	}
	else
	{
		if (pParam->bCal)
			nErrorCode = ImageCapImageAcquistion(pDlg->m_SensorIP, pImage, nAcqMode, pDlg->m_strCalReferencePath);
		else
			nErrorCode = ImageCapImageAcquistion(pDlg->m_SensorIP, pImage, nAcqMode, NULL);
	}

	SendMessage(pDlg->GetSafeHwnd(), WM_IMAGERECV, (WPARAM)pParam, nErrorCode);

	return 0;
}



double GetSA(double radius)
{
    return 4 * M_PI * radius * radius;
}

double GetVol(double radius)
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

