#if !defined(AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
#define AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_

#include "AboutDlg.h"	// Added by ClassView
#include "InfoDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

class CMonitorDlg : public CDialog
{
// Construction
public:
	void ClearTable();
	CMonitorDlg(CWnd* pParent = NULL);   // standard constructor
	
	int* m_pIRQPenting;
	BYTE m_ports[256];
	BYTE m_access[256];
	
	BOOL m_update;

// Dialog Data
	//{{AFX_DATA(CMonitorDlg)
	enum { IDD = IDD_MONITOR_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuAbout();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuClear();
	afx_msg void OnMenuInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	COLORREF TColor[4];

	void RedrawContents();
	void SaveConfiguration();
	void LoadConfiguration();
	CString Byte2Hex(BYTE i);

	CString m_AppFileName;
	CString m_ExecutablePath;
	CMenu* pMenu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
