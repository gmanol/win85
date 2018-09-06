// Win85Doc.cpp : implementation of the CWin85Doc class
//

#include "stdafx.h"
#include "Win85.h"

#include "Win85Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWin85Doc

IMPLEMENT_DYNCREATE(CWin85Doc, CDocument)

BEGIN_MESSAGE_MAP(CWin85Doc, CDocument)
	//{{AFX_MSG_MAP(CWin85Doc)
	ON_COMMAND(ID_RUN_RUN, OnRunRun)
	ON_COMMAND(ID_RUN_TRACEINTO, OnRunTraceinto)
	ON_COMMAND(ID_VIEW_BREAKPOINTSDIALOG, OnViewBreakpointsdialog)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BREAKPOINTSDIALOG, OnUpdateViewBreakpointsdialog)
	ON_COMMAND(ID_OPTIONS_EMULATIONSPEED, OnOptionsEmulationspeed)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_EMULATIONSPEED, OnUpdateOptionsEmulationspeed)
	ON_COMMAND(ID_HARDWARE_COPYBINARYTOLPT, OnHardwareCopybinarytolpt)
	ON_COMMAND(ID_RUN_PROGRAMRESET, OnRunProgramreset)
	ON_COMMAND(ID_RUN_ANIMATE, OnRunAnimate)
	ON_COMMAND(ID_RUN_GOTOCURSOR, OnRunGotocursor)
	ON_UPDATE_COMMAND_UI(ID_RUN_RUN, OnUpdateRunRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWin85Doc construction/destruction

CWin85Doc::CWin85Doc()
{
	// TODO: add one-time construction code here

	int i;
	for (i=0;i<0x10000;i++)
	{
	BreakPoints[i]=0;
	BreakPointsHits[i]=0;
	}

	m_BreakPointsDlg.Create(IDD_BREAKPOINTS_DLG,NULL);

	m_SpeedDlg.Create(IDD_SPEED_DLG,NULL);
	m_SpeedDlg.m_slider.SetPos(16000);

	m_trace=FALSE;
	m_Running=FALSE;

	m_TextColor=RGB(0,0,0);
	m_TextLightColor=RGB(255,255,255);
	m_ROMTextColor=RGB(70,70,70);
	
	m_BarColor=RGB(0,0,192);
	m_BarTextColor=RGB(200,200,80);

	m_BarColorDisable=RGB(150,150,150);
	m_BarTextColorDisable=RGB(0,0,0);
	
	m_BreakPointColor=RGB(192,0,0);
	m_BreakPointTextColor=RGB(200,200,80);

	m_BreakPointDisableColor=RGB(122,122,122);
	m_BreakPointDisableTextColor=RGB(0,0,0);

	m_Relocate_Bar=FALSE;
	m_Hold=FALSE;
}

CWin85Doc::~CWin85Doc()
{
}


BOOL CWin85Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWin85Doc serialization

void CWin85Doc::Serialize(CArchive& ar)
{
		int i,length;
		BYTE b;

		CFile* myfile;
		myfile=ar.GetFile();
		length=myfile->GetLength();

		
		if (length>0x10000) length=0x10000;

	if (ar.IsStoring())
	{

		// TODO: add storing code here
		for (i=0;i<8192;i++)
		{
		ar << i8085.Memory.Peek(i);
		}

	}
	else
	{
		// TODO: add loading code here

		for (i=0;i<length;i++)
		{
		ar >> b;
		i8085.Memory.ForcePoke(i,b);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWin85Doc diagnostics

#ifdef _DEBUG
void CWin85Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWin85Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWin85Doc commands


void CWin85Doc::OnViewBreakpointsdialog() 
{
	// TODO: Add your command handler code here
	m_BreakPointsDlg.ShowWindow((m_BreakPointsDlg.GetStyle() & WS_VISIBLE)==0);	
	
	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos);
	pView->SetFocus();

    CString sTitle = GetTitle() + " BreakPoints";
	m_BreakPointsDlg.SetWindowText(sTitle);

}

void CWin85Doc::OnUpdateViewBreakpointsdialog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_BreakPointsDlg.GetStyle() & WS_VISIBLE);

}

void CWin85Doc::OnOptionsEmulationspeed() 
{
	// TODO: Add your command handler code here
	m_SpeedDlg.ShowWindow((m_SpeedDlg.GetStyle() & WS_VISIBLE)==0);	

	POSITION pos = GetFirstViewPosition();
	CView* pView = GetNextView(pos);
	pView->SetFocus();

	CString sTitle = GetTitle() + " Emulation Speed";
	m_SpeedDlg.SetWindowText(sTitle);

}

void CWin85Doc::OnUpdateOptionsEmulationspeed(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_SpeedDlg.GetStyle() & WS_VISIBLE);
}

void CWin85Doc::OnHardwareCopybinarytolpt() 
{
	// TODO: Add your command handler code here
	CWaitDlg* pMy_dlg=new CWaitDlg;

	pMy_dlg->Create(IDD_WAIT_DIALOG,NULL);

	CFile myfile;
	int i;
	char szBuffer[1];

	if (myfile.Open("LPT1:",CFile::modeWrite))
	{
		for (i=0;i<8192;i++)
		{
		szBuffer[0]=i8085.Memory.Peek(i);
		myfile.Write(szBuffer,1);
		}
	}

	myfile.Close();
	pMy_dlg->ShowWindow(SW_HIDE);	
}

void CWin85Doc::RefreshBreakpointsList()
{
	int i,j,h;
	CString x;
	char txt[10];
	BYTE b;

	m_BreakPointsDlg.m_BreakPointsCtrl.DeleteAllItems();

	for (i=0;i<0x10000;i++)
	{
		b=BreakPoints[i];
		if (b!=0)
		{
		x=CWin85App::Word2Hex(i);
		j=m_BreakPointsDlg.m_BreakPointsCtrl.InsertItem(10000,x);

		if (b==1) x="Active";
		if (b==2) x="Disabled";
		m_BreakPointsDlg.m_BreakPointsCtrl.SetItemText(j,1,x);
	
		h=BreakPointsHits[i];
		x=itoa(h,txt,10);
		m_BreakPointsDlg.m_BreakPointsCtrl.SetItemText(j,2,x);
		}
	}
}

void CWin85Doc::OnRunProgramreset() 
{
	// TODO: Add your command handler code here
	m_Hold=TRUE;
	Sleep(10);
	i8085.Reset();


	for (int i=0;i<100;i++)
	{
		if (CWin85App::gDeviceStatus[i]==TRUE) CWin85App::gDeviceReset[i]();
	}


	m_trace=TRUE;
	UpdateAllViews(NULL,0,NULL);
	m_trace=FALSE;

	m_Hold=FALSE;
}

void CWin85Doc::OnRunAnimate() 
{
	// TODO: Add your command handler code here

	UpdateAllViews(NULL,42,NULL);
}

void CWin85Doc::OnRunRun() 
{
	// TODO: Add your command handler code here

		if (m_RunState==FALSE)
		{
			m_RunState=TRUE;
			p_RunThread=AfxBeginThread(RunThread,this);
		}
		else
		{
			m_RunState=FALSE;
			UpdateAllViews(NULL,0,NULL);
			RefreshBreakpointsList();
		}
}

UINT CWin85Doc::RunThread(LPVOID pParam)
{
	CWin85Doc* pMyDoc;
	pMyDoc=(CWin85Doc*) pParam;
	DWORD i,w,s;

	pMyDoc->m_Running=TRUE;

	i=pMyDoc->i8085.clocks;


	do
	{
	if (pMyDoc->m_Hold==FALSE) pMyDoc->i8085.ExecuteNext();

	if (pMyDoc->BreakPoints[pMyDoc->i8085.PC]!=0)
	{
		pMyDoc->BreakPointsHits[pMyDoc->i8085.PC]++;
	}

	if (pMyDoc->BreakPoints[pMyDoc->i8085.PC]==1) 
	{

		pMyDoc->m_Relocate_Bar=TRUE;
		pMyDoc->m_RunState=FALSE;
		pMyDoc->RefreshBreakpointsList();
		pMyDoc->UpdateAllViews(NULL,0,NULL);
		pMyDoc->m_Relocate_Bar=FALSE;
	}

	if (pMyDoc->m_SpeedDlg.m_Turbo==FALSE)
	{

	s=pMyDoc->m_SpeedDlg.m_RunSpeed;
	w=pMyDoc->i8085.clocks-i;
	
    if (w>s) {Sleep(1);i=pMyDoc->i8085.clocks;}
	}

	} while (pMyDoc->m_RunState==TRUE);


	pMyDoc->m_Running=FALSE;
	return(0);
}

void CWin85Doc::OnRunTraceinto() 
{
	// TODO: Add your command handler code here
	m_rtn=i8085.ExecuteNext();

	m_trace=TRUE;
	UpdateAllViews(NULL,0,NULL);
	m_trace=FALSE;
}

void CWin85Doc::OnRunGotocursor() 
{
	// TODO: Add your command handler code here

	i8085.PC=CurrentCpuOffset;

	m_trace=TRUE;
	UpdateAllViews(NULL,0,NULL);
	m_trace=FALSE;
}

void CWin85Doc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class

	m_RunState=FALSE;
	do
	{
	Sleep(10);
	} while (m_Running==TRUE);

	CDocument::OnCloseDocument();
}

void CWin85Doc::OnUpdateRunRun(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_RunState==TRUE)
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}	
}


