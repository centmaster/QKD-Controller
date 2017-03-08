// QKDPhaseControllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qkdcontroller.h"
#include "QKDPhaseControllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQKDPhaseControllDlg dialog


CQKDPhaseControllDlg::CQKDPhaseControllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQKDPhaseControllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQKDPhaseControllDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQKDPhaseControllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQKDPhaseControllDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQKDPhaseControllDlg, CDialog)
	//{{AFX_MSG_MAP(CQKDPhaseControllDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQKDPhaseControllDlg message handlers
