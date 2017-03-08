#if !defined(AFX_QKDPHASECONTROLLDLG_H__665A3C63_94C3_4DD9_83EE_E46A08A1E1CC__INCLUDED_)
#define AFX_QKDPHASECONTROLLDLG_H__665A3C63_94C3_4DD9_83EE_E46A08A1E1CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QKDPhaseControllDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQKDPhaseControllDlg dialog

class CQKDPhaseControllDlg : public CDialog
{
// Construction
public:
	CQKDPhaseControllDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQKDPhaseControllDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQKDPhaseControllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQKDPhaseControllDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QKDPHASECONTROLLDLG_H__665A3C63_94C3_4DD9_83EE_E46A08A1E1CC__INCLUDED_)
