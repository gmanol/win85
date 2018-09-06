#if !defined(AFX_SADDRDLG_H__3C376CB5_B63A_11D3_8906_C9B7DDF45A0F__INCLUDED_)
#define AFX_SADDRDLG_H__3C376CB5_B63A_11D3_8906_C9B7DDF45A0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SAddrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSAddrDlg dialog

class CSAddrDlg : public CDialog
{
// Construction
public:
	CSAddrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSAddrDlg)
	enum { IDD = IDD_SETADDR_DIALOG };
	BYTE	m_edit_cs;
	BYTE	m_edit_data;
	BYTE	m_edit_instr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAddrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSAddrDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SADDRDLG_H__3C376CB5_B63A_11D3_8906_C9B7DDF45A0F__INCLUDED_)
