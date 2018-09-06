; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
Class1=CBASICIOApp
LastClass=CBASICIOdlg
NewFileInclude2=#include "BASICIO.h"
ResourceCount=3
NewFileInclude1=#include "stdafx.h"
Class2=CBASICIOdlg
LastTemplate=CDialog
Resource1=IDD_BASICIO_DLG
Resource2=IDD_ABOUT_DLG
Class3=CAboutDlg
Resource3=IDR_CONTEXT

[CLS:CBASICIOApp]
Type=0
HeaderFile=BASICIO.h
ImplementationFile=BASICIO.cpp
Filter=N
LastObject=CBASICIOApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_BASICIO_DLG]
Type=1
Class=CBASICIOdlg
ControlCount=15
Control1=IDC_EDIT_IN,edit,1350639617
Control2=IDC_IRQ_BUTTON_TRAP,button,1342242816
Control3=IDC_IRQ_BUTTON_RST75,button,1342242816
Control4=IDC_IRQ_BUTTON_RST65,button,1342242816
Control5=IDC_IRQ_BUTTON_RST55,button,1342242816
Control6=IDC_IRQ_BUTTON_INTR,button,1342242816
Control7=IDC_EDIT_PULSE_65,edit,1350639746
Control8=IDC_EDIT_PULSE_55,edit,1350639746
Control9=IDC_EDIT_PULSE_INTR,edit,1350639746
Control10=IDC_EDIT_INTRBUS,edit,1350631561
Control11=IDC_EDIT_OUT,edit,1350633473
Control12=IDC_STATIC,static,1342308353
Control13=IDC_STATIC,static,1342308353
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352

[CLS:CBASICIOdlg]
Type=0
HeaderFile=BASICIOdlg.h
ImplementationFile=BASICIOdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBASICIOdlg
VirtualFilter=dWC

[DLG:IDD_ABOUT_DLG]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177294

[MNU:IDR_CONTEXT]
Type=1
Class=?
Command1=ID_MENU_ABOUT
CommandCount=1

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

