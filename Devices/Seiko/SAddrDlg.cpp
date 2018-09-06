// SAddrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeikoDll.h"
#include "SAddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSAddrDlg dialog


CSAddrDlg::CSAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAddrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSAddrDlg)
	m_edit_cs = 0;
	m_edit_data = 0;
	m_edit_instr = 0;
	//}}AFX_DATA_INIT
}


void CSAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAddrDlg)
	DDX_Text(pDX, IDC_EDIT_CS, m_edit_cs);
	DDX_Text(pDX, IDC_EDIT_DATA, m_edit_data);
	DDX_Text(pDX, IDC_EDIT_INSTR, m_edit_instr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSAddrDlg, CDialog)
	//{{AFX_MSG_MAP(CSAddrDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAddrDlg message handlers
