// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

void CInfoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
		// TODO: Add your message handler code here

	CFont myfont;
	myfont.CreateFont(14,0,0,0,300,FALSE,FALSE,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_SWISS,
		"MS Sans Serif");


	CFont* pOldFont=dc.SelectObject(&myfont);


	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(GetSysColor(COLOR_BTNFACE));

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(25,15,"Unused Port");
	dc.TextOut(25,35,"Input Port");
	dc.TextOut(25,55,"Output Port");
	dc.TextOut(25,75,"Input/Output Port");

	CBrush mybrush;mybrush.CreateSolidBrush(RGB(0,0,0));
	CBrush* pOldBrush=dc.SelectObject(&mybrush);

#define radius 8

	dc.Ellipse(8,8+10,8+radius,8+10+radius);

	CBrush mybrush2;
	mybrush2.CreateSolidBrush(RGB(0,0,255));dc.SelectObject(&mybrush2);
	dc.Ellipse(8,8+30,8+radius,8+30+radius);

	CBrush mybrush3;
	mybrush3.CreateSolidBrush(RGB(255,0,0));dc.SelectObject(&mybrush3);
	dc.Ellipse(8,8+50,8+radius,8+50+radius);

	CBrush mybrush4;
	mybrush4.CreateSolidBrush(RGB(255,255,255));dc.SelectObject(&mybrush4);
	dc.Ellipse(8,8+70,8+radius,8+70+radius);

	dc.SelectObject(pOldBrush);
	dc.SelectObject(pOldFont);

	// Do not call CDialog::OnPaint() for painting messages
}
