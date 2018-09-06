// BASICIOdlg.cpp : implementation file
//

#include "stdafx.h"
#include "BASICIO.h"
#include "BASICIOdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBASICIOdlg dialog

#define	IRQ_TRAP *(m_pIRQPenting+0)
#define	IRQ_RST75 *(m_pIRQPenting+1)
#define	IRQ_RST65 *(m_pIRQPenting+2)
#define	IRQ_RST55 *(m_pIRQPenting+3)
#define	IRQ_INTR *(m_pIRQPenting+4)


CBASICIOdlg::CBASICIOdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBASICIOdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBASICIOdlg)
	m_edit_out = _T("");
	m_edit_in = 0;
	m_pulse55 = 0;
	m_pulse65 = 0;
	m_pulseINTR = 0;
	m_INTRBus = _T("");
	//}}AFX_DATA_INIT
}


void CBASICIOdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBASICIOdlg)
	DDX_Text(pDX, IDC_EDIT_OUT, m_edit_out);
	DDX_Text(pDX, IDC_EDIT_IN, m_edit_in);
	DDX_Text(pDX, IDC_EDIT_PULSE_55, m_pulse55);
	DDX_Text(pDX, IDC_EDIT_PULSE_65, m_pulse65);
	DDX_Text(pDX, IDC_EDIT_PULSE_INTR, m_pulseINTR);
	DDX_Text(pDX, IDC_EDIT_INTRBUS, m_INTRBus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBASICIOdlg, CDialog)
	//{{AFX_MSG_MAP(CBASICIOdlg)
	ON_BN_CLICKED(IDC_IRQ_BUTTON_TRAP, OnIrqButtonTrap)
	ON_BN_CLICKED(IDC_IRQ_BUTTON_RST75, OnIrqButtonRst75)
	ON_BN_CLICKED(IDC_IRQ_BUTTON_RST65, OnIrqButtonRst65)
	ON_BN_CLICKED(IDC_IRQ_BUTTON_RST55, OnIrqButtonRst55)
	ON_BN_CLICKED(IDC_IRQ_BUTTON_INTR, OnIrqButtonIntr)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBASICIOdlg message handlers


BOOL CBASICIOdlg::OnInitDialog() 
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

	m_pulse55=25;
	m_pulse65=25;
	m_pulseINTR=25;
	m_INTRBus="RST 5";
	UpdateData(FALSE);

	LoadConfiguration();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CBASICIOdlg::LoadConfiguration()
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

		m_port=szData[0];
	}
	else
	{

//  Create default .cfg File

	m_port=0x20;			// I/O port

	SaveConfiguration();
	}
}

void CBASICIOdlg::SaveConfiguration()
{
	CFile cf;

	char szDeviceName[20]="Basic I/O          ";
	szDeviceName[20]=0;
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];
	int i;

	for (i=0;i<256;i++)	szIOMap[i]=0;
	for (i=0;i<5;i++) szIRQMap[i]=1;

	szIOMap[m_port]=3;

	szData[0]=m_port;

	cf.Open(m_ExecutablePath+"\\"+m_AppFileName+".cfg",CFile::modeCreate | CFile::modeWrite);
	cf.Write(szDeviceName,20);
	cf.Write(szIOMap,256);
	cf.Write(szIRQMap,5);
	cf.Write(szData,5);
	cf.Close();
}

void CBASICIOdlg::OnIrqButtonTrap() 
{
	// TODO: Add your control notification handler code here

	IRQ_TRAP=1;
}

void CBASICIOdlg::OnIrqButtonRst75() 
{
	// TODO: Add your control notification handler code here
	IRQ_RST75=1;
}

void CBASICIOdlg::OnIrqButtonRst65() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	IRQ_RST65=m_pulse65;	
}

void CBASICIOdlg::OnIrqButtonRst55() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	IRQ_RST55=m_pulse55;
}

void CBASICIOdlg::OnIrqButtonIntr() 
{
	// TODO: Add your control notification handler code here

#define BUS_OPCODE *(m_pIRQPenting+5)
#define BUS_OPERAND *(m_pIRQPenting+6)

	UpdateData(TRUE);

	CString a=m_INTRBus;
	DWORD pulse=m_pulseINTR;

	BOOL r=FALSE;

	if ((a=="RST 0") || (a=="RST0")) {BUS_OPCODE=0xc7;r=TRUE;}
	if ((a=="RST 1") || (a=="RST1")) {BUS_OPCODE=0xcf;r=TRUE;}
	if ((a=="RST 2") || (a=="RST2")) {BUS_OPCODE=0xd7;r=TRUE;}
	if ((a=="RST 3") || (a=="RST3")) {BUS_OPCODE=0xdf;r=TRUE;}	
	if ((a=="RST 4") || (a=="RST4")) {BUS_OPCODE=0xe7;r=TRUE;}
	if ((a=="RST 5") || (a=="RST5")) {BUS_OPCODE=0xef;r=TRUE;}
	if ((a=="RST 6") || (a=="RST6")) {BUS_OPCODE=0xf7;r=TRUE;}
	if ((a=="RST 7") || (a=="RST7")) {BUS_OPCODE=0xff;r=TRUE;}

	
	if (a.Left(4)=="CALL") 	
	{
	a=a.Mid(5);
	BUS_OPCODE=0xcd;
	BUS_OPERAND=(WORD) StrHex2Val(a);
	m_INTRBus="CALL "+Word2Hex((WORD) StrHex2Val(a));UpdateData(FALSE);
	r=TRUE;
	}

	if (r=FALSE) {Beep(500,1);return;}

	IRQ_INTR=pulse;
}


BOOL CBASICIOdlg::PreTranslateMessage(MSG* pMsg) 
{
		// TODO: Add your specialized code here and/or call the base class

	return (IsDialogMessage(pMsg));
}

void CBASICIOdlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	ClientToScreen(&point);

	CMenu* pSubMenu=pMenu->GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	CDialog::OnRButtonDown(nFlags, point);
}

void CBASICIOdlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg mydlg;
	mydlg.DoModal();
}

DWORD CBASICIOdlg::StrHex2Val(CString str)
{
	int	i,m;
	DWORD Result;
	DWORD Adder;
	DWORD Mul;
	CString s;
	
	Result=0;
	Adder=1;

	m=str.GetLength();

	for (i=0;i<m;i++)
	{
		s=str.Mid(m-i-1,1);

		if (s=="0") Mul=0;
		if (s=="1") Mul=1;
		if (s=="2") Mul=2;
		if (s=="3") Mul=3;
		if (s=="4") Mul=4;
		if (s=="5") Mul=5;
		if (s=="6") Mul=6;
		if (s=="7") Mul=7;
		if (s=="8") Mul=8;
		if (s=="9") Mul=9;
		if (s=="A") Mul=10;
		if (s=="B") Mul=11;
		if (s=="C") Mul=12;
		if (s=="D") Mul=13;
		if (s=="E") Mul=14;
		if (s=="F") Mul=15;

		Result=Result+Adder*Mul;
		Adder=Adder*16;
	}

	return (Result);
}

CString CBASICIOdlg::Byte2Hex(BYTE i)
{
	CString preCalc[16]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
	return(preCalc[i>>4]+preCalc[i&0xf]);
}

CString CBASICIOdlg::Word2Hex(WORD i)
{
	return(Byte2Hex(i>>8)+Byte2Hex(i&0xff));
}
