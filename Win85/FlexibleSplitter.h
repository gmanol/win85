#if !defined(AFX_FLEXIBLESPLITTER_H__7AF9F625_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_)
#define AFX_FLEXIBLESPLITTER_H__7AF9F625_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlexibleSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlexibleSplitter window

class CFlexibleSplitter : public CSplitterWnd
{
// Construction
public:
	CFlexibleSplitter();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlexibleSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	BYTE nLines[5];
	void AdjustSplitters();
	virtual ~CFlexibleSplitter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFlexibleSplitter)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLEXIBLESPLITTER_H__7AF9F625_4DDD_11D4_9FBD_E196FF27BC9E__INCLUDED_)
