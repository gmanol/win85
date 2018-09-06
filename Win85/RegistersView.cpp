// RegistersView.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "RegistersView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistersView

IMPLEMENT_DYNCREATE(CRegistersView, CFormView)

CRegistersView::CRegistersView()
	: CFormView(CRegistersView::IDD)
{
	//{{AFX_DATA_INIT(CRegistersView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CRegistersView::~CRegistersView()
{
}

CWin85Doc* CRegistersView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWin85Doc)));
	return (CWin85Doc*)m_pDocument;
}


void CRegistersView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistersView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistersView, CFormView)
	//{{AFX_MSG_MAP(CRegistersView)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistersView diagnostics

#ifdef _DEBUG
void CRegistersView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRegistersView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRegistersView message handlers

void CRegistersView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	pDoc=GetDocument();						// Get a pointer to the document

	SetScrollSizes(MM_TEXT, CSize(0,0));	// Disable forms ScrollBar

	pDoc->m_BgColor=GetSysColor(COLOR_BTNFACE);

	SetTimer(1,1000,NULL);
}

void CRegistersView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

}


void CRegistersView::RedrawRegisters()
{
	if (IsWindowVisible())
	{

	CClientDC dc(this); // device context for painting
	CString s,a;

	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(pDoc->m_BgColor);

	dc.SetTextColor(pDoc->m_TextColor);

	CFont myfont;
	myfont.CreateFont(25,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,
		"Fixedsys");

	CFont* pOldFont=dc.SelectObject(&myfont);

	dc.TextOut(xc+cc*0,yc,"A:"+CWin85App::Byte2Hex(pDoc->i8085.A)+":"+CWin85App::Byte2Bin(pDoc->i8085.A)+":"+CWin85App::Byte2Dec(pDoc->i8085.A));
	dc.TextOut(xc+cc*0,yc+lc,"F:"+CWin85App::Byte2Hex(pDoc->i8085.FLAGS)+":"+CWin85App::Byte2Bin(pDoc->i8085.FLAGS)+":"+CWin85App::Byte2Dec(pDoc->i8085.FLAGS));


	s=CWin85App::Bit2Bin(pDoc->i8085.FLAGS,S);
	if (s=="1") dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*3,"S:"+s);

	s=CWin85App::Bit2Bin(pDoc->i8085.FLAGS,Z);
	if (s=="1") dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*4,"Z:"+s);

	s=CWin85App::Bit2Bin(pDoc->i8085.FLAGS,AC);
	if (s=="1") dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*5,"A:"+s);

	s=CWin85App::Bit2Bin(pDoc->i8085.FLAGS,P);
	if (s=="1") dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*6,"P:"+s);

	s=CWin85App::Bit2Bin(pDoc->i8085.FLAGS,CY);
	if (s=="1") dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*7,"C:"+s);

	dc.SetTextColor(pDoc->m_TextColor);

	dc.TextOut(xc+cc*0,yc+lc*3,"BC:"+CWin85App::Word2Hex(pDoc->i8085.BC)+":"+CWin85App::Word2Dec(pDoc->i8085.BC));
	dc.TextOut(xc+cc*0,yc+lc*4,"DE:"+CWin85App::Word2Hex(pDoc->i8085.DE)+":"+CWin85App::Word2Dec(pDoc->i8085.DE));
	dc.TextOut(xc+cc*0,yc+lc*5,"HL:"+CWin85App::Word2Hex(pDoc->i8085.HL)+":"+CWin85App::Word2Dec(pDoc->i8085.HL));
	dc.TextOut(xc+cc*0,yc+lc*6,"SP:"+CWin85App::Word2Hex(pDoc->i8085.SP)+":"+CWin85App::Word2Dec(pDoc->i8085.SP));
	dc.TextOut(xc+cc*0,yc+lc*7,"PC:"+CWin85App::Word2Hex(pDoc->i8085.PC)+":"+CWin85App::Word2Dec(pDoc->i8085.PC));
	
	if (CWin85App::gIRQMap[0]>0) dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*0,yc+lc*9,"TRAP");
	if (CWin85App::gIRQMap[1]>0) dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*5,yc+lc*9,"R7");
	if (CWin85App::gIRQMap[2]>0) dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*8,yc+lc*9,"R6");
	if (CWin85App::gIRQMap[3]>0) dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*11,yc+lc*9,"R5");
	if (CWin85App::gIRQMap[4]>0) dc.SetTextColor(pDoc->m_TextLightColor); else dc.SetTextColor(pDoc->m_TextColor);
	dc.TextOut(xc+cc*14,yc+lc*9,"INT");

	dc.SetTextColor(pDoc->m_TextColor);

	if (CWin85App::gIRQMap[4]!=0)
	{
		switch (CWin85App::gIRQMap[5])
		{
		case (0xc7):
		s=" rst 0   ";
		break;
		case (0xcf):
		s=" rst 1   ";
		break;
		case (0xd7):
		s=" rst 2   ";
		break;
		case (0xdf):
		s=" rst 3   ";
		break;
		case (0xe7):
		s=" rst 4   ";
		break;
		case (0xef):
		s=" rst 5   ";
		break;
		case (0xf7):
		s=" rst 6   ";
		break;
		case (0xff):
		s=" rst 7   ";
		break;
		case (0xcd):
		s="call "+CWin85App::Word2Hex((WORD) CWin85App::gIRQMap[6])+"  ";
		break;

		default:
		s=" (no irq)  ";
		break;
		}
	}
	else s=" (no irq)  ";


	dc.TextOut(xc+cc*0,yc+lc*10,"INT Bus:"+s);


	if (pDoc->i8085.Irq_Enable==TRUE) s="EI"; else s="DI";
	a="M7:"+CWin85App::Bit2Bin(pDoc->i8085.Irq_Mask,4);
	a=a+" M6:"+CWin85App::Bit2Bin(pDoc->i8085.Irq_Mask,2);
	a=a+" M5:"+CWin85App::Bit2Bin(pDoc->i8085.Irq_Mask,1);

	dc.TextOut(xc+cc*0,yc+lc*11,a+" "+s);

//	dc.TextOut(xc+cc*0,yc+lc*13,"SID:0 SOD:0 HLD:0");

	dc.TextOut(xc+cc*0,yc+lc*13,"Clock: "+m_SClocks+" Mhz"+"     ");
	dc.TextOut(xc+cc*0,yc+lc*14,"Ticks: "+CWin85App::DWord2Dec(pDoc->i8085.clocks));

	dc.MoveTo(cc*0,yc+lc*2+lc/2);dc.LineTo(cc*18,yc+lc*2+lc/2);
	dc.MoveTo(cc*0,yc+lc*8+lc/2);dc.LineTo(cc*18,yc+lc*8+lc/2);
	dc.MoveTo(cc*0,yc+lc*12+lc/2);dc.LineTo(cc*18,yc+lc*12+lc/2);

	dc.SelectObject(pOldFont);

	}
}


void CRegistersView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate(FALSE);
}

void CRegistersView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	RedrawRegisters();	
	
}

void CRegistersView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	m_OldClocks=pDoc->i8085.clocks-m_OldClocks;

	CClientDC dc(this); // device context for painting

	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(pDoc->m_BgColor);

	dc.SetTextColor(pDoc->m_TextColor);

	CFont myfont;
	myfont.CreateFont(25,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,FIXED_PITCH|FF_SWISS,
		"Fixedsys");

	CFont* pOldFont=dc.SelectObject(&myfont);
	
	double source = (double) m_OldClocks;
	source=source/1000000;

	m_SClocks.Format("%.4f",source);
	m_SClocks=m_SClocks.Left(6);

	dc.TextOut(xc+cc*0,yc+lc*13,"Clock: "+m_SClocks+" Mhz"+"     ");
	dc.TextOut(xc+cc*0,yc+lc*14,"Ticks: "+CWin85App::DWord2Dec(pDoc->i8085.clocks));
	
	dc.SelectObject(pOldFont);
	
	m_OldClocks=pDoc->i8085.clocks;

	CFormView::OnTimer(nIDEvent);
}


void CRegistersView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	Invalidate(FALSE);

	CFormView::OnRButtonDown(nFlags, point);
}


