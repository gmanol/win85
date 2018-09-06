#if !defined(AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
#define AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_

#include "AboutDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

class CDeviceDlg : public CDialog
{
// Construction
public:
	CDeviceDlg(CWnd* pParent = NULL);   // standard constructor
	int* m_pIRQPenting;

// Dialog Data
	//{{AFX_DATA(CDeviceDlg)
	enum { IDD = IDD_DEVICE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMenuAbout();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SaveConfiguration();
	void LoadConfiguration();
	CString m_AppFileName;
	CString m_ExecutablePath;
	CMenu* pMenu;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__FD85C309_7F50_11D4_9FBD_8FEF4995E403__INCLUDED_)
