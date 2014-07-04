// excel_parser.h : main header file for the EXCEL_PARSER application
//

#if !defined(AFX_EXCEL_PARSER_H__FF02CF27_9D68_4632_96DF_923A60FAC3AF__INCLUDED_)
#define AFX_EXCEL_PARSER_H__FF02CF27_9D68_4632_96DF_923A60FAC3AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExcel_parserApp:
// See excel_parser.cpp for the implementation of this class
//

class CExcel_parserApp : public CWinApp
{
public:
	CExcel_parserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcel_parserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExcel_parserApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCEL_PARSER_H__FF02CF27_9D68_4632_96DF_923A60FAC3AF__INCLUDED_)
