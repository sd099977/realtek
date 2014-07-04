// excel_parserDlg.h : header file
//

#if !defined(AFX_EXCEL_PARSERDLG_H__568B8F98_119A_462E_B6A6_1D32CEB9F52C__INCLUDED_)
#define AFX_EXCEL_PARSERDLG_H__568B8F98_119A_462E_B6A6_1D32CEB9F52C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExcel_parserDlg dialog

class CExcel_parserDlg : public CDialog
{
// Construction
public:
	CExcel_parserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExcel_parserDlg)
	enum { IDD = IDD_EXCEL_PARSER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcel_parserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExcel_parserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCEL_PARSERDLG_H__568B8F98_119A_462E_B6A6_1D32CEB9F52C__INCLUDED_)
