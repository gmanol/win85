#if !defined(AFX_REGISTERSVIEW_H__72F4E6A3_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
#define AFX_REGISTERSVIEW_H__72F4E6A3_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegistersView.h : header file
//
#include "Win85Doc.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistersView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRegistersView : public CFormView
{
protected:
	CRegistersView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRegistersView)

// Form Data
public:
	//{{AFX_DATA(CRegistersView)
	enum { IDD = IDD_FORMVIEW_REGISTERS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CWin85Doc* GetDocument();

// Operations
public:

	CWin85Doc* pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistersView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRegistersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRegistersView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_SClocks;

	DWORD m_OldClocks;	

	void RedrawRegisters();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERSVIEW_H__72F4E6A3_4ADC_11D4_9FBD_9FE5E347129E__INCLUDED_)
