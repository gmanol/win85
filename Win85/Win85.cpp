// Win85.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Win85.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "Win85Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWin85App

BEGIN_MESSAGE_MAP(CWin85App, CWinApp)
	//{{AFX_MSG_MAP(CWin85App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

// Devices Exported functions

HINSTANCE	CWin85App::mylib[];
WRITEPROC	CWin85App::gDeviceWrite[];
READPROC	CWin85App::gDeviceRead[];
CONFIGPROC	CWin85App::gDeviceConfig[];
SHOWPROC	CWin85App::gShowWindow[];
HIDEPROC	CWin85App::gHideWindow[];
INITPROC	CWin85App::gInitIRQ[];
RESETPROC	CWin85App::gDeviceReset[];
DLGMSGPROC	CWin85App::gDialogMessage[];

// CWin85App Global variables

CString CWin85App::gDevicesFilenames[];
int		CWin85App::gNumOfDevices;
int		CWin85App::gRIOMap[];
int		CWin85App::gWIOMap[];
int		CWin85App::gIRQMap[];
BOOL	CWin85App::gDeviceStatus[];
CString CWin85App::gExecutablePath;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_about;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CWin85App construction


CWin85App::CWin85App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWin85App object

CWin85App theApp;

/////////////////////////////////////////////////////////////////////////////
// CWin85App initialization

BOOL CWin85App::InitInstance()
{
	// initialize global variables (emc)
	gNumOfDevices=0;
	int j;
	for (j=0;j<256;j++)
	{
		gRIOMap[j]=-1;
		gWIOMap[j]=-1;
	}

	for (j=0;j<7;j++)
	{	
		gIRQMap[j]=0;
	}

	for (j=0;j<100;j++)
	{
		gDeviceStatus[j]=FALSE;
	}

	char buffer[100];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), buffer, _MAX_PATH));
    CString sPath = (CString)buffer;
    sPath = sPath.Left(sPath.ReverseFind('\\'));

	gExecutablePath=sPath;

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_WIN85TYPE,
		RUNTIME_CLASS(CWin85Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCpuView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

    // Don't display a new MDI child window during startup
    if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
      cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo)) 
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->MDIMaximize(pMainFrame);	// - emc
	pMainFrame->UpdateWindow();

//	CAboutDlg aboutDlg;
//	aboutDlg.DoModal();

	return TRUE;
}


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_about = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_REGISTER_EDIT, m_about);
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	#include "License.inc"
	m_about=pStr;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// App command to run the dialog
void CWin85App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWin85App message handlers


CString CWin85App::Byte2Hex(BYTE i)
{
	CString preCalc[16]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};
	return(preCalc[i>>4]+preCalc[i&0xf]);
}

CString CWin85App::Byte2Bin(BYTE i)
{
	CString preCalc[16]={"0000","0001","0010","0011","0100",
		"0101","0110","0111","1000","1001","1010","1011",
		"1100","1101","1110","1111"};

	return(preCalc[i>>4]+preCalc[i&0xf]);
}

CString CWin85App::Byte2Dec(BYTE i)
{
	CString r,t;
	char txt[10];
	r=itoa(i,txt,10);
	r.TrimLeft();
	r.TrimRight();
	t="000";
	t=t.Left(3-r.GetLength());
	return(t+r);
}

CString CWin85App::Word2Hex(WORD i)
{
	return(Byte2Hex(i>>8)+Byte2Hex(i&0xff));
}

CString CWin85App::Word2Hex(BYTE h, BYTE l)
{
	return(Byte2Hex(h)+Byte2Hex(l));
}


CString CWin85App::Word2Bin(WORD i)
{
	return("0000");
}

CString CWin85App::Word2Dec(WORD i)
{
	CString r,t;
	char txt[10];
	r=itoa(i,txt,10);
	r.TrimLeft();
	r.TrimRight();
	t="00000";
	t=t.Left(5-r.GetLength());
	return(t+r);
}

CString CWin85App::DWord2Dec(DWORD i)
{
	CString r,t;
	char txt[16];

	r=_ui64toa(i,txt,10);
	r.TrimLeft();
	r.TrimRight();
	t="0000000000";
	t=t.Left(10-r.GetLength());
	return(t+r);
}

CString CWin85App::Bit2Bin(BYTE b, BYTE mask)
{
	if ((b & mask)!=0) return("1");
	return("0");
}

//----------------------------------------------------------------
BOOL CWin85App::Check(CString str, int Count)
{
	int	i,j;
	CString s;
	CString ValidStr[17]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H'};
	BOOL bCheck;

	for (i=0;i<str.GetLength();i++)
	{
		s=str.Mid(i,1);
		bCheck=FALSE;

		for (j=0;j<Count;j++)
		{
			if (s==ValidStr[j]) bCheck=TRUE;
		}

		if (bCheck==FALSE) return(FALSE);
	}

	return(TRUE);
}

DWORD CWin85App::StrBin2Val(CString str)
{
	int	i,m;
	DWORD Result;
	DWORD Adder;
	
	Result=0;
	Adder=1;

	m=str.GetLength();

	for (i=0;i<m;i++)
	{
		if (str.Mid(m-i-1,1)=="1") Result=Result+Adder;
		Adder=Adder*2;
	}

	return (Result);
}

DWORD CWin85App::StrHex2Val(CString str)
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

DWORD CWin85App::Str2Val(CString t,BOOL* State)
{

	CString s,l;

	t.MakeUpper();
	t.TrimLeft();t.TrimRight();

	if (t.GetLength()==0) {*State=FALSE;return 0;}

	if (Check(t,17)==FALSE) {*State=FALSE;return 0;}

	s=t.Right(1);

	if (s=="H")
	{
		if (t.GetLength()==1) {*State=FALSE;return 0;}
		l=t.Left(t.GetLength()-1);

		if (Check(l,16)==FALSE) {*State=FALSE;return 0;}

		*State=TRUE;
		return StrHex2Val(l);
	}

	if (s=="B")
	{
		if (t.GetLength()==1) {*State=FALSE;return 0;}
		l=t.Left(t.GetLength()-1);
		if (Check(l,2)==FALSE) {*State=FALSE;return 0;}

		*State=TRUE;
		return StrBin2Val(l);
	}



	if (Check(t,10)==FALSE) {*State=FALSE;return 0;}

	*State=TRUE;

	return ((DWORD) atoi(t));
}


BOOL CWin85App::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class


	  if (pMsg->message == WM_KEYDOWN && 
		(pMsg->wParam == VK_F7 ||
		pMsg->wParam == VK_F9 ||
		(pMsg->wParam == (VK_F2 | VK_CONTROL)) ||
		pMsg->wParam == VK_F12)) return CWinApp::PreTranslateMessage(pMsg);

		BOOL d;

		d=FALSE;
		for (int i=0;i<100;i++)			// max 100 devices
		{
		if (CWin85App::gDeviceStatus[i]==TRUE) d=CWin85App::gDialogMessage[i](pMsg);
		if (d==TRUE) return TRUE;
		}
		
		return CWinApp::PreTranslateMessage(pMsg);
}

