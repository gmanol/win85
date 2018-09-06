#if !defined(AFX_BREAKPOINTSDLG_H__1DAB7340_D9C0_11D3_9FBC_BA934C070A63__INCLUDED_)
#define AFX_BREAKPOINTSDLG_H__1DAB7340_D9C0_11D3_9FBC_BA934C070A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BreakPointsDlg.h : header file
//
#include "BreakPointsCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CBreakPointsDlg dialog

class CBreakPointsDlg : public CDialog
{
// Construction
public:
	CBreakPointsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBreakPointsDlg)
	enum { IDD = IDD_BREAKPOINTS_DLG };
	CBreakPointsCtrl	m_BreakPointsCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBreakPointsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBreakPointsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BREAKPOINTSDLG_H__1DAB7340_D9C0_11D3_9FBC_BA934C070A63__INCLUDED_)
