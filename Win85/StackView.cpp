// StackView.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "StackView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStackView

IMPLEMENT_DYNCREATE(CStackView, CFormView)

CStackView::CStackView()
	: CFormView(CStackView::IDD)
{
	//{{AFX_DATA_INIT(CStackView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStackView::~CStackView()
{
}

CWin85Doc* CStackView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWin85Doc)));
	return (CWin85Doc*)m_pDocument;
}


void CStackView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStackView)
	DDX_Control(pDX, IDC_STACK_SCROLLBAR, m_ScrollBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStackView, CFormView)
	//{{AFX_MSG_MAP(CStackView)
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
// CStackView diagnostics

#ifdef _DEBUG
void CStackView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStackView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStackView message handlers

void CStackView::OnInitialUpdate() 
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

	STACKLINES=(cy-yc)/15;

	// Customize ScrollBar

	m_ScrollBar.SetScrollRange(0,32767-(STACKLINES-1),TRUE);

	StackOffset=~0xfffe;
	StackBar=0;

	pDoc->m_BgColor=GetSysColor(COLOR_BTNFACE);

	BarColor=pDoc->m_BarColorDisable;
	BarTextColor=pDoc->m_BarTextColorDisable;
}

void CStackView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if(!IsWindowVisible()) return;

	STACKLINES=(cy-yc)/15;


  	m_ScrollBar.MoveWindow(cx-SCROLLBAR_WIDTH,0,SCROLLBAR_WIDTH,cy,FALSE);

	m_ScrollBar.SetScrollRange(0,32767-(STACKLINES-1),TRUE);
	
	Invalidate(FALSE);

	
	if ((StackBar>(STACKLINES-1)) && (STACKLINES > 0))
	{
		StackBar=STACKLINES-1;
	}

}


void CStackView::RedrawStack()
{
	if (IsWindowVisible())
	{

	CClientDC dc(this); // device context for painting

	CFont myfont;
	myfont.CreateFont(25,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,
		"Fixedsys");

	CFont* pOldFont=dc.SelectObject(&myfont);

	int i;
	WORD offset;
		
	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);


	for (i=0;i<STACKLINES;i++)
	{
		dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);
		offset=0xffff-(StackOffset+i*2);

	if (i==StackBar) {dc.SetBkColor(BarColor);dc.SetTextColor(BarTextColor);}
	if (offset==(pDoc->i8085.SP)) {dc.SetTextColor(pDoc->m_TextLightColor);}	

	dc.TextOut(xc,yc+lc*i,pDoc->i8085.ReadStackBlock(offset));

	if (i==StackBar) {dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);}
	}


	dc.SetBkColor(pDoc->m_BgColor);
	dc.TextOut(xc,yc+lc*STACKLINES,"               ");

	m_ScrollBar.SetScrollPos(StackOffset/2,TRUE);

	dc.SelectObject(pOldFont);
	}
}

void CStackView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

	RedrawStack();


	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CStackView::OnKeyUp() 
{
	// TODO: Add your command handler code here

	if (StackBar==0)
	{
		StackOffset=StackOffset-2;
	}
	else
	{
		StackBar--;
	}

	RedrawStack();

}

void CStackView::OnKeyCtrlUp() 
{
	// TODO: Add your command handler code here

	StackOffset=StackOffset-2;
	RedrawStack();
}

void CStackView::OnKeyDown() 
{
	// TODO: Add your command handler code here

	if (StackBar==STACKLINES-1)
	{
		StackOffset=StackOffset+2;
	}
	else
	{
		StackBar++;
	}

	RedrawStack();
}

void CStackView::OnKeyCtrlDown() 
{
	// TODO: Add your command handler code here
	
	StackOffset=StackOffset+2;
	RedrawStack();
}


void CStackView::OnKeyLeft() 
{
	// TODO: Add your command handler code here

	StackOffset=StackOffset-1;
	RedrawStack();

}

void CStackView::OnKeyRight() 
{
	// TODO: Add your command handler code here

	StackOffset=StackOffset+1;
	RedrawStack();

}

void CStackView::OnKeyPgup() 
{
	// TODO: Add your command handler code here

	if (StackBar!=0)
	{
		StackBar=0;
	}
	else
	{
		StackOffset=StackOffset-2*STACKLINES;
	}

	RedrawStack();
}

void CStackView::OnKeyPgdown() 
{
	// TODO: Add your command handler code here

	if (StackBar!=(STACKLINES-1))
	{
		StackBar=STACKLINES-1;
	}
	else
	{
		StackOffset=StackOffset+2*STACKLINES;
	}

	RedrawStack();
}

void CStackView::OnKeyCtrlPgup() 
{
	// TODO: Add your command handler code here

	StackOffset=StackOffset-0x1000;
	RedrawStack();
}

void CStackView::OnKeyCtrlPgdown() 
{
	// TODO: Add your command handler code here

	StackOffset=StackOffset+0x1000;
	RedrawStack();
}

void CStackView::OnKeyCtrlHome() 
{
	// TODO: Add your command handler code here

	StackBar=0;
	StackOffset=(StackOffset & 1);
	RedrawStack();
}

void CStackView::OnKeyCtrlEnd() 
{
	// TODO: Add your command handler code here

	StackBar=STACKLINES-1;
	StackOffset=0x10000-2*STACKLINES+(StackOffset & 1);
	RedrawStack();

}

void CStackView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	int i;
	
	if (pScrollBar==&m_ScrollBar)	{

	switch (nSBCode)
		{

		case TB_THUMBTRACK:
		m_ScrollBar.SetScrollPos(nPos);
		i=m_ScrollBar.GetScrollPos();
		StackOffset=(i<<1)+(StackOffset & 1);
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

	RedrawStack();
	}

	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CStackView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	pDoc=GetDocument();

	if (pDoc->m_trace==TRUE) 
	{
		if (pDoc->m_rtn==1)	StackOffset=~pDoc->i8085.SP;
	}

	Invalidate(FALSE);
}

void CStackView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	RedrawStack();	
}

void CStackView::OnKey0() 
{
	// TODO: Add your command handler code here

	EnterValue("0");
}


void CStackView::OnKey1() 
{
	// TODO: Add your command handler code here
	EnterValue("1");	
}

void CStackView::OnKey2() 
{
	// TODO: Add your command handler code here
	EnterValue("2");	
}

void CStackView::OnKey3() 
{
	// TODO: Add your command handler code here
	EnterValue("3");	
}

void CStackView::OnKey4() 
{
	// TODO: Add your command handler code here
	EnterValue("4");	
}

void CStackView::OnKey5() 
{
	// TODO: Add your command handler code here
	EnterValue("5");	
}

void CStackView::OnKey6() 
{
	// TODO: Add your command handler code here
	EnterValue("6");	
}

void CStackView::OnKey7() 
{
	// TODO: Add your command handler code here
	EnterValue("7");	
}

void CStackView::OnKey8() 
{
	// TODO: Add your command handler code here
	EnterValue("8");	
}

void CStackView::OnKey9() 
{
	// TODO: Add your command handler code here
	EnterValue("9");	
}

void CStackView::OnKeyA() 
{
	// TODO: Add your command handler code here
	EnterValue("A");	
}

void CStackView::OnKeyB() 
{
	// TODO: Add your command handler code here
	EnterValue("B");	
}

void CStackView::OnKeyC() 
{
	// TODO: Add your command handler code here
	EnterValue("C");	
}

void CStackView::OnKeyD() 
{
	// TODO: Add your command handler code here
	EnterValue("D");	
}

void CStackView::OnKeyE() 
{
	// TODO: Add your command handler code here
	EnterValue("E");	
}

void CStackView::OnKeyF() 
{
	// TODO: Add your command handler code here
	EnterValue("F");	
}


void CStackView::EnterValue(CString str)
{
	DWORD r;

	CInputDlg dlg=new CInputDlg;

	str.MakeLower();

	dlg.m_input=str;
	dlg.DoModal();

	r=dlg.Result;

	if (dlg.Status==TRUE && r<65536)
	{

		pDoc->i8085.Memory.ForcePoke(0xffff-StackOffset-StackBar*2,(BYTE) (r & 0xff));
		pDoc->i8085.Memory.ForcePoke(0xffff-StackOffset-StackBar*2+1,(BYTE) (r >> 8));

		pDoc->UpdateAllViews(NULL,0,NULL);
	}
	else
	{
		Beep(500,1);
	}
}

void CStackView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	Invalidate(FALSE);

	CFormView::OnRButtonDown(nFlags, point);
}

BOOL CStackView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
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


