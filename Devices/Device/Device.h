// Device.h : main header file for the DEVICE DLL
//

#if !defined(AFX_DEVICE_H__FD85C302_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
#define AFX_DEVICE_H__FD85C302_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "DeviceDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CDeviceApp
// See Device.cpp for the implementation of this class
//

class CDeviceApp : public CWinApp
{
public:
	CDeviceDlg my_dlg;
	CDeviceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDeviceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICE_H__FD85C302_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
