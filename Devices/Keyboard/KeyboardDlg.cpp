// KeyboardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Keyboard.h"
#include "KeyboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog


CKeyboardDlg::CKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyboardDlg)
	//}}AFX_DATA_INIT
}


void CKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyboardDlg)
	DDX_Control(pDX, IDC_BUTTON_9, m_button9);
	DDX_Control(pDX, IDC_BUTTON_8, m_button8);
	DDX_Control(pDX, IDC_BUTTON_7, m_button7);
	DDX_Control(pDX, IDC_BUTTON_6, m_button6);
	DDX_Control(pDX, IDC_BUTTON_5, m_button5);
	DDX_Control(pDX, IDC_BUTTON_4, m_button4);
	DDX_Control(pDX, IDC_BUTTON_31, m_button31);
	DDX_Control(pDX, IDC_BUTTON_30, m_button30);
	DDX_Control(pDX, IDC_BUTTON_3, m_button3);
	DDX_Control(pDX, IDC_BUTTON_29, m_button29);
	DDX_Control(pDX, IDC_BUTTON_28, m_button28);
	DDX_Control(pDX, IDC_BUTTON_27, m_button27);
	DDX_Control(pDX, IDC_BUTTON_26, m_button26);
	DDX_Control(pDX, IDC_BUTTON_25, m_button25);
	DDX_Control(pDX, IDC_BUTTON_24, m_button24);
	DDX_Control(pDX, IDC_BUTTON_23, m_button23);
	DDX_Control(pDX, IDC_BUTTON_22, m_button22);
	DDX_Control(pDX, IDC_BUTTON_21, m_button21);
	DDX_Control(pDX, IDC_BUTTON_20, m_button20);
	DDX_Control(pDX, IDC_BUTTON_2, m_button2);
	DDX_Control(pDX, IDC_BUTTON_19, m_button19);
	DDX_Control(pDX, IDC_BUTTON_18, m_button18);
	DDX_Control(pDX, IDC_BUTTON_17, m_button17);
	DDX_Control(pDX, IDC_BUTTON_16, m_button16);
	DDX_Control(pDX, IDC_BUTTON_15, m_button15);
	DDX_Control(pDX, IDC_BUTTON_14, m_button14);
	DDX_Control(pDX, IDC_BUTTON_13, m_button13);
	DDX_Control(pDX, IDC_BUTTON_12, m_button12);
	DDX_Control(pDX, IDC_BUTTON_11, m_button11);
	DDX_Control(pDX, IDC_BUTTON_10, m_button10);
	DDX_Control(pDX, IDC_BUTTON_1, m_button1);
	DDX_Control(pDX, IDC_BUTTON_0, m_button0);
	DDX_Control(pDX, IDC_BUTTON_SHIFT2, m_right_shift);
	DDX_Control(pDX, IDC_BUTTON_SHIFT, m_left_shift);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyboardDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyboardDlg)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON_10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON_11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON_12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON_13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON_14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON_15, OnButton15)
	ON_BN_CLICKED(IDC_BUTTON_16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON_17, OnButton17)
	ON_BN_CLICKED(IDC_BUTTON_18, OnButton18)
	ON_BN_CLICKED(IDC_BUTTON_19, OnButton19)
	ON_BN_CLICKED(IDC_BUTTON_20, OnButton20)
	ON_BN_CLICKED(IDC_BUTTON_21, OnButton21)
	ON_BN_CLICKED(IDC_BUTTON_22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON_23, OnButton23)
	ON_BN_CLICKED(IDC_BUTTON_24, OnButton24)
	ON_BN_CLICKED(IDC_BUTTON_25, OnButton25)
	ON_BN_CLICKED(IDC_BUTTON_26, OnButton26)
	ON_BN_CLICKED(IDC_BUTTON_27, OnButton27)
	ON_BN_CLICKED(IDC_BUTTON_28, OnButton28)
	ON_BN_CLICKED(IDC_BUTTON_31, OnButton31)
	ON_BN_CLICKED(IDC_BUTTON_29, OnButton29)
	ON_BN_CLICKED(IDC_BUTTON_30, OnButton30)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg message handlers

BOOL CKeyboardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR));

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

void CKeyboardDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	ClientToScreen(&point);

	CMenu* pSubMenu=pMenu->GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

	
	CDialog::OnRButtonDown(nFlags, point);
}

void CKeyboardDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg mydlg;
	mydlg.DoModal();

}


void CKeyboardDlg::LoadConfiguration()
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

		Device.m_sample_port=szData[0];
	}
	else
	{

//  Create default .cfg File

	Device.m_sample_port=96;

	SaveConfiguration();
	}

}

void CKeyboardDlg::SaveConfiguration()
{
	CFile cf;

	char szDeviceName[20]="Keyboard           ";
	szDeviceName[20]=0;
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];
	int i;

	for (i=0;i<256;i++)	szIOMap[i]=0;
	for (i=0;i<5;i++) szIRQMap[i]=0;
	for (i=0;i<5;i++) szData[i]=0;

	szIRQMap[1]=1;

	szIOMap[Device.m_sample_port]=3;

	szData[0]=Device.m_sample_port;

	cf.Open(m_ExecutablePath+"\\"+m_AppFileName+".cfg",CFile::modeCreate | CFile::modeWrite);
	cf.Write(szDeviceName,20);
	cf.Write(szIOMap,256);
	cf.Write(szIRQMap,5);
	cf.Write(szData,5);
	cf.Close();

}


void CKeyboardDlg::ExternalConfig()
{
	CConfigDlg mydlg;

	mydlg.m_sample_port=Device.m_sample_port;

	if (mydlg.DoModal()==IDOK)
	{
		Device.m_sample_port=mydlg.m_sample_port;
		SaveConfiguration();
	}
}

#define ButtonFeedBack(BUTTONID) BUTTONID.SetState(TRUE);Sleep(10);BUTTONID.SetState(FALSE);

void CKeyboardDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='A';
	IRQ_RST75=1;

	ButtonFeedBack(m_button1)
}

void CKeyboardDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='B';
	IRQ_RST75=1;

	ButtonFeedBack(m_button2)
}

void CKeyboardDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='C';
	IRQ_RST75=1;
	ButtonFeedBack(m_button3)
}


void CKeyboardDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='D';	
	IRQ_RST75=1;
	ButtonFeedBack(m_button4)
}

void CKeyboardDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='E';
	IRQ_RST75=1;
	ButtonFeedBack(m_button5)
}

void CKeyboardDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='F';
	IRQ_RST75=1;
	ButtonFeedBack(m_button6)
}

void CKeyboardDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='Q';
	IRQ_RST75=1;
	ButtonFeedBack(m_button8)
}

void CKeyboardDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='W';
	IRQ_RST75=1;
	ButtonFeedBack(m_button9)
}

void CKeyboardDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='R';
	IRQ_RST75=1;
	ButtonFeedBack(m_button10)
}

void CKeyboardDlg::OnButton11() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='T';
	IRQ_RST75=1;	
	ButtonFeedBack(m_button11)
}

void CKeyboardDlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='Y';
	IRQ_RST75=1;	
	ButtonFeedBack(m_button12)
}

void CKeyboardDlg::OnButton13() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='U';
	IRQ_RST75=1;
	ButtonFeedBack(m_button13)
}

void CKeyboardDlg::OnButton14() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='I';
	IRQ_RST75=1;
	ButtonFeedBack(m_button14)
}

void CKeyboardDlg::OnButton15() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='O';
	IRQ_RST75=1;	
	ButtonFeedBack(m_button15)
}

void CKeyboardDlg::OnButton16() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='P';
	IRQ_RST75=1;
	ButtonFeedBack(m_button16)
}

void CKeyboardDlg::OnButton17() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer='S';
	IRQ_RST75=1;
	ButtonFeedBack(m_button17)
}

void CKeyboardDlg::OnButton18() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='1';
	else
		Device.m_buffer='G';
	
	IRQ_RST75=1;
	ButtonFeedBack(m_button18)
}

void CKeyboardDlg::OnButton19() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='2';
	else
		Device.m_buffer='H';

	IRQ_RST75=1;
	ButtonFeedBack(m_button19)
}

void CKeyboardDlg::OnButton20() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='3';
	else
		Device.m_buffer='J';

	IRQ_RST75=1;
	ButtonFeedBack(m_button20)
}

void CKeyboardDlg::OnButton21() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='4';
	else
		Device.m_buffer='K';

	IRQ_RST75=1;
	ButtonFeedBack(m_button21)
}

void CKeyboardDlg::OnButton22() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer=',';
	else
		Device.m_buffer='L';

	IRQ_RST75=1;
	ButtonFeedBack(m_button22)
}

void CKeyboardDlg::OnButton23() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer=' ';
	IRQ_RST75=1;
	ButtonFeedBack(m_button23)
}

void CKeyboardDlg::OnButton24() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='5';
	else
		Device.m_buffer='X';

	IRQ_RST75=1;
	ButtonFeedBack(m_button24)
}

void CKeyboardDlg::OnButton25() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='6';
	else
		Device.m_buffer='V';

	IRQ_RST75=1;
	ButtonFeedBack(m_button25)
}

void CKeyboardDlg::OnButton26() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='7';
	else
		Device.m_buffer='N';

	IRQ_RST75=1;
	ButtonFeedBack(m_button26)
}

void CKeyboardDlg::OnButton27() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='8';
	else
		Device.m_buffer='M';

	IRQ_RST75=1;
	ButtonFeedBack(m_button27)
}

void CKeyboardDlg::OnButton28() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
		Device.m_buffer='9';
	else
		Device.m_buffer='Z';

	IRQ_RST75=1;
	ButtonFeedBack(m_button28)
}

void CKeyboardDlg::OnButton31() 
{
	// TODO: Add your control notification handler code here
	Device.m_buffer=13;
	IRQ_RST75=1;
	ButtonFeedBack(m_button31)
}

void CKeyboardDlg::OnButton29() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
	{
		Device.m_buffer='0';
		IRQ_RST75=1;
	}
	ButtonFeedBack(m_button29)
}

void CKeyboardDlg::OnButton30() 
{
	// TODO: Add your control notification handler code here
	if (m_left_shift.GetCheck()==BST_CHECKED || m_right_shift.GetCheck()==BST_CHECKED)
	{
		Device.m_buffer=':';
		IRQ_RST75=1;
	}
	ButtonFeedBack(m_button30)
}


BOOL CKeyboardDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL r=FALSE;
	if (pMsg->message >= WM_KEYFIRST &&   pMsg->message <=WM_KEYLAST)
	{
	r=TranslateAccelerator(m_hWnd, m_hAccel,pMsg);
	}

	if (r==FALSE) return (IsDialogMessage(pMsg));
	else return TRUE;
}
