// DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Device.h"
#include "DeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

#define	IRQ_TRAP *(m_pIRQPenting+0)
#define	IRQ_RST75 *(m_pIRQPenting+1)
#define	IRQ_RST65 *(m_pIRQPenting+2)
#define	IRQ_RST55 *(m_pIRQPenting+3)
#define	IRQ_INTR *(m_pIRQPenting+4)

#define BUS_OPCODE *(m_pIRQPenting+5)
#define BUS_OPERAND *(m_pIRQPenting+6)


CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceDlg)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg message handlers

BOOL CDeviceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buffer[100];
	::GetModuleFileName(AfxGetInstanceHandle(), buffer, _MAX_PATH);
    CString sPath = (CString)buffer;
    sPath = sPath.Left(sPath.ReverseFind('\\'));
	m_ExecutablePath=sPath;

	CString h,b;
	m_AppFileName=AfxGetAppName();
	m_AppFileName.MakeLower();
	h=m_AppFileName.Mid(0,1);
	b=m_AppFileName.Mid(1);
	h.MakeUpper();
	m_AppFileName=h+b;

	pMenu=new CMenu();
	pMenu->LoadMenu(IDR_CONTEXT);

	LoadConfiguration();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceDlg::LoadConfiguration()
{
	char szDeviceName[20];
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];

	CFile cf;

	if (cf.Open(m_ExecutablePath+"\\"+m_AppFileName+".cfg",CFile::modeRead))
	{

		cf.Read(szDeviceName,20);
		cf.Read(szIOMap,256);
		cf.Read(szIRQMap,5);
		cf.Read(szData,5);
		cf.Close();

//		m_port=szData[0];
	}
	else
	{

//  Create default .cfg File

//	m_port=0x20;			// I/O port

	SaveConfiguration();
	}
}

void CDeviceDlg::SaveConfiguration()
{
	CFile cf;

	char szDeviceName[20]="Sample Device      ";
	szDeviceName[20]=0;
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];
	int i;

	for (i=0;i<256;i++)	szIOMap[i]=3;
	for (i=0;i<5;i++) szIRQMap[i]=0;

//	szIOMap[m_port]=3;
//	szData[0]=m_port;

	cf.Open(m_ExecutablePath+"\\"+m_AppFileName+".cfg",CFile::modeCreate | CFile::modeWrite);
	cf.Write(szDeviceName,20);
	cf.Write(szIOMap,256);
	cf.Write(szIRQMap,5);
	cf.Write(szData,5);
	cf.Close();
}

void CDeviceDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg mydlg;
	mydlg.DoModal();
}

void CDeviceDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);

	CMenu* pSubMenu=pMenu->GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	CDialog::OnRButtonDown(nFlags, point);
}
