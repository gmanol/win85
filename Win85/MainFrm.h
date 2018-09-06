// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__BF07BECB_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
#define AFX_MAINFRM_H__BF07BECB_4202_11D3_8906_EB9C49D44C00__INCLUDED_

#include "DevicesDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar 	m_runToolBar;
	CToolBar	m_breakpointsToolBar;
	CToolBar	m_hardwareToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewToolbarRun();
	afx_msg void OnUpdateViewToolbarRun(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarBreakpoints();
	afx_msg void OnUpdateViewToolbarBreakpoints(CCmdUI* pCmdUI);
	afx_msg void OnViewToolbarsDevices();
	afx_msg void OnUpdateViewToolbarsDevices(CCmdUI* pCmdUI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnViewToolbarsHardware();
	afx_msg void OnUpdateViewToolbarsHardware(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDevicesDlg m_DevicesDlg;
	void DockControlBarLeftOf(CToolBar* Bar, CToolBar* LeftOf);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__BF07BECB_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
