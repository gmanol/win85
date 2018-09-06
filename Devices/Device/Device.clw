; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
Class1=CDeviceApp
LastClass=CDeviceDlg
NewFileInclude2=#include "Device.h"
ResourceCount=3
NewFileInclude1=#include "stdafx.h"
Class2=CDeviceDlg
LastTemplate=CDialog
Resource1=IDD_ABOUT_DLG
Class3=CAboutDlg
Resource2=IDD_DEVICE_DLG
Resource3=IDR_CONTEXT

[CLS:CDeviceApp]
Type=0
HeaderFile=Device.h
ImplementationFile=Device.cpp
Filter=N
LastObject=CDeviceApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_DEVICE_DLG]
Type=1
Class=CDeviceDlg
ControlCount=0

[CLS:CDeviceDlg]
Type=0
HeaderFile=DeviceDlg.h
ImplementationFile=DeviceDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDeviceDlg
VirtualFilter=dWC

[DLG:IDD_ABOUT_DLG]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

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
Command1=ID_MENU_ABOUT
CommandCount=1

