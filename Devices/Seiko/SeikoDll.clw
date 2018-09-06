; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=4
Class1=CSeikoDllApp
LastClass=CSeikoDlg
NewFileInclude2=#include "SeikoDll.h"
ResourceCount=4
NewFileInclude1=#include "stdafx.h"
Class2=CSeikoDlg
LastTemplate=CDialog
Resource1=IDD_SEIKO_DIALOG
Resource2=IDD_SETADDR_DIALOG
Class3=CAboutDlg
Resource3=IDD_ABOUT_DIALOG
Class4=CSAddrDlg
Resource4=IDR_CONTEXT

[CLS:CSeikoDllApp]
Type=0
HeaderFile=SeikoDll.h
ImplementationFile=SeikoDll.cpp
Filter=N
LastObject=CSeikoDllApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_SEIKO_DIALOG]
Type=1
Class=CSeikoDlg
ControlCount=2
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360

[CLS:CSeikoDlg]
Type=0
HeaderFile=SeikoDlg.h
ImplementationFile=SeikoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSeikoDlg
VirtualFilter=dWC

[MNU:IDR_CONTEXT]
Type=1
Class=CSeikoDlg
Command1=ID_MENU_DOUBLE_SIZE
Command2=ID_MENU_INVERTCOLORS
Command3=ID_MENU_ABOUT
CommandCount=3

[DLG:IDD_ABOUT_DIALOG]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177283

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg
VirtualFilter=dWC

[DLG:IDD_SETADDR_DIALOG]
Type=1
Class=CSAddrDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_INSTR,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EDIT_DATA,edit,1350631552
Control6=IDC_STATIC,static,1342308864
Control7=IDC_EDIT_CS,edit,1350631552
Control8=IDC_STATIC,static,1342308864

[CLS:CSAddrDlg]
Type=0
HeaderFile=SAddrDlg.h
ImplementationFile=SAddrDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSAddrDlg
VirtualFilter=dWC

