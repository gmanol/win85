#if !defined(AFX_STACKVIEW_H__72F4E6A2_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
#define AFX_STACKVIEW_H__72F4E6A2_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StackView.h : header file
//
#include "Win85Doc.h"

/////////////////////////////////////////////////////////////////////////////
// CStackView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "InputDlg.h"	// Added by ClassView

class CStackView : public CFormView
{
protected:
	CStackView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStackView)

// Form Data
public:
	//{{AFX_DATA(CStackView)
	enum { IDD = IDD_FORMVIEW_STACK };
	CScrollBar	m_ScrollBar;
	//}}AFX_DATA

// Attributes
public:
	CWin85Doc* GetDocument();

// Operations
public:
	CWin85Doc* pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStackView)
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
	virtual ~CStackView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStackView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyUp();
	afx_msg void OnKeyDown();
	afx_msg void OnKeyLeft();
	afx_msg void OnKeyRight();
	afx_msg void OnKeyPgup();
	afx_msg void OnKeyPgdown();
	afx_msg void OnKeyCtrlPgup();
	afx_msg void OnKeyCtrlPgdown();
	afx_msg void OnKeyCtrlHome();
	afx_msg void OnKeyCtrlEnd();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKey0();
	afx_msg void OnKey1();
	afx_msg void OnKey2();
	afx_msg void OnKey3();
	afx_msg void OnKey4();
	afx_msg void OnKey5();
	afx_msg void OnKey6();
	afx_msg void OnKey7();
	afx_msg void OnKey8();
	afx_msg void OnKey9();
	afx_msg void OnKeyA();
	afx_msg void OnKeyB();
	afx_msg void OnKeyC();
	afx_msg void OnKeyD();
	afx_msg void OnKeyE();
	afx_msg void OnKeyF();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyCtrlDown();
	afx_msg void OnKeyCtrlUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnterValue(CString str);
	void RedrawStack();

	int	STACKLINES;

	WORD StackBar;
	WORD StackOffset;

	COLORREF BarColor;
	COLORREF BarTextColor;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STACKVIEW_H__72F4E6A2_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
