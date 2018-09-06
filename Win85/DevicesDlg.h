#if !defined(AFX_DEVICESDLG_H__041381C0_C881_11D3_9FBB_D31CBEE7B018__INCLUDED_)
#define AFX_DEVICESDLG_H__041381C0_C881_11D3_9FBB_D31CBEE7B018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevicesDlg.h : header file
//
#include "MyListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDevicesDlg dialog

class CDevicesDlg : public CDialog
{
// Construction
public:
	CDevicesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDevicesDlg)
	enum { IDD = IDD_CONNECT_DIALOG };
	CMyListCtrl	m_device_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevicesDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevicesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICESDLG_H__041381C0_C881_11D3_9FBB_D31CBEE7B018__INCLUDED_)
