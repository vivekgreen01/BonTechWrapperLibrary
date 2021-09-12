#include <windows.h>
#ifndef __CALIBRATION_DLLEX_H__
#define __CALIBRATION_DLLEX_H__


#ifdef _USRDLL
#define DLLFunction  __declspec(dllexport)
#else
#define DLLFunction  __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	DLLFunction int __stdcall ImageCalibration(unsigned short* pObjectImage, LPCTSTR lpszRefPath, int nWidth, int nHeight, int nMode, CRect rectMargin, BOOL bBackGround);	

	DLLFunction int __stdcall ImageCalibrationMode(unsigned short* pObjectImage, LPCTSTR lpszRefPath, int nWidth, int nHeight, int nMode, CRect rectMargin, BOOL bBackGround, LPCTSTR lpszDataPath, int nAcqMode);

	DLLFunction int __stdcall ImageCalibrationMode2(unsigned short* pObjectImage, LPCTSTR lpszRefPath, int nWidth, int nHeight, int nMode, CRect rectMargin, BOOL bBackGround, LPCTSTR lpszDataPath, int nAcqMode);

	DLLFunction int __stdcall GenerateReferenceFile(unsigned short* pDarkImage, unsigned short** pBrightImage, int nBrightNum, int nAcqMode, LPCTSTR lpszSavePath, int nWidth, int nHeight);

#ifdef __cplusplus
}
#endif
#endif