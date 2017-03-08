; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CQKDControllerDlg
LastTemplate=CScrollBar
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "qkdcontroller.h"
LastPage=0

ClassCount=5
Class1=CQKDControllerApp
Class2=CAboutDlg
Class3=CQKDControllerDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class4=CQKDPhaseControllDlg
Resource2=IDD_QKDCONTROLLER_DIALOG
Class5=PMW
Resource3=IDD_DIALOG1

[CLS:CQKDControllerApp]
Type=0
BaseClass=CWinApp
HeaderFile=QKDController.h
ImplementationFile=QKDController.cpp
Filter=D
LastObject=CQKDControllerApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=QKDControllerDlg.cpp
ImplementationFile=QKDControllerDlg.cpp
Filter=D
LastObject=CAboutDlg

[CLS:CQKDControllerDlg]
Type=0
BaseClass=CDialog
HeaderFile=QKDControllerDlg.h
ImplementationFile=QKDControllerDlg.cpp
LastObject=CQKDControllerDlg
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_QKDCONTROLLER_DIALOG]
Type=1
Class=CQKDControllerDlg
ControlCount=35
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,static,1342308352
Control4=IDC_USBInfo,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_MasterMode,button,1342242816
Control12=IDC_SlaveMode,button,1073807360
Control13=IDC_SendData,button,1342242816
Control14=IDC_ReadData,button,1342242816
Control15=IDC_EDIT1,edit,1350631552
Control16=IDC_EDIT2,edit,1350631552
Control17=IDC_EDIT3,edit,1350631552
Control18=IDC_EDIT4,edit,1350631552
Control19=IDC_EDIT5,edit,1350631552
Control20=IDC_EDIT6,edit,1350631552
Control21=IDC_STATIC,static,1342308864
Control22=IDC_STATIC,static,1342308864
Control23=IDC_STATIC,static,1342308864
Control24=IDC_STATIC,static,1342308864
Control25=IDC_STATIC,static,1342308864
Control26=IDC_STATIC,static,1342308864
Control27=IDC_State,static,1350696960
Control28=IDC_Scor_PMW,scrollbar,1342177280
Control29=IDC_Scor_Delay1,scrollbar,1342177280
Control30=IDC_Scor_Delay2,scrollbar,1342177280
Control31=IDC_Scor_AD1,scrollbar,1342177280
Control32=IDC_Scor_AD3,scrollbar,1342177280
Control33=IDC_Scor_AD2,scrollbar,1342177280
Control34=IDC_STATIC2,static,1342308352
Control35=IDC_BUTTON1,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CQKDPhaseControllDlg]
Type=0
HeaderFile=QKDPhaseControllDlg.h
ImplementationFile=QKDPhaseControllDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CQKDPhaseControllDlg

[CLS:PMW]
Type=0
HeaderFile=PMW.h
ImplementationFile=PMW.cpp
BaseClass=CScrollBar
Filter=W
LastObject=IDC_SCROLLBAR1

