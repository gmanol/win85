#if !defined(AFX_SPEEDDLG_H__283E4A7B_FF6F_11D3_9FBC_F59D60AD4A16__INCLUDED_)
#define AFX_SPEEDDLG_H__283E4A7B_FF6F_11D3_9FBC_F59D60AD4A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpeedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg dialog

class CSpeedDlg : public CDialog
{
// Construction
public:
	BOOL m_Turbo;
	int m_RunSpeed;
	CSpeedDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeedDlg)
	enum { IDD = IDD_SPEED_DLG };
	CButton	m_Turbo_Button;
	CSliderCtrl	m_slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpeedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTurboCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEEDDLG_H__283E4A7B_FF6F_11D3_9FBC_F59D60AD4A16__INCLUDED_)
