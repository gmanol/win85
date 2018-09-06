// Win85Doc.h : interface of the CWin85Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIN85DOC_H__BF07BECF_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
#define AFX_WIN85DOC_H__BF07BECF_4202_11D3_8906_EB9C49D44C00__INCLUDED_

#include "Machine.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiDef.h"
#include "BreakPointsDlg.h"	// Added by ClassView
#include "SpeedDlg.h"	// Added by ClassView
#include "WaitDlg.h"	// Added by ClassView


class CWin85Doc : public CDocument
{
protected: // create from serialization only
	CWin85Doc();
	DECLARE_DYNCREATE(CWin85Doc)

// Attributes
public:

	CMachine i8085;

	LONG BreakPointsHits[0x10000];
	BYTE BreakPoints[0x10000];


	COLORREF m_BgColor;
	COLORREF m_TextColor;
	COLORREF m_TextLightColor;
	COLORREF m_ROMTextColor;

	COLORREF m_BarColor;
	COLORREF m_BarTextColor;
	COLORREF m_BarColorDisable;
	COLORREF m_BarTextColorDisable;

	COLORREF m_BreakPointColor;
	COLORREF m_BreakPointTextColor;
	COLORREF m_BreakPointDisableColor;
	COLORREF m_BreakPointDisableTextColor;

	BOOL m_Relocate_Bar;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWin85Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	WORD CurrentCpuOffset;
	BOOL m_Running;
	int m_rtn;
	BOOL m_trace;
	BOOL m_RunState;

	void RefreshBreakpointsList();
	virtual ~CWin85Doc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWin85Doc)
	afx_msg void OnRunRun();
	afx_msg void OnRunTraceinto();
	afx_msg void OnViewBreakpointsdialog();
	afx_msg void OnUpdateViewBreakpointsdialog(CCmdUI* pCmdUI);
	afx_msg void OnOptionsEmulationspeed();
	afx_msg void OnUpdateOptionsEmulationspeed(CCmdUI* pCmdUI);
	afx_msg void OnHardwareCopybinarytolpt();
	afx_msg void OnRunProgramreset();
	afx_msg void OnRunAnimate();
	afx_msg void OnRunGotocursor();
	afx_msg void OnUpdateRunRun(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSpeedDlg m_SpeedDlg;

	CBreakPointsDlg m_BreakPointsDlg;

	static UINT RunThread(LPVOID pParam);
	CWinThread*	p_RunThread;
	BOOL m_RunTo;
	WORD m_StopAddress;
	BOOL m_Hold;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIN85DOC_H__BF07BECF_4202_11D3_8906_EB9C49D44C00__INCLUDED_)
