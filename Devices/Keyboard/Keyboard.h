// Keyboard.h : main header file for the KEYBOARD DLL
//

#if !defined(AFX_DEVICE_H__A49D2C46_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
#define AFX_DEVICE_H__A49D2C46_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "KeyboardDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CKeyboardApp
// See Keyboard.cpp for the implementation of this class
//

class CKeyboardApp : public CWinApp
{
public:
	CKeyboardDlg my_dlg;
	CKeyboardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CKeyboardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICE_H__A49D2C46_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
