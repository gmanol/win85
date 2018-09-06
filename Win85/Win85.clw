; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Win85.h"
LastPage=0

ClassCount=20
Class1=CWin85App
Class2=CWin85Doc
Class3=CInputDlg
Class4=CMainFrame

ResourceCount=24
Resource1=IDR_RUNTOOLBAR (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDR_WIN85TYPE
Resource7=IDR_WIN85TYPE1 (English (U.S.))
Resource8=IDR_HARDWARETOOLBAR
Resource9=IDD_WIN85_FORM (English (U.S.))
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_FORMVIEW_MEMORY (English (U.S.))
Resource5=IDD_SPEED_DLG
Resource6=IDR_MAINFRAME2 (English (U.S.))
Resource10=IDD_ABOUTBOX (English (U.S.))
Class7=CAssemblyDlg
Resource11=IDR_BREAKPOINTSTOOLBAR (English (U.S.))
Class8=CDevicesDlg
Class9=CMyListCtrl
Resource12=IDD_CONNECT_DIALOG
Resource13=IDD_FORMVIEW_STACK (English (U.S.))
Class10=CWaitDlg
Resource14=IDR_MAINFRAME (English (U.S.))
Class11=CBreakPointsDlg
Class12=CBreakPointsCtrl
Resource15=IDD_WAIT_DIALOG
Class13=CMemoryCfgDlg
Resource16=IDR_WIN85TYPE (English (U.S.))
Class14=CSpeedDlg
Resource17=IDD_BREAKPOINTS_DLG
Resource18=IDR_RUNTOOLBAR1 (English (U.S.))
Resource19=IDD_FORMVIEW_CPU (English (U.S.))
Resource20=IDD_MEMORY_DLG
Class15=CCpuView
Class16=CMemoryView
Class17=CStackView
Class18=CRegistersView
Class19=CFlexibleSplitter
Class20=CSolidSplitter
Resource21=IDD_ASSEMBLY_DLG
Resource22=IDD_FORMVIEW_REGISTERS (English (U.S.))
Resource23=IDR_MAINFRAME1 (English (U.S.))
Resource24=IDD_INPUT_DLG

[CLS:CWin85App]
Type=0
HeaderFile=Win85.h
ImplementationFile=Win85.cpp
Filter=N
LastObject=CWin85App
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CWin85Doc]
Type=0
HeaderFile=Win85Doc.h
ImplementationFile=Win85Doc.cpp
Filter=N
LastObject=CWin85Doc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=ID_OPTIONS_SAVEASDEFAULTLAYOUT
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=Win85.cpp
ImplementationFile=Win85.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=9
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP

[MNU:IDR_WIN85TYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=22
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=16
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP

[DLG:IDD_WIN85_FORM (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177298
Control2=IDC_STATIC,static,1342177298
Control3=IDC_STATIC,static,1342177298
Control4=IDC_STATIC,static,1342177298
Control5=IDC_SCROLLBAR_CPU,scrollbar,1342177281
Control6=IDC_SCROLLBAR_DUMP,scrollbar,1342177281
Control7=IDC_SCROLLBAR_STACK,scrollbar,1342177281

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
CommandCount=3

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_TOOLBAR_RUN
Command7=ID_VIEW_TOOLBAR_BREAKPOINTS
Command8=ID_VIEW_TOOLBARS_HARDWARE
Command9=ID_VIEW_STATUS_BAR
Command10=ID_VIEW_TOOLBARS_DEVICES
Command11=ID_APP_ABOUT
CommandCount=11

[MNU:IDR_WIN85TYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_TOOLBAR_RUN
Command10=ID_VIEW_TOOLBAR_BREAKPOINTS
Command11=ID_VIEW_TOOLBARS_HARDWARE
Command12=ID_VIEW_STATUS_BAR
Command13=ID_VIEW_TOOLBARS_DEVICES
Command14=ID_VIEW_BREAKPOINTSDIALOG
Command15=ID_RUN_RUN
Command16=ID_RUN_GOTOCURSOR
Command17=ID_RUN_TRACEINTO
Command18=ID_RUN_PROGRAMRESET
Command19=ID_BREAKPOINTS_TOGGLE
Command20=ID_BREAKPOINTS_DISABLE
Command21=ID_BREAKPOINTS_AT
Command22=ID_BREAKPOINTS_DELETEALL
Command23=ID_HARDWARE_COPYBINARYTOLPT
Command24=ID_OPTIONS_MEMORYCONFIGURATION
Command25=ID_OPTIONS_EMULATIONSPEED
Command26=ID_OPTIONS_SAVEASDEFAULTLAYOUT
Command27=ID_APP_ABOUT
CommandCount=27

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_KEY_0
Command2=ID_KEY_1
Command3=ID_KEY_2
Command4=ID_KEY_3
Command5=ID_KEY_4
Command6=ID_KEY_5
Command7=ID_KEY_6
Command8=ID_KEY_7
Command9=ID_KEY_8
Command10=ID_KEY_9
Command11=ID_KEY_A
Command12=ID_KEY_B
Command13=ID_VIEW_BREAKPOINTSDIALOG
Command14=ID_KEY_C
Command15=ID_EDIT_COPY
Command16=ID_KEY_D
Command17=ID_VIEW_TOOLBARS_DEVICES
Command18=ID_KEY_E
Command19=ID_KEY_F
Command20=ID_KEY_H
Command21=ID_KEY_I
Command22=ID_KEY_J
Command23=ID_KEY_L
Command24=ID_KEY_M
Command25=ID_KEY_N
Command26=ID_FILE_NEW
Command27=ID_KEY_O
Command28=ID_FILE_OPEN
Command29=ID_KEY_P
Command30=ID_FILE_PRINT
Command31=ID_KEY_R
Command32=ID_KEY_S
Command33=ID_FILE_SAVE
Command34=ID_OPTIONS_EMULATIONSPEED
Command35=ID_EDIT_PASTE
Command36=ID_EDIT_UNDO
Command37=ID_EDIT_CUT
Command38=ID_KEY_DOWN
Command39=ID_KEY_CTRL_DOWN
Command40=ID_KEY_END
Command41=ID_KEY_CTRL_END
Command42=ID_KEY_ESC
Command43=ID_HELP
Command44=ID_CONTEXT_HELP
Command45=ID_HARDWARE_COPYBINARYTOLPT
Command46=ID_BREAKPOINTS_TOGGLE
Command47=ID_RUN_PROGRAMRESET
Command48=ID_BREAKPOINTS_AT
Command49=ID_BREAKPOINTS_DISABLE
Command50=ID_RUN_GOTOCURSOR
Command51=ID_NEXT_PANE
Command52=ID_PREV_PANE
Command53=ID_RUN_TRACEINTO
Command54=ID_RUN_RUN
Command55=ID_KEY_HOME
Command56=ID_KEY_CTRL_HOME
Command57=ID_EDIT_COPY
Command58=ID_EDIT_PASTE
Command59=ID_KEY_LEFT
Command60=ID_KEY_CTRL_LEFT
Command61=ID_KEY_PGDOWN
Command62=ID_KEY_CTRL_PGDOWN
Command63=ID_KEY_PGUP
Command64=ID_KEY_CTRL_PGUP
Command65=ID_KEY_RIGHT
Command66=ID_KEY_CTRL_RIGHT
Command67=ID_SWITCH_FOCUS
Command68=ID_SWITCH_FOCUS_BK
Command69=ID_KEY_UP
Command70=ID_KEY_CTRL_UP
Command71=ID_KEY_X
Command72=ID_EDIT_CUT
Command73=ID_EDIT_UNDO
CommandCount=73

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_REGISTER_EDIT,edit,1344276549
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[TB:IDR_RUNTOOLBAR (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_RUN_RUN
Command2=ID_RUN_GOTOCURSOR
Command3=ID_RUN_TRACEINTO
Command4=ID_RUN_PROGRAMRESET
CommandCount=4

[TB:IDR_BREAKPOINTSTOOLBAR (English (U.S.))]
Type=1
Class=?
Command1=ID_BREAKPOINTS_TOGGLE
Command2=ID_BREAKPOINTS_DISABLE
Command3=ID_BREAKPOINTS_AT
Command4=ID_BREAKPOINTS_DELETEALL
CommandCount=4

[DLG:IDD_ASSEMBLY_DLG]
Type=1
Class=CAssemblyDlg
ControlCount=3
Control1=IDC_ASSEMBLY_EDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CAssemblyDlg]
Type=0
HeaderFile=AssemblyDlg.h
ImplementationFile=AssemblyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAssemblyDlg
VirtualFilter=dWC

[DLG:IDD_CONNECT_DIALOG]
Type=1
Class=CDevicesDlg
ControlCount=1
Control1=IDC_DEVICE_LIST,SysListView32,1342242821

[CLS:CDevicesDlg]
Type=0
HeaderFile=DevicesDlg.h
ImplementationFile=DevicesDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDevicesDlg
VirtualFilter=dWC

[CLS:CMyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CMyListCtrl
VirtualFilter=FWC

[TB:IDR_HARDWARETOOLBAR]
Type=1
Class=?
Command1=ID_HARDWARE_COPYBINARYTOLPT
CommandCount=1

[DLG:IDD_WAIT_DIALOG]
Type=1
Class=CWaitDlg
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CWaitDlg]
Type=0
HeaderFile=WaitDlg.h
ImplementationFile=WaitDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CWaitDlg

[DLG:IDD_BREAKPOINTS_DLG]
Type=1
Class=CBreakPointsDlg
ControlCount=1
Control1=IDC_BREAKPOINTS_LIST,SysListView32,1342242821

[CLS:CBreakPointsDlg]
Type=0
HeaderFile=BreakPointsDlg.h
ImplementationFile=BreakPointsDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBreakPointsDlg
VirtualFilter=dWC

[CLS:CBreakPointsCtrl]
Type=0
HeaderFile=BreakPointsCtrl.h
ImplementationFile=BreakPointsCtrl.cpp
BaseClass=CListCtrl
Filter=W
LastObject=CBreakPointsCtrl

[DLG:IDD_MEMORY_DLG]
Type=1
Class=CMemoryCfgDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MEMORY_CFGLIST,SysListView32,1350631425

[CLS:CMemoryCfgDlg]
Type=0
HeaderFile=MemoryCfgDlg.h
ImplementationFile=MemoryCfgDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMemoryCfgDlg
VirtualFilter=dWC

[DLG:IDD_SPEED_DLG]
Type=1
Class=CSpeedDlg
ControlCount=4
Control1=IDC_SPEED_SLIDER,msctls_trackbar32,1342242821
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308354
Control4=IDC_TURBO_CHECK,button,1342250755

[CLS:CSpeedDlg]
Type=0
HeaderFile=SpeedDlg.h
ImplementationFile=SpeedDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSpeedDlg
VirtualFilter=dWC

[DLG:IDD_FORMVIEW_CPU (English (U.S.))]
Type=1
Class=CCpuView
ControlCount=2
Control1=IDC_STATIC,static,1073741824
Control2=IDC_CPU_SCROLLBAR,scrollbar,1342177281

[DLG:IDD_FORMVIEW_REGISTERS (English (U.S.))]
Type=1
Class=CRegistersView
ControlCount=1
Control1=IDC_STATIC,static,1073872896

[DLG:IDD_FORMVIEW_MEMORY (English (U.S.))]
Type=1
Class=CMemoryView
ControlCount=2
Control1=IDC_STATIC,static,1073872896
Control2=IDC_MEMORY_SCROLLBAR,scrollbar,1342177281

[DLG:IDD_FORMVIEW_STACK (English (U.S.))]
Type=1
Class=CStackView
ControlCount=2
Control1=IDC_STATIC,static,1073872896
Control2=IDC_STACK_SCROLLBAR,scrollbar,1342177281

[CLS:CCpuView]
Type=0
HeaderFile=CpuView.h
ImplementationFile=CpuView.cpp
BaseClass=CFormView
Filter=D
LastObject=CCpuView
VirtualFilter=VWC

[CLS:CMemoryView]
Type=0
HeaderFile=MemoryView.h
ImplementationFile=MemoryView.cpp
BaseClass=CFormView
Filter=D
LastObject=CMemoryView
VirtualFilter=VWC

[CLS:CStackView]
Type=0
HeaderFile=StackView.h
ImplementationFile=StackView.cpp
BaseClass=CFormView
Filter=D
LastObject=CStackView
VirtualFilter=VWC

[CLS:CRegistersView]
Type=0
HeaderFile=RegistersView.h
ImplementationFile=RegistersView.cpp
BaseClass=CFormView
Filter=D
LastObject=CRegistersView
VirtualFilter=VWC

[CLS:CSolidSplitter]
Type=0
HeaderFile=SolidSplitter.h
ImplementationFile=SolidSplitter.cpp
BaseClass=CSplitterWnd
Filter=W
LastObject=CSolidSplitter
VirtualFilter=pWC

[CLS:CFlexibleSplitter]
Type=0
HeaderFile=FlexibleSplitter.h
ImplementationFile=FlexibleSplitter.cpp
BaseClass=CSplitterWnd
Filter=T
LastObject=CFlexibleSplitter
VirtualFilter=pWC

[DLG:IDD_INPUT_DLG]
Type=1
Class=CInputDlg
ControlCount=3
Control1=IDC_INPUT_EDIT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CInputDlg]
Type=0
HeaderFile=InputDlg.h
ImplementationFile=InputDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputDlg
VirtualFilter=dWC

[MNU:IDR_WIN85TYPE1 (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_TOOLBAR_RUN
Command17=ID_VIEW_TOOLBAR_BREAKPOINTS
Command18=ID_VIEW_TOOLBARS_HARDWARE
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_TOOLBARS_DEVICES
Command21=ID_VIEW_BREAKPOINTSDIALOG
Command22=ID_RUN_RUN
Command23=ID_RUN_GOTOCURSOR
Command24=ID_RUN_TRACEINTO
Command25=ID_RUN_STEPOVER
Command26=ID_RUN_EXECUTETO
Command27=ID_RUN_STEPOUT
Command28=ID_RUN_ANIMATE
Command29=ID_RUN_PROGRAMRESET
Command30=ID_BREAKPOINTS_TOGGLE
Command31=ID_BREAKPOINTS_DISABLE
Command32=ID_BREAKPOINTS_AT
Command33=ID_BREAKPOINTS_HARDWAREBREAKPOINT
Command34=ID_BREAKPOINTS_DELETEALL
Command35=ID_HARDWARE_COPYBINARYTOLPT
Command36=ID_OPTIONS_MEMORYCONFIGURATION
Command37=ID_OPTIONS_EMULATIONSPEED
Command38=ID_OPTIONS_SAVEPOSITION
Command39=ID_HELP_FINDER
Command40=ID_APP_ABOUT
CommandCount=40

[MNU:IDR_MAINFRAME1 (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_TOOLBAR_RUN
Command8=ID_VIEW_TOOLBAR_BREAKPOINTS
Command9=ID_VIEW_TOOLBARS_HARDWARE
Command10=ID_VIEW_STATUS_BAR
Command11=ID_VIEW_TOOLBARS_DEVICES
Command12=ID_HELP_FINDER
Command13=ID_APP_ABOUT
CommandCount=13

[TB:IDR_MAINFRAME2 (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[TB:IDR_RUNTOOLBAR1 (English (U.S.))]
Type=1
Class=?
Command1=ID_RUN_RUN
Command2=ID_RUN_GOTOCURSOR
Command3=ID_RUN_TRACEINTO
Command4=ID_RUN_STEPOVER
Command5=ID_RUN_ANIMATE
Command6=ID_RUN_PROGRAMRESET
CommandCount=6

