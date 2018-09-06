#if !defined(AFX_SOLIDSPLITTER_H__7AF9F624_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_)
#define AFX_SOLIDSPLITTER_H__7AF9F624_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SolidSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSolidSplitter window

class CSolidSplitter : public CSplitterWnd
{
// Construction
public:
	CSolidSplitter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSolidSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSolidSplitter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSolidSplitter)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLIDSPLITTER_H__7AF9F624_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_)
