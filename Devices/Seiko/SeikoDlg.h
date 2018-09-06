#if !defined(AFX_SEIKODLG_H__124799DE_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_)
#define AFX_SEIKODLG_H__124799DE_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_

#include "SeikoEmul.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SeikoDlg.h : header file
//
#include "AboutDlg.h"
#include "SAddrDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSeikoDlg dialog

class CSeikoDlg : public CDialog
{
// Construction
public:
	void ExternalConfig();

	CSeikoEmul Seiko;
	CSeikoDlg(CWnd* pParent = NULL);   // standard constructor
	CMenu* pMenu;

// Dialog Data
	//{{AFX_DATA(CSeikoDlg)
	enum { IDD = IDD_SEIKO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeikoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeikoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuDoubleSize();
	afx_msg void OnMenuInvertcolors();
	afx_msg void OnMenuAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetIOAddress();
	CString sz_AppFileName;
	CString ExecutablePath;
	void LoadConfiguration();
	void SaveConfiguration();
	BOOL InvertColors;
	void ResizeDialog();
	int SizeX;
	int SizeY;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEIKODLG_H__124799DE_B580_11D3_8906_9D19ABDDDF0C__INCLUDED_)
