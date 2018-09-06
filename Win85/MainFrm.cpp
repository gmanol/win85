// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Win85.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TOOLBAR_RUN, OnViewToolbarRun)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_RUN, OnUpdateViewToolbarRun)
	ON_COMMAND(ID_VIEW_TOOLBAR_BREAKPOINTS, OnViewToolbarBreakpoints)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBAR_BREAKPOINTS, OnUpdateViewToolbarBreakpoints)
	ON_COMMAND(ID_VIEW_TOOLBARS_DEVICES, OnViewToolbarsDevices)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBARS_DEVICES, OnUpdateViewToolbarsDevices)
	ON_WM_MOVE()
	ON_COMMAND(ID_VIEW_TOOLBARS_HARDWARE, OnViewToolbarsHardware)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBARS_HARDWARE, OnUpdateViewToolbarsHardware)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT,WS_CHILD |WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	if (!(m_runToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) ||
		!(m_runToolBar.LoadToolBar(IDR_RUNTOOLBAR)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!(m_breakpointsToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) ||
		!(m_breakpointsToolBar.LoadToolBar(IDR_BREAKPOINTSTOOLBAR)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!(m_hardwareToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)) ||
		!(m_hardwareToolBar.LoadToolBar(IDR_HARDWARETOOLBAR)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_runToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_breakpointsToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_hardwareToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	
	DockControlBar(&m_wndToolBar);
	DockControlBarLeftOf(&m_runToolBar,&m_wndToolBar);
	DockControlBarLeftOf(&m_breakpointsToolBar,&m_runToolBar);
	DockControlBarLeftOf(&m_hardwareToolBar,&m_breakpointsToolBar);


	m_wndToolBar.SetWindowText("File");
	m_runToolBar.SetWindowText("Run");
	m_breakpointsToolBar.SetWindowText("Breakpoints");
	m_hardwareToolBar.SetWindowText("Hardware");

	m_DevicesDlg.Create(IDD_CONNECT_DIALOG,this);

	m_runToolBar.SetButtonStyle(0,TBBS_CHECKBOX);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	int sx,sy;

	sy=::GetSystemMetrics(SM_CYSCREEN);
	sx=::GetSystemMetrics(SM_CXSCREEN);
    cs.cy = sy*9/10;
    cs.cx = sx*9/10;
    cs.y = (sy - cs.cy) / 2;
    cs.x = (sx - cs.cx) / 2;
	cs.style |= (WS_HSCROLL|WS_VSCROLL);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewToolbarRun() 
{
	// TODO: Add your command handler code here

	CControlBar *pBar;
	pBar = (CControlBar *) &m_runToolBar;
	ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE)==0, FALSE);
}

void CMainFrame::OnUpdateViewToolbarRun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	CControlBar *pBar;
	pBar = (CControlBar *) &m_runToolBar;
	pCmdUI->SetCheck(pBar->GetStyle() & WS_VISIBLE);
}

void CMainFrame::OnViewToolbarBreakpoints() 
{
	// TODO: Add your command handler code here
	CControlBar *pBar;
	pBar = (CControlBar *) &m_breakpointsToolBar;
	ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE)==0, FALSE);
}

void CMainFrame::OnUpdateViewToolbarBreakpoints(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar *pBar;
	pBar = (CControlBar *) &m_breakpointsToolBar;
	pCmdUI->SetCheck(pBar->GetStyle() & WS_VISIBLE);
	
}


void CMainFrame::OnViewToolbarsDevices() 
{
	// TODO: Add your command handler code here
	m_DevicesDlg.ShowWindow((m_DevicesDlg.GetStyle() & WS_VISIBLE)==0);
	SetFocus();
}

void CMainFrame::OnUpdateViewToolbarsDevices(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_DevicesDlg.GetStyle() & WS_VISIBLE);

}

void CMainFrame::DockControlBarLeftOf(CToolBar *Bar, CToolBar *LeftOf)
{
    CRect rect;
    DWORD dw;
    UINT n;

    // get MFC to adjust the dimensions of all docked ToolBars
    // so that GetWindowRect will be accurate
    RecalcLayout(TRUE);

    LeftOf->GetWindowRect(&rect);
    rect.OffsetRect(1,0);
    dw = LeftOf->GetBarStyle();
    n = 0;
    n = (dw & CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
    n = (dw & CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
    n = (dw & CBRS_ALIGN_LEFT && n==0) ?  AFX_IDW_DOCKBAR_LEFT : n;
    n = (dw & CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

    DockControlBar(Bar,n,&rect);
}


void CMainFrame::OnMove(int x, int y) 
{
	CMDIFrameWnd::OnMove(x, y);
	
	// TODO: Add your message handler code here
	RECT FrameRect,DevicesRect;
	CPoint mypoint;
	int lx,ly;
	
	this->GetWindowRect(&FrameRect);
//	ClientToScreen(&FrameRect);
	m_DevicesDlg.GetWindowRect(&DevicesRect);

	lx=DevicesRect.right-DevicesRect.left;
	ly=DevicesRect.bottom-DevicesRect.top;

	mypoint.y=FrameRect.top+80;
	mypoint.x=FrameRect.right-360;

	DevicesRect.top=mypoint.y;
	DevicesRect.left=mypoint.x;
	DevicesRect.bottom=mypoint.y+ly;
	DevicesRect.right=mypoint.x+lx;


	m_DevicesDlg.MoveWindow(&DevicesRect,TRUE);
}


void CMainFrame::OnViewToolbarsHardware() 
{
	// TODO: Add your command handler code here
	CControlBar *pBar;
	pBar = (CControlBar *) &m_hardwareToolBar;
	ShowControlBar(pBar, (pBar->GetStyle() & WS_VISIBLE)==0, FALSE);

}

void CMainFrame::OnUpdateViewToolbarsHardware(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CControlBar *pBar;
	pBar = (CControlBar *) &m_hardwareToolBar;
	pCmdUI->SetCheck(pBar->GetStyle() & WS_VISIBLE);
	
}


