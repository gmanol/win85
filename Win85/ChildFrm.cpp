// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "Win85.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_COMMAND(ID_OPTIONS_SAVEASDEFAULTLAYOUT, OnOptionsSaveasdefaultlayout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here

	CFile fcfg;

	char buf[300];
	CString szLongPathName;

	::GetModuleFileName(AfxGetInstanceHandle(),buf, 300);

	szLongPathName=buf;
	szLongPathName=szLongPathName.Left(szLongPathName.GetLength()-3)+"cfg";
	szLongPathName.MakeLower();


	fcfg.Open(szLongPathName,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);


	if (fcfg.GetLength()<5)
	{
		iLeft0=15;
		iLeft1=3;
		iRight0=15;
		iRight1=0;
		iYSize=24;

		fcfg.Write(&iLeft0,1);
		fcfg.Write(&iLeft1,1);
		fcfg.Write(&iRight0,1);
		fcfg.Write(&iRight1,1);
		fcfg.Write(&iYSize,1);
		fcfg.Flush();
	}
	else if (fcfg.GetLength()==5)
	{
		fcfg.Read(&iLeft0,1);
		fcfg.Read(&iLeft1,1);
		fcfg.Read(&iRight0,1);
		fcfg.Read(&iRight1,1);
		fcfg.Read(&iYSize,1);
	}

	fcfg.Close();

}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

//	cs.style &= ~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_THICKFRAME);
	
	cs.style &= ~WS_MAXIMIZEBOX;


	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect mRect;

 // get current geometry of the frame window
 GetClientRect(&mRect);

 m_wndMainSplitter.CreateStatic(this, 1, 2);

 // First main splitter pane
// m_wndMainSplitter.CreateView(0,0,RUNTIME_CLASS(CMyView),CSize((mRect.Width()-cx)/2, 0),pContext);


 m_wndLeftSplitter.CreateStatic(&m_wndMainSplitter,3,1,WS_CHILD|WS_VISIBLE|WS_BORDER,m_wndMainSplitter.IdFromRowCol(0,0));

  // First aux splitter pane
 m_wndLeftSplitter.CreateView(0,0,RUNTIME_CLASS(CCpuView),CSize(0,0),pContext);
 

 // Second aux splitter pane
 m_wndLeftSplitter.CreateView(1,0,RUNTIME_CLASS(CMemoryView),CSize(0,0),pContext);

 // Third aux splitter pane
 m_wndLeftSplitter.CreateView(2,0,RUNTIME_CLASS(CMemoryView),CSize(0,0),pContext);


   // add the second splitter pane - which is a nested splitter with 2 rows
 m_wndRightSplitter.CreateStatic(&m_wndMainSplitter,3,1,WS_CHILD|WS_VISIBLE|WS_BORDER,m_wndMainSplitter.IdFromRowCol(0,1));

 // First aux splitter pane
 m_wndRightSplitter.CreateView(0,0,RUNTIME_CLASS(CRegistersView),CSize(0,0),pContext);
 

 // Second aux splitter pane
 m_wndRightSplitter.CreateView(1,0,RUNTIME_CLASS(CStackView),CSize(0,0),pContext);
 m_wndRightSplitter.CreateView(2,0,RUNTIME_CLASS(CStackView),CSize(0,0),pContext);
 
// m_wndMainSplitter.SetActivePane(0,0);

 m_wndMainSplitter.SetColumnInfo(0,SPLITTERX,0);


 m_wndLeftSplitter.SetRowInfo(0,yc+iLeft0*lc+yf,0);	// cpu
 m_wndLeftSplitter.SetRowInfo(1,yc+iLeft1*lc+yf,0); // memory 1

 m_wndRightSplitter.SetRowInfo(0,yc+iRight0*lc+yf,0); // registers
 m_wndRightSplitter.SetRowInfo(1,yc+iRight1*lc+yf,0); // stack 1

  
 return TRUE;

	
//	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here


	RECT rct;
	GetWindowRect( &rct );
	SetWindowPos( NULL, 0, 0,
        rct.right - rct.left,
		yc+iYSize*lc+yf,
        SWP_NOZORDER | SWP_NOMOVE);

	return 0;
}

void CChildFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default

	lpMMI->ptMinTrackSize.x=MDICHILDX;
	lpMMI->ptMaxTrackSize.x=MDICHILDX;

	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);
}


void CChildFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class

	 m_wndRightSplitter.AdjustSplitters();
	 m_wndLeftSplitter.AdjustSplitters();

	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}


void CChildFrame::OnSizing( UINT nSide, LPRECT lpRect )
{
	
	int a,h;

	if (nSide==WMSZ_BOTTOM || nSide==WMSZ_BOTTOMLEFT || nSide==WMSZ_BOTTOMRIGHT)
	{
		a=((lpRect->bottom)-(lpRect->top)) / lc;
		iYSize=(BYTE) a;
		h=a*lc;
		lpRect->bottom=(lpRect->top)+h+yc+yf;
	}
	else if (nSide==WMSZ_TOP || nSide==WMSZ_TOPLEFT || nSide==WMSZ_TOPRIGHT)
	{
		a=((lpRect->bottom)-(lpRect->top)) / lc;
		iYSize=(BYTE) a;
		h=a*lc;
		lpRect->top=(lpRect->bottom)-(h+yc+yf);
	}

	CMDIChildWnd::OnSizing( nSide, lpRect );
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if (!IsWindowVisible()) return;

	m_wndLeftSplitter.AdjustSplitters();
	m_wndRightSplitter.AdjustSplitters();
}

void CChildFrame::OnOptionsSaveasdefaultlayout() 
{
	// TODO: Add your command handler code here

	CFile fcfg;

	char buf[300];
	CString szLongPathName;

	::GetModuleFileName(AfxGetInstanceHandle(),buf, 300);

	szLongPathName=buf;
	szLongPathName=szLongPathName.Left(szLongPathName.GetLength()-3)+"cfg";
	szLongPathName.MakeLower();

	fcfg.Open(szLongPathName,CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);


	iLeft0=m_wndLeftSplitter.nLines[0];
	iLeft1=m_wndLeftSplitter.nLines[1];

	iRight0=m_wndRightSplitter.nLines[0];
	iRight1=m_wndRightSplitter.nLines[1];


	fcfg.Write(&iLeft0,1);
	fcfg.Write(&iLeft1,1);
	fcfg.Write(&iRight0,1);
	fcfg.Write(&iRight1,1);
	fcfg.Write(&iYSize,1);

	fcfg.Flush();
	fcfg.Close();

}
