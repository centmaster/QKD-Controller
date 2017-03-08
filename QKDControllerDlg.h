// QKDControllerDlg.h : header file
//

#if !defined(AFX_QKDCONTROLLERDLG_H__FC616C0C_128B_4FF0_8D6C_6A6F0D91301D__INCLUDED_)
#define AFX_QKDCONTROLLERDLG_H__FC616C0C_128B_4FF0_8D6C_6A6F0D91301D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CyAPI.h"

/////////////////////////////////////////////////////////////////////////////
// CQKDControllerDlg dialog

class CQKDControllerDlg : public CDialog
{
// Construction
public:
	CWinThread *Phasemodulator;
	CQKDControllerDlg(CWnd* pParent = NULL);	// standard constructor

 //   CCyUSBDevice *QKDController;

	CCyUSBEndPoint *OutEndpt;
	CCyUSBEndPoint *InEndpt;

	CCyControlEndPoint  *ept;	//¿ØÖÆ¶Ëµã

	CWinThread *QKDThread;
	CWinThread *ChatThread;

// Dialog Data
	//{{AFX_DATA(CQKDControllerDlg)
	enum { IDD = IDD_QKDCONTROLLER_DIALOG };
	CScrollBar	m_Scor_AD3;
	CScrollBar	m_Scor_AD2;
	CScrollBar	m_Scor_AD1;
	CScrollBar	m_Scor_Delay2;
	CScrollBar	m_Scor_Delay1;
	CScrollBar	m_Scor_PMW;
	CString	m_USB;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQKDControllerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQKDControllerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMasterMode();
	afx_msg void OnSlaveMode();
	afx_msg void OnSendData();
	afx_msg void OnReadData();
	afx_msg void OnShow(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnscanDA1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QKDCONTROLLERDLG_H__FC616C0C_128B_4FF0_8D6C_6A6F0D91301D__INCLUDED_)
