// Monitor.h : main header file for the MONITOR DLL
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
#include "MonitorDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CMonitorApp
// See Monitor.cpp for the implementation of this class
//

class CMonitorApp : public CWinApp
{
public:
	CMonitorDlg my_dlg;
	CMonitorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMonitorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICE_H__FD85C302_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
