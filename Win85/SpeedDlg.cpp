// SpeedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "SpeedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg dialog


CSpeedDlg::CSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpeedDlg)
	//}}AFX_DATA_INIT
}


void CSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeedDlg)
	DDX_Control(pDX, IDC_TURBO_CHECK, m_Turbo_Button);
	DDX_Control(pDX, IDC_SPEED_SLIDER, m_slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpeedDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeedDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_TURBO_CHECK, OnTurboCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeedDlg message handlers

BOOL CSpeedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_RunSpeed=16000;
	m_Turbo=FALSE;
	m_slider.SetRange(0,50000,TRUE);
	m_slider.SetTicFreq(5000);
	m_slider.SetPos(m_RunSpeed);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSpeedDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_RunSpeed=m_slider.GetPos();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSpeedDlg::OnTurboCheck() 
{
	// TODO: Add your control notification handler code here
	int i;
	i=m_Turbo_Button.GetCheck();
	if (i==0)
	{
		m_Turbo=FALSE;
	}
	else
	{
		m_Turbo=TRUE;
		
	}
}
