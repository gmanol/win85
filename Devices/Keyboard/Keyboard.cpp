// Keyboard.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Keyboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKeyboardApp

BEGIN_MESSAGE_MAP(CKeyboardApp, CWinApp)
	//{{AFX_MSG_MAP(CKeyboardApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardApp construction

CKeyboardApp::CKeyboardApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeyboardApp object

CKeyboardApp theApp;

BOOL CKeyboardApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	my_dlg.Create(IDD_KEYBOARD_DLG,NULL);

	return CWinApp::InitInstance();
}

void gWrite(BYTE port,BYTE data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.my_dlg.Device.Write(port,data);
}

BYTE gRead(BYTE port)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return(theApp.my_dlg.Device.Read(port));
}

void gConfigure()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.my_dlg.ExternalConfig();
}

void gShowWindow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.my_dlg.ShowWindow(SW_SHOW);
}

void gHideWindow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.my_dlg.ShowWindow(SW_HIDE);
}

void gInitializeIRQ(int* IRQtable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.my_dlg.Device.m_pIRQPenting=IRQtable;
}

void gReset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.my_dlg.Device.Reset();
}

BOOL gDialogMessage(MSG *pMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (theApp.PreTranslateMessage(pMsg));
}
