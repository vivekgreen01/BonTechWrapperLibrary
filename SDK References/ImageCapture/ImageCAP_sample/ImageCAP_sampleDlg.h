
// ImageCAP_sampleDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "ImageCAPDllEx.h"
//#include "CalibrationDllEx.h"
#include "afxcmn.h"

#define WM_IMAGERECV WM_USER+100


// CImageCAP_sampleDlg 대화 상자
class CImageCAP_sampleDlg : public CDialog
{
public:
	unsigned int m_HostIP;		
	unsigned int m_SensorIP;
	CString m_strDataReferencePath;
	CString m_strCalReferencePath;

	CString m_strDarkFile;
	CString m_strBrightFile;

	unsigned short m_nWidth;
	unsigned short m_nHeight;

	int m_nDetectorMode;


// 생성입니다.
public:
	CImageCAP_sampleDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	void DisplayErrorCode(int nErrorCode);	

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGECAP_SAMPLE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.



// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();		
	afx_msg void OnDestroy();	
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg LRESULT OnReceiveImage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton5();
	
	CString m_strLog;
	CSliderCtrl m_sliderMode;		
	
	CIPAddressCtrl m_ipHost;
	CIPAddressCtrl m_ipSensor;


	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();


	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	int m_nWindowTime;
	int m_nAVGFrameNum;
	int m_nRadioAcqMode;	
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedRadio1();
};


typedef struct TH_PARAM
{
	CDialog* pDlg;	
	unsigned short* pImage;
	int nMode;
	int nDetectorMode;
	BOOL bCal;
	int nDarkNum;

	CString strFileName;

}TH_PARAM, *PTH_PARAM;

UINT ImageAcqThread(LPVOID lpParam);
UINT ImageSaveThread(LPVOID lpParam);
UINT ImageCalThread(LPVOID lpParam);