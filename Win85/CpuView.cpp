// CpuView.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "CpuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCpuView

IMPLEMENT_DYNCREATE(CCpuView, CFormView)

CCpuView::CCpuView()
	: CFormView(CCpuView::IDD)
{
	//{{AFX_DATA_INIT(CCpuView)
	//}}AFX_DATA_INIT
}

CCpuView::~CCpuView()
{
}

CWin85Doc* CCpuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWin85Doc)));
	return (CWin85Doc*)m_pDocument;
}

void CCpuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCpuView)
	DDX_Control(pDX, IDC_CPU_SCROLLBAR, m_ScrollBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCpuView, CFormView)
	//{{AFX_MSG_MAP(CCpuView)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_KEY_UP, OnKeyUp)
	ON_COMMAND(ID_KEY_DOWN, OnKeyDown)
	ON_COMMAND(ID_KEY_PGDOWN, OnKeyPgdown)
	ON_COMMAND(ID_KEY_PGUP, OnKeyPgup)
	ON_COMMAND(ID_KEY_CTRL_PGUP, OnKeyCtrlPgup)
	ON_COMMAND(ID_KEY_CTRL_PGDOWN, OnKeyCtrlPgdown)
	ON_COMMAND(ID_KEY_CTRL_END, OnKeyCtrlEnd)
	ON_COMMAND(ID_KEY_CTRL_HOME, OnKeyCtrlHome)
	ON_COMMAND(ID_KEY_A, OnKeyA)
	ON_COMMAND(ID_KEY_C, OnKeyC)
	ON_COMMAND(ID_KEY_D, OnKeyD)
	ON_COMMAND(ID_KEY_E, OnKeyE)
	ON_COMMAND(ID_KEY_H, OnKeyH)
	ON_COMMAND(ID_KEY_I, OnKeyI)
	ON_COMMAND(ID_KEY_J, OnKeyJ)
	ON_COMMAND(ID_KEY_L, OnKeyL)
	ON_COMMAND(ID_KEY_M, OnKeyM)
	ON_COMMAND(ID_KEY_N, OnKeyN)
	ON_COMMAND(ID_KEY_O, OnKeyO)
	ON_COMMAND(ID_KEY_P, OnKeyP)
	ON_COMMAND(ID_KEY_R, OnKeyR)
	ON_COMMAND(ID_KEY_S, OnKeyS)
	ON_COMMAND(ID_KEY_X, OnKeyX)
	ON_COMMAND(ID_BREAKPOINTS_TOGGLE, OnBreakpointsToggle)
	ON_COMMAND(ID_BREAKPOINTS_DISABLE, OnBreakpointsDisable)
	ON_COMMAND(ID_BREAKPOINTS_DELETEALL, OnBreakpointsDeleteall)
	ON_COMMAND(ID_BREAKPOINTS_AT, OnBreakpointsAt)
	ON_COMMAND(ID_KEY_LEFT, OnKeyLeft)
	ON_COMMAND(ID_KEY_RIGHT, OnKeyRight)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_KEY_CTRL_DOWN, OnKeyCtrlDown)
	ON_COMMAND(ID_KEY_CTRL_UP, OnKeyCtrlUp)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCpuView diagnostics

#ifdef _DEBUG
void CCpuView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCpuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCpuView message handlers

void CCpuView::OnInitialUpdate() 
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

	CPULINES=(cy-yc)/15;

	m_ScrollBar.SetScrollRange(0,32767-(CPULINES/2-1),TRUE);

	CpuOffset=0;
	CpuBar=0;

	pDoc->m_BgColor=GetSysColor(COLOR_BTNFACE);

	BarColor=pDoc->m_BarColor;
	BarTextColor=pDoc->m_BarTextColor;
}

void CCpuView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if(!IsWindowVisible()) return;

	m_ScrollBar.MoveWindow(cx-SCROLLBAR_WIDTH,0,SCROLLBAR_WIDTH,cy,FALSE);

	CPULINES=(cy-yc)/15;

	m_ScrollBar.SetScrollRange(0,32767-(CPULINES/2-1),TRUE);

	Invalidate(FALSE);

	if ( (CpuBar > CPULINES-1) && (CPULINES > 0) ) CpuBar=CPULINES-1;

}

void CCpuView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	int i;

	if (pScrollBar==&m_ScrollBar)	{

	switch (nSBCode)
		{
		case TB_THUMBTRACK:
		m_ScrollBar.SetScrollPos(nPos);
		i=m_ScrollBar.GetScrollPos();
		CpuOffset=i<<1;
		if (i!=0) TrimCpuOffset(CpuOffset);
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

	RedrawCpu(FALSE);
	}

	
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CCpuView::RedrawCpu(bool trace)
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

	if (pDoc->m_Relocate_Bar==TRUE)
	{
		if ((pDoc->i8085.PC < CpuOffset) || (pDoc->i8085.PC > CpuOffsetEnd))
		{
		CpuOffset=pDoc->i8085.PC;
		CpuBar=0;
		}
	}

	
	BYTE opcode,b2,b3,l;
	WORD ip;
	CString x,d,PCp;

	if (trace==TRUE)
	{
	if (pDoc->i8085.PC<CpuOffset || pDoc->i8085.PC>CpuOffsetEnd) 
	{CpuOffset=pDoc->i8085.PC;CpuBar=0;}
	}
	
	ip=CpuOffset;
	
	dc.SetBkMode(OPAQUE);

	for (int t=0;t<CPULINES;t++)
	{

	opcode=pDoc->i8085.Memory.Peek(ip);
	b2=pDoc->i8085.Memory.Peek(ip+1);
	b3=pDoc->i8085.Memory.Peek(ip+2);


	if (pDoc->i8085.Memory.MemoryAccess(ip)==FALSE)
	{
		dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_ROMTextColor);
	}
	else
	{
		dc.SetBkColor(pDoc->m_BgColor);dc.SetTextColor(pDoc->m_TextColor);
	}

	if (ip==pDoc->i8085.PC) PCp="->"; else PCp="  ";

	x=pDoc->i8085.Memory.MemoryType(ip)+CWin85App::Word2Hex(ip)+PCp+CWin85App::Byte2Hex(opcode);
	d=pDoc->i8085.Disassembly(opcode,b2,b3);

	CpuBarOffsets[t]=ip;

	switch (pDoc->BreakPoints[CpuBarOffsets[t]]) 
	{
	case 1:
		dc.SetBkColor(pDoc->m_BreakPointColor);dc.SetTextColor(pDoc->m_BreakPointTextColor);
	break;
	case 2:
		dc.SetBkColor(pDoc->m_BreakPointDisableColor);dc.SetTextColor(pDoc->m_BreakPointDisableTextColor);
	break;
	}

	if (ip==pDoc->i8085.PC && trace==TRUE) 
	{
		dc.SetBkColor(BarColor);dc.SetTextColor(BarTextColor);
		CpuBar=t;						// move cpu bar to new position
	}

	if (CpuBar==t && trace==FALSE)		// paint cpu bar
	{
		dc.SetBkColor(BarColor);dc.SetTextColor(BarTextColor);
	}


	l=pDoc->i8085.OpcodeLength[opcode];

	switch (l)
	{
	case 1:
	dc.TextOut(xc,yc+lc*t,x+"          "+d);
	break;
	case 2:
	dc.TextOut(xc,yc+lc*t,x+" "+CWin85App::Byte2Hex(b2)+"       "+d);
	break;
	case 3:
	dc.TextOut(xc,yc+lc*t,x+" "+CWin85App::Byte2Hex(b2)+" "+CWin85App::Byte2Hex(b3)+"    "+d);
	break;
	}

	ip=ip+l;
	}

	dc.SetBkColor(pDoc->m_BgColor);
	dc.TextOut(xc,yc+lc*CPULINES,"                                                      ");

	CpuOffsetEnd=ip-l;

	pDoc->CurrentCpuOffset=CpuBarOffsets[CpuBar];

	m_ScrollBar.SetScrollPos(CpuOffset>>1);


	dc.SelectObject(pOldFont);
	}
}

void CCpuView::TrimCpuOffset(WORD Estimate)
{
	BYTE opcode;
	WORD ip,t,st,d,newCpuOffset;

	st=40;
	ip=Estimate-st;

	if (ip<0) {ip=0;st=Estimate;}


	for (t=0;t<st;t++)
	{

	opcode=pDoc->i8085.Memory.Peek(ip);
 
	ip=ip+pDoc->i8085.OpcodeLength[opcode];

	d=Estimate-ip;
	if ((d<4) & (d>0)) newCpuOffset=ip;
	}

	CpuOffset=newCpuOffset;
}

void CCpuView::OnKeyUp() 
{
	// TODO: Add your command handler code here
	if (CpuBar==0)
	{
		TrimCpuOffset(CpuOffset);
	}
		else
	{
		CpuBar--;
	}
	
	RedrawCpu(FALSE);		
}

void CCpuView::OnKeyCtrlUp() 
{
	// TODO: Add your command handler code here

	TrimCpuOffset(CpuOffset);
	RedrawCpu(FALSE);			
}

void CCpuView::OnKeyDown() 
{
	// TODO: Add your command handler code here

	CpuBar++;
	if (CpuBar==CPULINES)
	{
		CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
		CpuBar=CPULINES-1;
	}
		RedrawCpu(FALSE);
}

void CCpuView::OnKeyCtrlDown() 
{
	// TODO: Add your command handler code here

	CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
	RedrawCpu(FALSE);
}


void CCpuView::OnKeyPgdown() 
{
	// TODO: Add your command handler code here

		int i;
		if (CpuBar!=CPULINES-1) 
		{
			CpuBar=CPULINES-1;
		}
		else
		{
			for (i=0;i<CPULINES-1;i++)
			{
			CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
			}
		}

		RedrawCpu(FALSE);	
}

void CCpuView::OnKeyPgup() 
{
	// TODO: Add your command handler code here
		int i;

		if (CpuBar!=0) 
		{
			CpuBar=0;
		}
		else
		{
		for (i=0;i<CPULINES-1;i++) TrimCpuOffset(CpuOffset);
		}
		RedrawCpu(FALSE);
	
}

void CCpuView::OnKeyCtrlPgup() 
{
	// TODO: Add your command handler code here
		CpuOffset=CpuOffset-0x1000;
		TrimCpuOffset(CpuOffset);
		CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
		RedrawCpu(FALSE);

}

void CCpuView::OnKeyCtrlPgdown() 
{
	// TODO: Add your command handler code here
		CpuOffset=CpuOffset+0x1000;
		TrimCpuOffset(CpuOffset);
		CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
		RedrawCpu(FALSE);
}

void CCpuView::OnKeyCtrlEnd() 
{
	// TODO: Add your command handler code here
		CpuBar=CPULINES-1;
		CpuOffset=0xffff;
		for (int i=0;i<CPULINES-1;i++) TrimCpuOffset(CpuOffset);
		RedrawCpu(FALSE);	
}

void CCpuView::OnKeyCtrlHome() 
{
	// TODO: Add your command handler code here
		CpuBar=0;
		CpuOffset=0;
		RedrawCpu(FALSE);	
}

void CCpuView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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
	RedrawCpu(FALSE);


	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CCpuView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	pDoc=GetDocument();

	if (lHint==42) AfxMessageBox("42");

	if (pDoc->m_trace==TRUE) 
	{
		RedrawCpu(TRUE);
	}
	else 
	{
		RedrawCpu(FALSE);
	}
}

void CCpuView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class

	RedrawCpu(FALSE);	
}

void CCpuView::OnKeyA() 
{
	// TODO: Add your command handler code here
	Assembly("a");
}

void CCpuView::OnKeyC() 
{
	// TODO: Add your command handler code here
	Assembly("c");	
}

void CCpuView::OnKeyD() 
{
	// TODO: Add your command handler code here
	Assembly("d");
}

void CCpuView::OnKeyE() 
{
	// TODO: Add your command handler code here
	Assembly("e");
}

void CCpuView::OnKeyH() 
{
	// TODO: Add your command handler code here
	Assembly("h");	
}

void CCpuView::OnKeyI() 
{
	// TODO: Add your command handler code here
	Assembly("i");
}

void CCpuView::OnKeyJ() 
{
	// TODO: Add your command handler code here
	Assembly("j");	
}

void CCpuView::OnKeyL() 
{
	// TODO: Add your command handler code here
	Assembly("l");
}

void CCpuView::OnKeyM() 
{
	// TODO: Add your command handler code here
	Assembly("m");
}

void CCpuView::OnKeyN() 
{
	// TODO: Add your command handler code here
	Assembly("n");
}

void CCpuView::OnKeyO() 
{
	// TODO: Add your command handler code here
	Assembly("o");
}

void CCpuView::OnKeyP() 
{
	// TODO: Add your command handler code here
	Assembly("p");
}

void CCpuView::OnKeyR() 
{
	// TODO: Add your command handler code here
	Assembly("r");
}

void CCpuView::OnKeyS() 
{
	// TODO: Add your command handler code here
	Assembly("s");
}

void CCpuView::OnKeyX() 
{
	// TODO: Add your command handler code here
	Assembly("x");	
}

void CCpuView::Assembly(CString str)
{
		int r;

		CAssemblyDlg dlg=new CAssemblyDlg;
		str.MakeLower();
		dlg.m_assembly_edit=str;
		
		dlg.DoModal();
		r=pDoc->i8085.Assembly(dlg.m_assembly_edit,CpuBarOffsets[CpuBar]);
		delete dlg;

		if (r==0) {
		CpuBar++;
				if (CpuBar==CPULINES)
				{
				CpuOffset=CpuOffset+pDoc->i8085.OpcodeLength[pDoc->i8085.Memory.Peek(CpuOffset)];
				CpuBar=CPULINES-1;
				}
		}

	pDoc->UpdateAllViews(NULL,0,NULL);
}


void CCpuView::OnBreakpointsToggle() 
{
	// TODO: Add your command handler code here
	BYTE b,s;
	WORD Address;

	Address=CpuBarOffsets[CpuBar];

	b=pDoc->BreakPoints[Address];

	s=1;

	switch (b)
	{
	case 0:
		s=1;
	break;

	case 1:
		s=0;
		pDoc->BreakPointsHits[Address]=0;
	break;
	}
	pDoc->BreakPoints[Address]=s;
	pDoc->RefreshBreakpointsList();	
}

void CCpuView::OnBreakpointsDisable() 
{
	// TODO: Add your command handler code here
	if (pDoc->BreakPoints[CpuBarOffsets[CpuBar]]!=0) 
	{
		pDoc->BreakPoints[CpuBarOffsets[CpuBar]]=2;
		pDoc->RefreshBreakpointsList();
	}
}

void CCpuView::OnBreakpointsDeleteall() 
{
	// TODO: Add your command handler code here
	int i;

	for (i=0;i<0x10000;i++)
	{
	pDoc->BreakPoints[i]=0;
	pDoc->BreakPointsHits[i]=0;
	}
	pDoc->RefreshBreakpointsList();
	RedrawCpu(FALSE);
}

void CCpuView::OnBreakpointsAt() 
{
	// TODO: Add your command handler code here
	DWORD r;

	CInputDlg dlg;

	dlg.m_Title="Breakpoint at...";
	dlg.DoModal();

	r=dlg.Result;

	if (dlg.Status==TRUE && r<65536)
	{
		pDoc->BreakPoints[r]=1;
		pDoc->RefreshBreakpointsList();
		RedrawCpu(FALSE);
	}
	else
	{
		Beep(500,1);
	}
	
}


void CCpuView::OnKeyLeft() 
{
	// TODO: Add your command handler code here
	CpuOffset=CpuOffset-1;
	RedrawCpu(FALSE);
}

void CCpuView::OnKeyRight() 
{
	// TODO: Add your command handler code here
	CpuOffset=CpuOffset+1;
	RedrawCpu(FALSE);
}

BOOL CCpuView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
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



void CCpuView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	Invalidate(FALSE);
	
	CFormView::OnRButtonDown(nFlags, point);
}
