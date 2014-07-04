; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExcel_parserDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "excel_parser.h"

ClassCount=4
Class1=CExcel_parserApp
Class2=CExcel_parserDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EXCEL_PARSER_DIALOG

[CLS:CExcel_parserApp]
Type=0
HeaderFile=excel_parser.h
ImplementationFile=excel_parser.cpp
Filter=N

[CLS:CExcel_parserDlg]
Type=0
HeaderFile=excel_parserDlg.h
ImplementationFile=excel_parserDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=excel_parserDlg.h
ImplementationFile=excel_parserDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EXCEL_PARSER_DIALOG]
Type=1
Class=CExcel_parserDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

