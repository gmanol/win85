// DevicesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "DevicesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevicesDlg dialog


CDevicesDlg::CDevicesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevicesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevicesDlg)
	//}}AFX_DATA_INIT
}


void CDevicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevicesDlg)
	DDX_Control(pDX, IDC_DEVICE_LIST, m_device_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevicesDlg, CDialog)
	//{{AFX_MSG_MAP(CDevicesDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevicesDlg message handlers

BOOL CDevicesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	m_device_list.InsertColumn(0,"Device Name",LVCFMT_LEFT,114);
	m_device_list.InsertColumn(1,"Status",LVCFMT_LEFT,54);
	m_device_list.InsertColumn(2,"I/O Ports",LVCFMT_LEFT,100);
	m_device_list.InsertColumn(3,"IRQs",LVCFMT_LEFT,70);


	m_device_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDevicesDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!IsWindowVisible()) return;

	m_device_list.MoveWindow(0,0,cx,cy,TRUE);

}
