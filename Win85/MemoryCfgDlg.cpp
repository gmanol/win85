// MemoryCfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "MemoryCfgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoryCfgDlg dialog


CMemoryCfgDlg::CMemoryCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryCfgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoryCfgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMemoryCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryCfgDlg)
	DDX_Control(pDX, IDC_MEMORY_CFGLIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemoryCfgDlg, CDialog)
	//{{AFX_MSG_MAP(CMemoryCfgDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryCfgDlg message handlers

BOOL CMemoryCfgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	
	m_list.InsertColumn(0,"Bank",LVCFMT_CENTER,84);
	m_list.InsertColumn(1,"Type",LVCFMT_LEFT,54);
	m_list.InsertColumn(2,"Mirror",LVCFMT_LEFT,54);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
