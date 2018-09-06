// BASICIO.h : main header file for the BASICIO DLL
//

#if !defined(AFX_BASICIO_H__DCCB1C12_3D55_11D4_9FBD_B735594674E0__INCLUDED_)
#define AFX_BASICIO_H__DCCB1C12_3D55_11D4_9FBD_B735594674E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "BASICIOdlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CBASICIOApp
// See BASICIO.cpp for the implementation of this class
//

class CBASICIOApp : public CWinApp
{
public:
	CBASICIOdlg my_dlg;
	CBASICIOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBASICIOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CBASICIOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICIO_H__DCCB1C12_3D55_11D4_9FBD_B735594674E0__INCLUDED_)
