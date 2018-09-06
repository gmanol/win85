// MemoryView.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "MemoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoryView

IMPLEMENT_DYNCREATE(CMemoryView, CFormView)

CMemoryView::CMemoryView()
	: CFormView(CMemoryView::IDD)
{
	//{{AFX_DATA_INIT(CMemoryView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMemoryView::~CMemoryView()
{
}

CWin85Doc* CMemoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWin85Doc)));
	return (CWin85Doc*)m_pDocument;
}


void CMemoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryView)
	DDX_Control(pDX, IDC_MEMORY_SCROLLBAR, m_ScrollBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemoryView, CFormView)
	//{{AFX_MSG_MAP(CMemoryView)
	ON_WM_SIZE()
	ON_COMMAND(ID_KEY_UP, OnKeyUp)
	ON_COMMAND(ID_KEY_DOWN, OnKeyDown)
	ON_COMMAND(ID_KEY_LEFT, OnKeyLeft)
	ON_COMMAND(ID_KEY_RIGHT, OnKeyRight)
	ON_COMMAND(ID_KEY_PGUP, OnKeyPgup)
	ON_COMMAND(ID_KEY_PGDOWN, OnKeyPgdown)
	ON_COMMAND(ID_KEY_CTRL_PGUP, OnKeyCtrlPgup)
	ON_COMMAND(ID_KEY_CTRL_PGDOWN, OnKeyCtrlPgdown)
	ON_COMMAND(ID_KEY_CTRL_HOME, OnKeyCtrlHome)
	ON_COMMAND(ID_KEY_CTRL_END, OnKeyCtrlEnd)
	ON_WM_VSCROLL()
	ON_COMMAND(ID_KEY_0, OnKey0)
	ON_COMMAND(ID_KEY_1, OnKey1)
	ON_COMMAND(ID_KEY_2, OnKey2)
	ON_COMMAND(ID_KEY_3, OnKey3)
	ON_COMMAND(ID_KEY_4, OnKey4)
	ON_COMMAND(ID_KEY_5, OnKey5)
	ON_COMMAND(ID_KEY_6, OnKey6)
	ON_COMMAND(ID_KEY_7, OnKey7)
	ON_COMMAND(ID_KEY_8, OnKey8)
	ON_COMMAND(ID_KEY_9, OnKey9)
	ON_COMMAND(ID_KEY_A, OnKeyA)
	ON_COMMAND(ID_KEY_B, OnKeyB)
	ON_COMMAND(ID_KEY_C, OnKeyC)
	ON_COMMAND(ID_KEY_D, OnKeyD)
	ON_COMMAND(ID_KEY_E, OnKeyE)
	ON_COMMAND(ID_KEY_F, OnKeyF)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_KEY_CTRL_DOWN, OnKeyCtrlDown)
	ON_COMMAND(ID_KEY_CTRL_UP, OnKeyCtrlUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryView diagnostics

#ifdef _DEBUG
void CMemoryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMemoryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMemoryView message handlers

void CMemoryView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	pDoc=GetDocument();						// Get a pointer to the document

	SetScrollSizes(MM_TEXT, CSize(0,0));	// Disable forms ScrollBar


	// Draw custom ScrollBar

	RECT area;
	int cx,cy;

	GetWindowRect(&area);

	cy=area.bottom-area.top;
	cx=area.right-area.left;

	m_ScrollBar.MoveWindow(cx-SCROLLBAR_WIDTH,0,SCROLLBAR_WIDTH,cy,TRUE);

	// Customize ScrollBar

	MEMORYLINES=(cy-yc)/15;

	m_ScrollBar.SetScrollRange(0,4095-(MEMORYLINES-1),TRUE);
	
	DumpOffset=0;
	MemoryBar=0;

	pDoc->m_BgColor=GetSysColor(COLOR_BTNFACE);

	BarColor=pDoc->m_BarColorDisable;
	BarTextColor=pDoc->m_BarTextColorDisable;
}

void CMemoryView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if(!IsWindowVisible()) return;

	m_ScrollBar.MoveWindow(cx-SCROLLBAR_WIDTH,0,SCROLLBAR_WIDTH,cy,FALSE);

	MEMORYLINES=(cy-yc)/15;

	m_ScrollBar.SetScrollRange(0,4095-(MEMORYLINES-1),TRUE);
	
	Invalidate(FALSE);


	if (((MemoryBar>>4) > (MEMORYLINES-1))  && (MEMORYLINES > 0) )
	{
		MemoryBar=((MEMORYLINES-1) << 4) + (MemoryBar & 0xf);
	}
}

/*
void CMemoryView::RedrawDump()
{
	CClientDC dc(this); // device context for painting

	dc.SetBkColor(pDoc->m_BgColor);

	CFont myfont;
	myfont.CreateFont(25,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,
		"Fixedsys");

	CFont* pOldFont=dc.SelectObject(&myfont);

	WORD m;
	CString s;

	for (WORD i=0;i<MEMORYLINES;i++)
	{

	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);

	dc.TextOut(xc,yc+lc*i,pDoc->i8085.ReadMemoryBlock16(DumpOffset+(i<<4)));

	dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_ROMTextColor);

	dc.TextOut(xc,yc+lc*i,pDoc->i8085.ReadMemoryBlock16i(DumpOffset+(i<<4)));

	if ((MemoryBar >> 4)==i)
	{
		m=MemoryBar & 0x0f;
		m=m<<1;
		
	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(BarColor);dc.SetTextColor(BarTextColor);

	s=pDoc->i8085.ReadMemoryBlockSolid(DumpOffset+(i<<4));

	dc.TextOut(xc+cc*5+m*cc,yc+lc*i,s.Mid(m,2));
	m=m>>1;
	dc.TextOut(xc+cc*38+m*cc,yc+lc*i,s.Mid(35+m,1));
	}

	}

	dc.SetBkMode(OPAQUE);dc.SetBkColor(pDoc->m_BgColor);
	dc.TextOut(xc,yc+lc*MEMORYLINES,"                                                      ");

	dc.SelectObject(pOldFont);

	m_ScrollBar.SetScrollPos(DumpOffset>>4,TRUE);
} */

void CMemoryView::RedrawDump()
{
	if (IsWindowVisible())
	{

	CClientDC dc(this); // device context for painting

	dc.SetBkColor(pDoc->m_BgColor);

	CFont myfont;
	myfont.CreateFont(25,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,
		"Fixedsys");

	CFont* pOldFont=dc.SelectObject(&myfont);
	dc.SetBkMode(OPAQUE);

	WORD m;
	CString s;

	for (WORD i=0;i<MEMORYLINES;i++)
	{

	dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);

	dc.TextOut(xc,yc+lc*i,pDoc->i8085.ReadMemoryBlock(DumpOffset+(i<<4)));

	if ((MemoryBar >> 4)==i)
	{
		m=MemoryBar & 0x0f;
		m=m<<1;
		
	dc.SetBkColor(BarColor);dc.SetTextColor(BarTextColor);

	s=pDoc->i8085.ReadMemoryBlockSolid(DumpOffset+(i<<4));

	dc.TextOut(xc+cc*5+m*cc,yc+lc*i,s.Mid(m,2));
	m=m>>1;
	dc.TextOut(xc+cc*38+m*cc,yc+lc*i,s.Mid(35+m,1));
	}

	}

	dc.SetBkColor(pDoc->m_BgColor);
	dc.TextOut(xc,yc+lc*MEMORYLINES,"                                                      ");

	dc.SelectObject(pOldFont);

	m_ScrollBar.SetScrollPos(DumpOffset>>4,TRUE);

	}
}

void CMemoryView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (bActivate==TRUE)
	{
	BarColor=pDoc->m_BarColor;
	BarTextColor=pDoc->m_BarTextColor;
	}
	else
	{
	BarColor=pDoc->m_BarColorDisable;
	BarTextColor=pDoc->m_BarTextColorDisable;
	}
	RedrawDump();

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CMemoryView::OnKeyUp() 
{
	// TODO: Add your command handler code here

		if ((MemoryBar>>4)==0)
		{
			DumpOffset=DumpOffset-16;
		}
		else
		{
			MemoryBar=MemoryBar-16;
		}

		RedrawDump();
}

void CMemoryView::OnKeyCtrlUp() 
{
	// TODO: Add your command handler code here

		DumpOffset=DumpOffset-16;
		RedrawDump();
}

void CMemoryView::OnKeyDown() 
{
	// TODO: Add your command handler code here

		if ((MemoryBar>>4)==(MEMORYLINES-1))
		{
			DumpOffset=DumpOffset+16;
		}
		else
		{
			MemoryBar=MemoryBar+16;
		}

		RedrawDump();
	
}

void CMemoryView::OnKeyCtrlDown() 
{
	// TODO: Add your command handler code here

	DumpOffset=DumpOffset+16;
	RedrawDump();
}

void CMemoryView::OnKeyLeft() 
{
	// TODO: Add your command handler code here

		if (MemoryBar==0)
		{
			DumpOffset=DumpOffset-16;
			MemoryBar=15;
		}
		else
		{
			MemoryBar--;
		}

		RedrawDump();
}

void CMemoryView::OnKeyRight() 
{
	// TODO: Add your command handler code here
		if (MemoryBar==16*(MEMORYLINES-1)+15)
		{
			DumpOffset=DumpOffset+16;
			MemoryBar=16*(MEMORYLINES-1);
		}
		else
		{
			MemoryBar++;
		}

		RedrawDump();
}

void CMemoryView::OnKeyPgup() 
{
	// TODO: Add your command handler code here

		if ((MemoryBar>>4)!=0) 
		{
			MemoryBar=MemoryBar & 0xf;
		}
		else
		{	
			DumpOffset=DumpOffset-16*MEMORYLINES;
		}
		RedrawDump();

}

void CMemoryView::OnKeyPgdown() 
{
	// TODO: Add your command handler code here

		if ((MemoryBar>>4)!=(MEMORYLINES-1)) 
		{
			MemoryBar=(MemoryBar & 0xf) | 16*(MEMORYLINES-1);
		}
		else
		{	
			DumpOffset=DumpOffset+16*MEMORYLINES;
		}
		RedrawDump();	
}

void CMemoryView::OnKeyCtrlPgup() 
{
	// TODO: Add your command handler code here
	
		DumpOffset=DumpOffset-0x1000;
		RedrawDump();
}

void CMemoryView::OnKeyCtrlPgdown() 
{
	// TODO: Add your command handler code here

		DumpOffset=DumpOffset+0x1000;
		RedrawDump();
	
}

void CMemoryView::OnKeyCtrlHome() 
{
	// TODO: Add your command handler code here

		DumpOffset=0;
		MemoryBar=0;
		RedrawDump();
}

void CMemoryView::OnKeyCtrlEnd() 
{
	// TODO: Add your command handler code here

		DumpOffset=0x10000-(16*MEMORYLINES);
		MemoryBar=16*(MEMORYLINES-1);
		RedrawDump();
}

void CMemoryView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	int	i;

	if (pScrollBar==&m_ScrollBar)
	{

	switch (nSBCode)
		{

		case TB_THUMBTRACK:
		m_ScrollBar.SetScrollPos(nPos);
		i=m_ScrollBar.GetScrollPos();
		DumpOffset=i<<4;
		break;

		case SB_LINEDOWN:
		OnKeyDown();
		break;
		
		case SB_LINEUP:
		OnKeyUp();
		break;

		case SB_PAGEDOWN:
		OnKeyPgdown();
		break;

		case SB_PAGEUP:
		OnKeyPgup();
		break;
		}

	RedrawDump();
	}
	
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMemoryView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(FALSE);
}

void CMemoryView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	RedrawDump();
}

void CMemoryView::OnKey0() 
{
	// TODO: Add your command handler code here
	EnterValue("0");
	
}

void CMemoryView::OnKey1() 
{
	// TODO: Add your command handler code here
	EnterValue("1");
}

void CMemoryView::OnKey2() 
{
	// TODO: Add your command handler code here
	EnterValue("2");
}

void CMemoryView::OnKey3() 
{
	// TODO: Add your command handler code here
	EnterValue("3");
}

void CMemoryView::OnKey4() 
{
	// TODO: Add your command handler code here
	EnterValue("4");
}

void CMemoryView::OnKey5() 
{
	// TODO: Add your command handler code here
	EnterValue("5");
}

void CMemoryView::OnKey6() 
{
	// TODO: Add your command handler code here
	EnterValue("6");
}

void CMemoryView::OnKey7() 
{
	// TODO: Add your command handler code here
	EnterValue("7");
}

void CMemoryView::OnKey8() 
{
	// TODO: Add your command handler code here
	EnterValue("8");
}

void CMemoryView::OnKey9() 
{
	// TODO: Add your command handler code here
	EnterValue("9");
}

void CMemoryView::OnKeyA() 
{
	// TODO: Add your command handler code here
	EnterValue("A");
}

void CMemoryView::OnKeyB() 
{
	// TODO: Add your command handler code here
	EnterValue("B");
}

void CMemoryView::OnKeyC() 
{
	// TODO: Add your command handler code here
	EnterValue("C");
}

void CMemoryView::OnKeyD() 
{
	// TODO: Add your command handler code here
	EnterValue("D");
}

void CMemoryView::OnKeyE() 
{
	// TODO: Add your command handler code here
	EnterValue("E");
}

void CMemoryView::OnKeyF() 
{
	// TODO: Add your command handler code here
	EnterValue("F");
}

void CMemoryView::EnterValue(CString str)
{
	DWORD r;

	CInputDlg dlg=new CInputDlg;

	str.MakeLower();

	dlg.m_input=str;
	dlg.DoModal();

	r=dlg.Result;

	if (dlg.Status==TRUE && r<256)
	{
		pDoc->i8085.Memory.ForcePoke(DumpOffset+MemoryBar,(BYTE) r);
		pDoc->UpdateAllViews(NULL,0,NULL);
	}
	else
	{
		Beep(500,1);
	}
}

void CMemoryView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);

	CFormView::OnRButtonDown(nFlags, point);
}

BOOL CMemoryView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default

	if (zDelta>0)
	{
		OnKeyCtrlUp();OnKeyCtrlUp();OnKeyCtrlUp();
	}
	else
	{
		OnKeyCtrlDown();OnKeyCtrlDown();OnKeyCtrlDown();
	}
	
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}


