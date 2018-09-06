// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__BF07BECD_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
#define AFX_CHILDFRM_H__BF07BECD_4202_11D3_8906_EB9C49D44C00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "cpuview.h"
#include "memoryview.h"
#include "registersview.h"
#include "stackview.h"
#include "FlexibleSplitter.h"	// Added by ClassView
#include "SolidSplitter.h"	// Added by ClassView

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSolidSplitter m_wndMainSplitter;
	CFlexibleSplitter m_wndLeftSplitter;
	CFlexibleSplitter m_wndRightSplitter;

	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSizing( UINT nSide, LPRECT lpRect );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOptionsSaveasdefaultlayout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BYTE	iLeft0;
	BYTE	iLeft1;

	BYTE	iRight0;
	BYTE	iRight1;

	BYTE	iYSize;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__BF07BECD_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
