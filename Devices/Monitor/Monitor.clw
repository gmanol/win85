; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=4
Class1=CMonitorApp
LastClass=CMonitorDlg
NewFileInclude2=#include "Monitor.h"
ResourceCount=4
NewFileInclude1=#include "stdafx.h"
Class2=CMonitorDlg
LastTemplate=CDialog
Resource1=IDD_ABOUT_DLG
Class3=CAboutDlg
Resource2=IDD_INFO_DLG
Resource3=IDD_MONITOR_DLG
Class4=CInfoDlg
Resource4=IDR_CONTEXT

[CLS:CMonitorApp]
Type=0
HeaderFile=Monitor.h
ImplementationFile=Monitor.cpp
Filter=N
LastObject=CMonitorApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_MONITOR_DLG]
Type=1
Class=CMonitorDlg
ControlCount=0

[CLS:CMonitorDlg]
Type=0
HeaderFile=MonitorDlg.h
ImplementationFile=MonitorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MENU_INFO
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

[MNU:IDR_CONTEXT]
Type=1
Class=?
Command1=ID_MENU_CLEAR
Command2=ID_MENU_INFO
Command3=ID_MENU_ABOUT
CommandCount=3

[DLG:IDD_INFO_DLG]
Type=1
Class=CInfoDlg
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CInfoDlg]
Type=0
HeaderFile=InfoDlg.h
ImplementationFile=InfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInfoDlg
VirtualFilter=dWC

[DLG:IDD_ABOUT_DLG]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177283

