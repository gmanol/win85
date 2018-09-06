// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

#define	IRQ_TRAP *(m_pIRQPenting+0)
#define	IRQ_RST75 *(m_pIRQPenting+1)
#define	IRQ_RST65 *(m_pIRQPenting+2)
#define	IRQ_RST55 *(m_pIRQPenting+3)
#define	IRQ_INTR *(m_pIRQPenting+4)

#define BUS_OPCODE *(m_pIRQPenting+5)
#define BUS_OPERAND *(m_pIRQPenting+6)


CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitorDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
	//{{AFX_MSG_MAP(CMonitorDlg)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	ON_COMMAND(ID_MENU_INFO, OnMenuInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg message handlers

BOOL CMonitorDlg::OnInitDialog() 
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

	ClearTable();

	SetTimer(1,100,NULL);

	TColor[0]=RGB(0,0,0);
	TColor[1]=RGB(255,0,0);
	TColor[2]=RGB(0,0,255);
	TColor[3]=RGB(255,255,255);


	SetWindowPos(NULL,0,0,245,227,SWP_NOMOVE|SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitorDlg::LoadConfiguration()
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

void CMonitorDlg::SaveConfiguration()
{
	CFile cf;

	char szDeviceName[20]="I/O Monitor        ";
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

void CMonitorDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg mydlg;
	mydlg.DoModal();
}

void CMonitorDlg::OnMenuInfo() 
{
	// TODO: Add your command handler code here
	CInfoDlg mydlg;
	mydlg.DoModal();
}


void CMonitorDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ClientToScreen(&point);

	CMenu* pSubMenu=pMenu->GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	CDialog::OnRButtonDown(nFlags, point);
}

#define LF 12
#define CF 14

void CMonitorDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	CFont myfont;

	myfont.CreateFont(8,2,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
	DEFAULT_QUALITY,FF_SWISS,
	"MS Sans Serif");


	CFont* pOldFont=dc.SelectObject(&myfont);


	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
	dc.SetTextColor(RGB(20,27,100));
	

	int	c=0;
	for (int x=CF;x<CF*17;x=x+CF)
	{
		dc.TextOut(x+1,0,Byte2Hex(c));
		c++;
	}
	
	dc.TextOut(0,LF*1, "00");
	dc.TextOut(0,LF*2, "10");
	dc.TextOut(0,LF*3, "20");
	dc.TextOut(0,LF*4, "30");
	dc.TextOut(0,LF*5, "40");
	dc.TextOut(0,LF*6, "50");
	dc.TextOut(0,LF*7, "60");
	dc.TextOut(0,LF*8, "70");
	dc.TextOut(0,LF*9, "80");
	dc.TextOut(0,LF*10,"90");
	dc.TextOut(0,LF*11,"A0");
	dc.TextOut(0,LF*12,"B0");
	dc.TextOut(0,LF*13,"C0");
	dc.TextOut(0,LF*14,"D0");
	dc.TextOut(0,LF*15,"E0");
	dc.TextOut(0,LF*16,"F0");

	dc.SelectObject(pOldFont);

	RedrawContents();
	// Do not call CDialog::OnPaint() for painting messages
}

void CMonitorDlg::RedrawContents()
{
	CClientDC dc(this);

	int x,y,c;

	CFont myfont;

	myfont.CreateFont(8,0,0,0,400,FALSE,FALSE,0,DEFAULT_CHARSET,
	OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
	PROOF_QUALITY,FF_SWISS | VARIABLE_PITCH,
	"MS Sans Serif");


	CFont* pOldFont=dc.SelectObject(&myfont);


	dc.SetBkMode(OPAQUE);
	dc.SetBkColor(GetSysColor(COLOR_BTNFACE));

	c=0;
	for (y=LF*1;y<LF*17;y=y+LF)
	{
		for (x=CF;x<CF*17;x=x+CF)
		{
		dc.SetTextColor(TColor[m_access[c]]);
		dc.TextOut(x+1,y,Byte2Hex(m_ports[c]));
		c++;
		}
	}


	dc.SelectObject(pOldFont);
}


void CMonitorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_update==TRUE) {m_update=FALSE;RedrawContents();}

	CDialog::OnTimer(nIDEvent);
}

CString CMonitorDlg::Byte2Hex(BYTE i)
{
	CString preCalc[16]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
	return(preCalc[i>>4]+preCalc[i&0xf]+" ");
}


void CMonitorDlg::OnMenuClear() 
{
	// TODO: Add your command handler code here

	ClearTable();
}

void CMonitorDlg::ClearTable()
{
	for (int i=0;i<256;i++)
	{
		m_ports[i]=0;
		m_access[i]=0;
	}
	m_update=TRUE;
}

