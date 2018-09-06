// BreakPointsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "BreakPointsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBreakPointsDlg dialog


CBreakPointsDlg::CBreakPointsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBreakPointsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBreakPointsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBreakPointsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBreakPointsDlg)
	DDX_Control(pDX, IDC_BREAKPOINTS_LIST, m_BreakPointsCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBreakPointsDlg, CDialog)
	//{{AFX_MSG_MAP(CBreakPointsDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBreakPointsDlg message handlers

BOOL CBreakPointsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_BreakPointsCtrl.InsertColumn(0,"Address",LVCFMT_RIGHT,60);
	m_BreakPointsCtrl.InsertColumn(1,"Status",LVCFMT_LEFT,60);
	m_BreakPointsCtrl.InsertColumn(2,"Hits",LVCFMT_LEFT,60);

	m_BreakPointsCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBreakPointsDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!IsWindowVisible()) return;

	m_BreakPointsCtrl.MoveWindow(0,0,cx,cy,TRUE);	
}

