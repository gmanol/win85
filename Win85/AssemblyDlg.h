#if !defined(AFX_ASSEMBLYDLG_H__0396EB4E_99BC_11D3_8906_DAE9D51A6413__INCLUDED_)
#define AFX_ASSEMBLYDLG_H__0396EB4E_99BC_11D3_8906_DAE9D51A6413__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssemblyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg dialog

class CAssemblyDlg : public CDialog
{
// Construction
public:
	CAssemblyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAssemblyDlg)
	enum { IDD = IDD_ASSEMBLY_DLG };
	CEdit	m_assembly_control;
	CString	m_assembly_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssemblyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssemblyDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSEMBLYDLG_H__0396EB4E_99BC_11D3_8906_DAE9D51A6413__INCLUDED_)
