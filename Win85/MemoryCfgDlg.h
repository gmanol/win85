#if !defined(AFX_MEMORYCFGDLG_H__17C97940_E6C2_11D3_9FBC_989F586FA505__INCLUDED_)
#define AFX_MEMORYCFGDLG_H__17C97940_E6C2_11D3_9FBC_989F586FA505__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoryCfgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemoryCfgDlg dialog

class CMemoryCfgDlg : public CDialog
{
// Construction
public:
	CMemoryCfgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMemoryCfgDlg)
	enum { IDD = IDD_MEMORY_DLG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryCfgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoryCfgDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYCFGDLG_H__17C97940_E6C2_11D3_9FBC_989F586FA505__INCLUDED_)
