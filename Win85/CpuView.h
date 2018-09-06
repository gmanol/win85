#if !defined(AFX_CPUVIEW_H__72F4E6A0_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
#define AFX_CPUVIEW_H__72F4E6A0_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CpuView.h : header file
//

#include "Win85Doc.h"

/////////////////////////////////////////////////////////////////////////////
// CCpuView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "AssemblyDlg.h"	// Added by ClassView
#include "InputDlg.h"	// Added by ClassView

class CCpuView : public CFormView
{
protected:
	CCpuView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCpuView)

// Form Data
public:
	//{{AFX_DATA(CCpuView)
	enum { IDD = IDD_FORMVIEW_CPU };
	CScrollBar	m_ScrollBar;
	//}}AFX_DATA

// Attributes
public:
	
	CWin85Doc* GetDocument();

// Operations
public:
	void RedrawCpu(bool trace);

	CWin85Doc* pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCpuView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCpuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CCpuView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyUp();
	afx_msg void OnKeyDown();
	afx_msg void OnKeyPgdown();
	afx_msg void OnKeyPgup();
	afx_msg void OnKeyCtrlPgup();
	afx_msg void OnKeyCtrlPgdown();
	afx_msg void OnKeyCtrlEnd();
	afx_msg void OnKeyCtrlHome();
	afx_msg void OnKeyA();
	afx_msg void OnKeyC();
	afx_msg void OnKeyD();
	afx_msg void OnKeyE();
	afx_msg void OnKeyH();
	afx_msg void OnKeyI();
	afx_msg void OnKeyJ();
	afx_msg void OnKeyL();
	afx_msg void OnKeyM();
	afx_msg void OnKeyN();
	afx_msg void OnKeyO();
	afx_msg void OnKeyP();
	afx_msg void OnKeyR();
	afx_msg void OnKeyS();
	afx_msg void OnKeyX();
	afx_msg void OnBreakpointsToggle();
	afx_msg void OnBreakpointsDisable();
	afx_msg void OnBreakpointsDeleteall();
	afx_msg void OnBreakpointsAt();
	afx_msg void OnKeyLeft();
	afx_msg void OnKeyRight();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyCtrlDown();
	afx_msg void OnKeyCtrlUp();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Assembly(CString str);

	int	CPULINES;

	WORD CpuOffset;
	WORD CpuBarOffsets[256];		// max 256 lines
	WORD CpuOffsetEnd;
	WORD CpuBar;

	COLORREF BarColor;
	COLORREF BarTextColor;

	void TrimCpuOffset(WORD Estimate);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPUVIEW_H__72F4E6A0_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
