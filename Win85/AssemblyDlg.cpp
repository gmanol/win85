// AssemblyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "AssemblyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg dialog


CAssemblyDlg::CAssemblyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssemblyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAssemblyDlg)
	m_assembly_edit = _T("");
	//}}AFX_DATA_INIT
}


void CAssemblyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssemblyDlg)
	DDX_Control(pDX, IDC_ASSEMBLY_EDIT, m_assembly_control);
	DDX_Text(pDX, IDC_ASSEMBLY_EDIT, m_assembly_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssemblyDlg, CDialog)
	//{{AFX_MSG_MAP(CAssemblyDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg message handlers

void CAssemblyDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_assembly_control.SetSel(-1);	

}
