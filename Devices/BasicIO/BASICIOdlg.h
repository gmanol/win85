#if !defined(AFX_BASICIODLG_H__2746F8C0_3D8E_11D4_9FBD_CA6A9DDC776E__INCLUDED_)
#define AFX_BASICIODLG_H__2746F8C0_3D8E_11D4_9FBD_CA6A9DDC776E__INCLUDED_

#include "AboutDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BASICIOdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBASICIOdlg dialog

class CBASICIOdlg : public CDialog
{
// Construction
public:
	CBASICIOdlg(CWnd* pParent = NULL);   // standard constructor
	int* m_pIRQPenting;

// Dialog Data
	//{{AFX_DATA(CBASICIOdlg)
	enum { IDD = IDD_BASICIO_DLG };
	CString	m_edit_out;
	BYTE	m_edit_in;
	long	m_pulse55;
	long	m_pulse65;
	long	m_pulseINTR;
	CString	m_INTRBus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBASICIOdlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBASICIOdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnIrqButtonTrap();
	afx_msg void OnIrqButtonRst75();
	afx_msg void OnIrqButtonRst65();
	afx_msg void OnIrqButtonRst55();
	afx_msg void OnIrqButtonIntr();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString Word2Hex(WORD i);
	CString Byte2Hex(BYTE i);
	DWORD StrHex2Val(CString str);
	CMenu* pMenu;
	BYTE m_port;
	void LoadConfiguration();
	void SaveConfiguration();
	CString m_AppFileName;
	CString m_ExecutablePath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICIODLG_H__2746F8C0_3D8E_11D4_9FBD_CA6A9DDC776E__INCLUDED_)
