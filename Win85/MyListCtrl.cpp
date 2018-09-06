// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Win85.h"
#include "MyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, OnSetfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void CMyListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION i;
	int k;

	i=GetFirstSelectedItemPosition();

	if (i!=NULL)
	{
		
    k = GetNextSelectedItem(i);

  
	if (CWin85App::gDeviceStatus[k]==FALSE)
		{
	// load device

	    CWin85App::mylib[k]=LoadLibrary(CWin85App::gDevicesFilenames[k]+".d85");
		CWin85App::gDeviceWrite[k]=(WRITEPROC) GetProcAddress(CWin85App::mylib[k],"gWrite");
		CWin85App::gDeviceRead[k]=(READPROC) GetProcAddress(CWin85App::mylib[k],"gRead");
		CWin85App::gDeviceConfig[k]=(CONFIGPROC) GetProcAddress(CWin85App::mylib[k],"gConfigure");
		CWin85App::gShowWindow[k]=(SHOWPROC) GetProcAddress(CWin85App::mylib[k],"gShowWindow");
		CWin85App::gHideWindow[k]=(HIDEPROC) GetProcAddress(CWin85App::mylib[k],"gHideWindow");
		CWin85App::gInitIRQ[k]=(INITPROC) GetProcAddress(CWin85App::mylib[k],"gInitializeIRQ");
		CWin85App::gDeviceReset[k]=(RESETPROC) GetProcAddress(CWin85App::mylib[k],"gReset");

		CWin85App::gDialogMessage[k]=(DLGMSGPROC) GetProcAddress(CWin85App::mylib[k],"gDialogMessage");

		CWin85App::gShowWindow[k]();

		CWin85App::gInitIRQ[k](&CWin85App::gIRQMap[0]);

		CWin85App::gDeviceStatus[k]=TRUE;

		AddDevice(k);

		RefreshList();
		SetItemText(k,1,"Loaded");
	
		}
	else
		{
	// unload device

		CWin85App::gDeviceStatus[k]=FALSE;
		RemoveDevice(k);
		SetItemText(k,1,"Waiting");
		if (FreeLibrary(CWin85App::mylib[k])==0) AfxMessageBox("unload error");
		}

	}

	*pResult = 0;
}


void CMyListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	POSITION i;
	int k;
	i=GetFirstSelectedItemPosition();

	if (i!=NULL)
	{
	
    k = GetNextSelectedItem(i);

	if (CWin85App::gDeviceStatus[k]==FALSE)
	{
		CWin85App::mylib[k]=LoadLibrary(CWin85App::gDevicesFilenames[k]+".d85");
		CWin85App::gDeviceWrite[k]=(WRITEPROC) GetProcAddress(CWin85App::mylib[k],"gWrite");
		CWin85App::gDeviceRead[k]=(READPROC) GetProcAddress(CWin85App::mylib[k],"gRead");
		CWin85App::gDeviceConfig[k]=(CONFIGPROC) GetProcAddress(CWin85App::mylib[k],"gConfigure");
		CWin85App::gDeviceStatus[k]=TRUE;

		CWin85App::gDeviceConfig[k]();

		FreeLibrary(CWin85App::mylib[k]);
		CWin85App::gDeviceStatus[k]=FALSE;
		RefreshList();
	}
	else
	{
		CWin85App::gDeviceConfig[k]();
		RefreshList();
		RemoveDevice(k);
		AddDevice(k);
	}
	}


	*pResult = 0;
}

void CMyListCtrl::RemoveDevice(int index)
{
	int k,j;

	k=index;

		for (j=0;j<256;j++)
			{
			if (CWin85App::gRIOMap[j]==k) CWin85App::gRIOMap[j]=-1;
			if (CWin85App::gWIOMap[j]==k) CWin85App::gWIOMap[j]=-1;
			}

		for (j=0;j<5;j++)
		{
			if (CWin85App::gIRQMap[j]==k) CWin85App::gIRQMap[j]=-1;
		}

}

void CMyListCtrl::AddDevice(int index)
{
	CFile cf;
	char szDeviceName[20];
	char szIOMap[256];
	char szIRQMap[5];

	int k,j;

	k=index;

		
		if (cf.Open(CWin85App::gDevicesFilenames[k]+".cfg",CFile::modeRead))
		{
		cf.Read(szDeviceName,20);
		cf.Read(szIOMap,256);
		cf.Read(szIRQMap,5);
		cf.Close();
		}

		for (j=0;j<256;j++)
		{
			if ((szIOMap[j] & 1)==1)
			{
				CWin85App::gRIOMap[j]=k;
			}
			if ((szIOMap[j] & 2)==2)
			{
				CWin85App::gWIOMap[j]=k;
			}
		}

		for (j=0;j<5;j++)
		{
//			if (szIRQMap[j]==1) CWin85App::gIRQMap[j]=k;
		}

}

void CMyListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION i;
	int k;
	i=GetFirstSelectedItemPosition();

	if (i!=NULL)
	{
		
    k = GetNextSelectedItem(i);
	if (CWin85App::gDeviceStatus[k]!=FALSE)
	{
		CWin85App::gShowWindow[k]();
	}

	}
	
	*pResult = 0;
}

void CMyListCtrl::OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	RefreshList();

	*pResult = 0;
}

void CMyListCtrl::RefreshList()
{
	CFile cf;
	char szDeviceName[20];
	char szIOMap[256];
	char szIRQMap[5];
	CString s;

	s=CWin85App::gExecutablePath+"\\Devices\\";

	DeleteAllItems();

	CFileFind finder;
    BOOL bWorking = finder.FindFile(s+"*.d85");

	CString x,f;

	int k,j;
	char txt[10];

	k=0;
    while (bWorking)
    {
      bWorking = finder.FindNextFile();	  

	  CWin85App::gDevicesFilenames[k]=s+finder.GetFileTitle();

	  f=s+finder.GetFileTitle()+".cfg";

	if (cf.Open(f,CFile::modeRead))
	{
		cf.Read(szDeviceName,20);
		cf.Read(szIOMap,256);
		cf.Read(szIRQMap,5);
		cf.Close();

		x=szDeviceName;x.TrimRight(" ");
		InsertItem(k,x);

		if (CWin85App::gDeviceStatus[k]==TRUE)
		{
		SetItemText(k,1,"Loaded");
		}
		else
		{
		SetItemText(k,1,"Waiting");
		}

			x="";
			for (j=0;j<256;j++)
			{
				if (szIOMap[j]!=0)
				{
					x=x+itoa(j,txt,16)+"h,";
				}
			}

		x=x.Mid(0,x.GetLength()-1);

		SetItemText(k,2,x);

			x="";
			if (szIRQMap[0]==1) x=x+"TRAP,";
			if (szIRQMap[1]==1) x=x+"RST7.5,";
			if (szIRQMap[2]==1) x=x+"RST6.5,";
			if (szIRQMap[3]==1) x=x+"RST5.5,";
			if (szIRQMap[0]==1) x=x+"INTR,";
		x=x.Mid(0,x.GetLength()-1);

		if (x.GetLength()==0) x="-";

		SetItemText(k,3,x);

  		k++;
	}
	else 
	{
		x=finder.GetFileTitle()+".d85";
		x.TrimRight(" ");
		InsertItem(k,x);

		if (CWin85App::gDeviceStatus[k]==TRUE)
		{
		SetItemText(k,1,"Loaded");
		}

		else
		{
		SetItemText(k,1,"Waiting");
		}

		x="-";

		SetItemText(k,2,x);
		SetItemText(k,3,x);

  		k++;
	}

	}


	CWin85App::gNumOfDevices=k;
}
