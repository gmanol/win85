// SeikoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeikoDll.h"
#include "SeikoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeikoDlg dialog


CSeikoDlg::CSeikoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeikoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeikoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSeikoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeikoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeikoDlg, CDialog)
	//{{AFX_MSG_MAP(CSeikoDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_DOUBLE_SIZE, OnMenuDoubleSize)
	ON_COMMAND(ID_MENU_INVERTCOLORS, OnMenuInvertcolors)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeikoDlg message handlers

BOOL CSeikoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	char buffer[100];
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), buffer, _MAX_PATH));
    CString sPath = (CString)buffer;
    sPath = sPath.Left(sPath.ReverseFind('\\'));
	ExecutablePath=sPath;

	CString h,b;
	sz_AppFileName=AfxGetAppName();
	sz_AppFileName.MakeLower();
	h=sz_AppFileName.Mid(0,1);
	b=sz_AppFileName.Mid(1);
	h.MakeUpper();
	sz_AppFileName=h+b;

	pMenu=new CMenu();
	pMenu->LoadMenu(IDR_CONTEXT);

	LoadConfiguration();

	if (SizeX==256)
	{
	pMenu->CheckMenuItem(ID_MENU_DOUBLE_SIZE,MF_CHECKED);
	}
	else
	{
	pMenu->CheckMenuItem(ID_MENU_DOUBLE_SIZE,MF_UNCHECKED);
	}

	if (InvertColors==TRUE)
	{
	pMenu->CheckMenuItem(ID_MENU_INVERTCOLORS,MF_CHECKED);
	}
	else
	{
	pMenu->CheckMenuItem(ID_MENU_INVERTCOLORS,MF_UNCHECKED);
	}

	ResizeDialog();

	SetTimer(1,30,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeikoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC MemDC;
	
	MemDC.CreateCompatibleDC(NULL);
	CBitmap MetBitmap;
	MetBitmap.CreateBitmap(128,64,1,1,&Seiko.SeikoRAM);
	CBitmap* pOldBitmap=MemDC.SelectObject(&MetBitmap);

	if (InvertColors==FALSE)
	{
	dc.StretchBlt(0,0,SizeX,SizeY,&MemDC,0,0,128,64,NOTSRCCOPY);
	}
	else
	{
	dc.StretchBlt(0,0,SizeX,SizeY,&MemDC,0,0,128,64,SRCCOPY);
	}
	MemDC.SelectObject(pOldBitmap);

	Seiko.m_update=FALSE;

/*
	// TODO: Add your message handler code here

		int j;

		CBitmap SeikoLcd_RAM;
		CBitmap SeikoLcd_OFF;

		SeikoLcd_RAM.CreateBitmap(128,64,1,1,&Seiko.SeikoRAM);
		SeikoLcd_OFF.CreateBitmap(128,64,1,1,&Seiko.SeikoOFF);

		HBITMAP hbitmap_RAM=SeikoLcd_RAM;
		HBITMAP hbitmap_OFF=SeikoLcd_OFF;
		
		HDC hMemDC=::CreateCompatibleDC(NULL);


		if (Seiko.Seiko_Display1==TRUE)	SelectObject(hMemDC,hbitmap_RAM);
		else SelectObject(hMemDC,hbitmap_OFF);


		j=Seiko.Seiko_Z1;

		::StretchBlt(dc.m_hDC,0,0,64*2,(64-j)*2
			,hMemDC,0,j,64,64-j,NOTSRCCOPY);

		if (j!=0){
		::StretchBlt(dc.m_hDC,0,0+(64-j)*2,64*2,j*2
			,hMemDC,0,0,64,j,NOTSRCCOPY);}


		if (Seiko.Seiko_Display2==TRUE)	SelectObject(hMemDC,hbitmap_RAM);
		else SelectObject(hMemDC,hbitmap_OFF);


		j=Seiko.Seiko_Z2;

		::StretchBlt(dc.m_hDC,0+64*2,0,64*2,(64-j)*2
			,hMemDC,64,j,64,64-j,NOTSRCCOPY);

		if (j!=0){
		::StretchBlt(dc.m_hDC,0+64*2,0+(64-j)*2,64*2,j*2
			,hMemDC,64,0,64,j,NOTSRCCOPY);}

		SelectObject(hMemDC,hbitmap_RAM);
		SeikoLcd_RAM.DeleteObject();
		SelectObject(hMemDC,hbitmap_OFF);
		SeikoLcd_OFF.DeleteObject();

		::DeleteDC(hMemDC);
*/
	// Do not call CDialog::OnPaint() for painting messages
}

void CSeikoDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (Seiko.m_update==TRUE) Invalidate(FALSE);

	CDialog::OnTimer(nIDEvent);
}

void CSeikoDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	ClientToScreen(&point);

	CMenu* pSubMenu=pMenu->GetSubMenu(0);

	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);


	CDialog::OnRButtonDown(nFlags, point);
}

void CSeikoDlg::OnMenuDoubleSize() 
{
	// TODO: Add your command handler code here
	if (SizeX==128)
	{
		SizeX=256;
		SizeY=128;
	
		pMenu->CheckMenuItem(ID_MENU_DOUBLE_SIZE,MF_CHECKED);
	}
	else
	{
		SizeX=128;
		SizeY=64;
	
		pMenu->CheckMenuItem(ID_MENU_DOUBLE_SIZE,MF_UNCHECKED);

	}
	ResizeDialog();
	SaveConfiguration();
	Invalidate(FALSE);
	Seiko.m_update=TRUE;
}

void CSeikoDlg::OnMenuInvertcolors() 
{
	// TODO: Add your command handler code here
	if (InvertColors==FALSE)
	{
		pMenu->CheckMenuItem(ID_MENU_INVERTCOLORS,MF_CHECKED);
		InvertColors=TRUE;
	}
	else
	{
		pMenu->CheckMenuItem(ID_MENU_INVERTCOLORS,MF_UNCHECKED);
		InvertColors=FALSE;
	}

	SaveConfiguration();
	Seiko.m_update=TRUE;
}

void CSeikoDlg::ResizeDialog()
{
	CRect r;

	GetWindowRect(&r);

	r.right=r.left+SizeX+6;
	r.bottom=r.top+SizeY+22;

	MoveWindow (&r,TRUE);
}

void CSeikoDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg mydlg;
	mydlg.DoModal();
}


void CSeikoDlg::SaveConfiguration()
{
	char szDeviceName[20]="Seiko G1216B1N000  ";
	szDeviceName[20]=0;
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];
	int i;

	for (i=0;i<256;i++)	szIOMap[i]=0;
	for (i=0;i<5;i++) szIRQMap[i]=0;

	szIOMap[Seiko.m_instr_port]=3;
	szIOMap[Seiko.m_data_port]=3;
	szIOMap[Seiko.m_cs_port]=2;

	BYTE m_double_size,m_invert_colors;
	if (SizeX==128) m_double_size=0; else m_double_size=1;
	if (InvertColors==FALSE) m_invert_colors=0; else m_invert_colors=1;


	szData[0]=Seiko.m_instr_port;
	szData[1]=Seiko.m_data_port;
	szData[2]=Seiko.m_cs_port;
	szData[3]=m_double_size;
	szData[4]=m_invert_colors;


	CFile cf;
	
	cf.Open(ExecutablePath+"\\"+sz_AppFileName+".cfg",CFile::modeCreate | CFile::modeWrite);
	cf.Write(szDeviceName,20);
	cf.Write(szIOMap,256);
	cf.Write(szIRQMap,5);
	cf.Write(szData,5);
	cf.Close();
}

void CSeikoDlg::LoadConfiguration()
{
	char szDeviceName[20];
	char szIOMap[256];
	char szIRQMap[5];
	char szData[5];
	CFile cf;
	BYTE m_double_size,m_invert_colors;

	if (cf.Open(ExecutablePath+"\\"+sz_AppFileName+".cfg",CFile::modeRead))
	{

		cf.Read(szDeviceName,20);
		cf.Read(szIOMap,256);
		cf.Read(szIRQMap,5);
		cf.Read(szData,5);
		cf.Close();

		Seiko.m_instr_port=szData[0];
		Seiko.m_data_port=szData[1];
		Seiko.m_cs_port=szData[2];
		m_double_size=szData[3];
		m_invert_colors=szData[4];

		if (m_double_size==0) 
		{
			SizeX=128;SizeY=64;
		}
		else
		{
			SizeX=256;SizeY=128;
		}


		if (m_invert_colors==0)
		{
			InvertColors=FALSE;
		}
		else
		{
			InvertColors=TRUE;
		}
	
	}
	else
	{
	SizeX=256;SizeY=128;
	InvertColors=FALSE;

	Seiko.m_instr_port=128;
	Seiko.m_data_port=129;
	Seiko.m_cs_port=130;

	SaveConfiguration();
	}

}

void CSeikoDlg::ExternalConfig()
{
	SetIOAddress();
	SaveConfiguration();
}


void CSeikoDlg::SetIOAddress()
{
	CSAddrDlg mydlg;
	mydlg.m_edit_instr=Seiko.m_instr_port;
	mydlg.m_edit_data=Seiko.m_data_port;
	mydlg.m_edit_cs=Seiko.m_cs_port;

	mydlg.DoModal();

	Seiko.m_instr_port=mydlg.m_edit_instr;
	Seiko.m_data_port=mydlg.m_edit_data;
	Seiko.m_cs_port=mydlg.m_edit_cs;

}

BOOL CSeikoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	
	return (IsDialogMessage(pMsg));
}
