// SolidSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "SolidSplitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolidSplitter

CSolidSplitter::CSolidSplitter()
{
  m_cxSplitter = m_cySplitter = 4;  //3 + 2 + 2;
  m_cxBorderShare = m_cyBorderShare = 0;
  m_cxSplitterGap = m_cySplitterGap = 4;   //3 + 2 + 2;
  m_cxBorder = m_cyBorder = 2;
}

CSolidSplitter::~CSolidSplitter()
{
}


BEGIN_MESSAGE_MAP(CSolidSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CSolidSplitter)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSolidSplitter message handlers

void CSolidSplitter::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CSplitterWnd::OnLButtonDown(nFlags, point);
}

void CSolidSplitter::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CSplitterWnd::OnLButtonUp(nFlags, point);
}

void CSolidSplitter::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CSplitterWnd::OnLButtonDblClk(nFlags, point);
}

void CSolidSplitter::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CSplitterWnd::OnMouseMove(nFlags, point);
}
