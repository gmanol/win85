// FlexibleSplitter.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "FlexibleSplitter.h"
#include "guidef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlexibleSplitter

CFlexibleSplitter::CFlexibleSplitter()
{

	m_cxSplitter = m_cySplitter = 4;  //3 + 2 + 2;
	m_cxBorderShare = m_cyBorderShare = 0;
	m_cxSplitterGap = m_cySplitterGap = 4;   //3 + 2 + 2;
	m_cxBorder = m_cyBorder = 2;

/*
	int m_cxSplitter, m_cySplitter;         // size of splitter bar
	int m_cxBorderShare, m_cyBorderShare;   // space on either side of splitter
	int m_cxSplitterGap, m_cySplitterGap;   // amount of space between panes
	int m_cxBorder, m_cyBorder;             // borders in client area
*/
}

CFlexibleSplitter::~CFlexibleSplitter()
{
}


BEGIN_MESSAGE_MAP(CFlexibleSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CFlexibleSplitter)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFlexibleSplitter message handlers


void CFlexibleSplitter::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CSplitterWnd::OnLButtonUp(nFlags, point);

	AdjustSplitters();
}

void CFlexibleSplitter::AdjustSplitters()
{
	int	h,t,a,i;

	for (i=0;i<GetRowCount();i++)
	{
		GetRowInfo(i,h,t);
		a=h/lc;
		nLines[i]=(BYTE) a;
		h=a*lc+yc+yf;

		SetRowInfo(i,h,t);
	}

	RecalcLayout();
}


