// SeikoDll.h : main header file for the SEIKODLL DLL
//

#if !defined(AFX_SEIKODLL_H__124799D7_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_)
#define AFX_SEIKODLL_H__124799D7_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SeikoDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CSeikoDllApp
// See SeikoDll.cpp for the implementation of this class
//

class CSeikoDllApp : public CWinApp
{
public:
	CSeikoDlg my_dlg;
	CSeikoDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeikoDllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSeikoDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void DisplayAppName();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEIKODLL_H__124799D7_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_)
