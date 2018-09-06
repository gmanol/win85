// Win85.h : main header file for the WIN85 application
//

#if !defined(AFX_WIN85_H__BF07BEC7_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
#define AFX_WIN85_H__BF07BEC7_4202_11D3_8906_EB9C49D44C00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWin85App:
// See Win85.cpp for the implementation of this class
//
typedef void (*WRITEPROC)(BYTE,BYTE);
typedef BYTE (*READPROC)(BYTE);
typedef void (*CONFIGPROC)(void);
typedef void (*SHOWPROC) (void);
typedef void (*HIDEPROC) (void);
typedef void (*INITPROC) (int*);
typedef void (*RESETPROC) (void);
typedef BOOL (*DLGMSGPROC) (MSG*);

class CWin85App : public CWinApp
{
public:

	CWin85App();

// Devices Exported functions

	static HINSTANCE	mylib[100];
	static WRITEPROC	gDeviceWrite[100];
	static READPROC		gDeviceRead[100];
	static CONFIGPROC	gDeviceConfig[100];
	static SHOWPROC		gShowWindow[100];
	static HIDEPROC		gHideWindow[100];
	static INITPROC		gInitIRQ[100];
	static RESETPROC	gDeviceReset[100];
	static DLGMSGPROC	gDialogMessage[100];

// CWin85App Global variables

	static int gIRQMap[7];

//	gIRQMap[0]=TRAP
//	gIRQMap[1]=RST7.5
//	gIRQMap[2]=RST6.5
//	gIRQMap[3]=RST5.5
//	gIRQMap[4]=INTR
//	gIRQMap[5]=INTR Bus
//	gIRQMap[6]=INTR Call Address

	static int gRIOMap[256];
	static int gWIOMap[256];

	static CString gDevicesFilenames[100];
	static BOOL gDeviceStatus[100];

	static int gNumOfDevices;

	static CString gExecutablePath;

// CWin85App Global Conversion functions

	static CString DWord2Dec(DWORD i);

	static CString Word2Dec(WORD i);
	static CString Word2Bin(WORD i);
	static CString Word2Hex(WORD i);
	static CString Word2Hex(BYTE h,BYTE l);

	static CString Byte2Dec(BYTE i);
	static CString Byte2Bin(BYTE i);
	static CString Byte2Hex(BYTE i);

	static CString Bit2Bin(BYTE b,BYTE mask);

// ------------------------------------

	static DWORD Str2Val(CString t,BOOL* State);
	static DWORD StrHex2Val(CString str);
	static DWORD StrBin2Val(CString str);
	static BOOL Check(CString str, int Count);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWin85App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWin85App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIN85_H__BF07BEC7_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
