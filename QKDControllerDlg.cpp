// QKDControllerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QKDController.h"
#include "QKDControllerDlg.h"

#include "CyAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LONG xfer=512;			//一次传输的数据量
CFile mFile;
CCyUSBDevice *QKDController;
CCyControlEndPoint  *ept;

UINT PhaseProc( LPVOID pParam )
{
	
	
	
	return 0;
	};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
    

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CQKDControllerDlg dialog

CQKDControllerDlg::CQKDControllerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQKDControllerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQKDControllerDlg)
	m_USB = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQKDControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQKDControllerDlg)
	DDX_Control(pDX, IDC_Scor_AD3, m_Scor_AD3);
	DDX_Control(pDX, IDC_Scor_AD2, m_Scor_AD2);
	DDX_Control(pDX, IDC_Scor_AD1, m_Scor_AD1);
	DDX_Control(pDX, IDC_Scor_Delay2, m_Scor_Delay2);
	DDX_Control(pDX, IDC_Scor_Delay1, m_Scor_Delay1);
	DDX_Control(pDX, IDC_Scor_PMW, m_Scor_PMW);
	DDX_Text(pDX, IDC_USBInfo, m_USB);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQKDControllerDlg, CDialog)
	//{{AFX_MSG_MAP(CQKDControllerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MasterMode, OnMasterMode)
	ON_BN_CLICKED(IDC_SlaveMode, OnSlaveMode)
	ON_BN_CLICKED(IDC_SendData, OnSendData)
	ON_BN_CLICKED(IDC_ReadData, OnReadData)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_AD1, OnShow)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, OnscanDA1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQKDControllerDlg message handlers

BOOL CQKDControllerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CFont font;
    font.CreatePointFont(480, "隶书");
     GetDlgItem(IDC_STATIC1)->SetFont(&font);
	m_Scor_PMW.SetScrollRange(0,255);
	m_Scor_Delay1.SetScrollRange(0,255);
	m_Scor_Delay2.SetScrollRange(0,255);
	m_Scor_AD1.SetScrollRange(0,255);
	m_Scor_AD2.SetScrollRange(0,255);
	m_Scor_AD3.SetScrollRange(0,255);

			//设置DA1
	

	//设置DA2

	//设置DA3

	//设置PWM

	//设置Delay1

	//设置Delay2

	QKDController  = new  CCyUSBDevice();
	
        
	if(QKDController->IsOpen())
	{   int VID,PID;
		m_USB="USB设备接入!";
	    VID = QKDController->VendorID; 
        PID  = QKDController->ProductID;
		CString crt;
		crt.Format("USB设备已接入!VID=%0X,PID=%1X",VID,PID);
		SetDlgItemText(IDC_State,crt);
		GetDlgItem(IDC_MasterMode)->EnableWindow(false);

	
	}
	else
	{
	m_USB="USB设备未接入!";
	
	SetDlgItemText(IDC_State,"USB设备未连接");
	GetDlgItem(IDC_MasterMode)->EnableWindow();
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	GetDlgItem(IDC_EDIT2)->EnableWindow(false);
	GetDlgItem(IDC_EDIT3)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT6)->EnableWindow(false);
	GetDlgItem(IDC_Scor_PMW)->EnableWindow(false);
	GetDlgItem(IDC_Scor_Delay1)->EnableWindow(false);
	GetDlgItem(IDC_Scor_Delay2)->EnableWindow(false);
	GetDlgItem(IDC_Scor_AD1)->EnableWindow(false);
	GetDlgItem(IDC_Scor_AD2)->EnableWindow(false);
	GetDlgItem(IDC_Scor_AD3)->EnableWindow(false);
	
	
		};
   Phasemodulator=AfxBeginThread(PhaseProc,this,0,0,CREATE_SUSPENDED,0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQKDControllerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQKDControllerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQKDControllerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*void CQKDControllerDlg::OnCustomdrawAd1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int DA1;float showDA1;char CDA1[10];
	DA1=m_DA1.GetPos();
	showDA1=(float)DA1*10/255;
	sprintf(CDA1, "%.2f",showDA1);

	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;

	else

	{

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x01;		//Open DA1
	buf[2]=DA1;		//数据0-255
    ept->XferData(buf,buflen);
	SetDlgItemText(IDC_EDIT1,CDA1);


	//CString str;
	//str.Format("%0.2f V",10.0/255.0*DA1);
	//SetDlgItemText(IDC_ShowDA1,str);
	};
	*pResult = 0;
}

void CQKDControllerDlg::OnCustomdrawAd2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int DA2;float showDA2; char CDA2[10];
	
	DA2=m_DA2.GetPos();
	showDA2=(float)DA2*10/255;
    sprintf(CDA2, "%.2f", showDA2);
	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;

	//控制位
	if(ept==NULL) return ;

	else

	{
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x02;		//Open DA2
	buf[2]=DA2;		//数据0-255
    ept->XferData(buf,buflen);
    SetDlgItemText(IDC_EDIT2,CDA2);
	};
	*pResult = 0;
}

void CQKDControllerDlg::OnCustomdrawAd3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int DA3;char CDA3[10];float showDA3;
	DA3=m_DA3.GetPos();
	showDA3=(float)DA3*10/255;
	 sprintf(CDA3, "%.2f", showDA3);

	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;

	else

	{

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x03;		//Open DA1
	buf[2]=DA3;		//数据0-255
    ept->XferData(buf,buflen);
	SetDlgItemText(IDC_EDIT3,CDA3);
	};

	*pResult = 0;
}

/*void CQKDControllerDlg::OnCustomdrawPwm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int PWM;char CPWM[10];
	PWM=m_PWM.GetPos();
//	showDA1=(float)DA1*2;
    sprintf(CPWM,"%d",PWM*2);
	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;

	else

	{

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x04;		//Open PWM
	buf[2]=PWM;		//数据0-255
    ept->XferData(buf,buflen);
	SetDlgItemText(IDC_EDIT4,CPWM);
	};
	*pResult = 0;
}

void CQKDControllerDlg::OnCustomdrawDelay2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int Delay2;char CDelay2[10];
	Delay2=m_Delay2.GetPos();
	//showDA1=(float)DA1*10/255;
    sprintf(CDelay2,"%d",Delay2);
	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;

	else

	{

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x06;		//Open PWM
	buf[2]=Delay2;		//数据0-255
    ept->XferData(buf,buflen);
	SetDlgItemText(IDC_EDIT6,CDelay2);
	};
	*pResult = 0;
}

/*void CQKDControllerDlg::OnCustomdrawDelay1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int Delay1;char CDelay1[10];
	Delay1=m_Delay1.GetPos();
	//showDA1=(float)DA1*10/255;
	sprintf(CDelay1,"%d",Delay1*1);

	LONG buflen =  3; 

	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;

	else

	{

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA1;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[3]; 
    ZeroMemory(buf, 3); 

	buf[0]=0xA1;
	buf[1]=0x05;		//Open PWM
	buf[2]=Delay1;		//数据0-255
    ept->XferData(buf,buflen);
	SetDlgItemText(IDC_EDIT5,CDelay1);
	};
	*pResult = 0;
}
*/
void CQKDControllerDlg::OnMasterMode() 
{
	// TODO: Add your control notification handler code here
   QKDController = new CCyUSBDevice();//m_hWnd);
	
   if( QKDController->IsOpen())
   {
	    int VID,PID;
	    VID = QKDController->VendorID; 
        PID  = QKDController->ProductID;
		CString crt;
		crt.Format("USB设备已接入!VID=%0X,PID=%1X",VID,PID);
		SetDlgItemText(IDC_State,crt);
		GetDlgItem(IDC_MasterMode)->EnableWindow(false);
   };
}

void CQKDControllerDlg::OnSlaveMode() 
{
	// TODO: Add your control notification handler code here
	//QKDController = new CCyUSBDevice(m_hWnd);
    
	int devices = QKDController->DeviceCount(); 
    int vID, pID; 

    int  d =  0; 
    do   { 
       QKDController->Open(d);    // Open automatically calls Close() if necessary 
       vID = QKDController->VendorID; 
       pID  = QKDController->ProductID; 
       d++;             
    } while ((d < devices) && (vID != 0x1981) && (pID != 0x1108));		//open Bob,从模式

	if(QKDController->IsOpen())
	{
		SetDlgItemText(IDC_USBInfo,"Bob is plus in!");
	}
	else
	{
		SetDlgItemText(IDC_USBInfo,"Bob is not plus in!");
	}
}

void CQKDControllerDlg::OnSendData()				//向USB发送调制数据，USB再将其写入FPGA中
{
  /*  unsigned long i;
     i=ResumeThread(Phasemodulator);
	if(1==i) SetDlgItemText(IDC_USBInfo,"线程启动成功");
	else 
	{ char cha[5];
	 itoa(i,cha,5);

      SetDlgItemText(IDC_USBInfo,cha);*/
//	if(0xFFFFFFFF!=ResumeThread(Phasemodulator)) SetDlgItemText(IDC_USBInfo,"线程启动成功");*/
	
	
    
	// TODO: Add your control notification handler code here
	//先发送数据，然后在发送写入FPGA的指令
/*	UCHAR  *outContext;
	LONG outlen;	//似乎要放在这里才好
	OVERLAPPED outOvLap;
	int i;
	CCyUSBEndPoint *OutEndpt;
	BOOL successout;
	outlen=xfer;
	LONG buflen =  2;

	PUCHAR outData = new UCHAR[xfer];	ZeroMemory(outData,xfer);
	outOvLap.hEvent   = CreateEvent(NULL, false, false, "CYUSB_OUT");

	for(i=0;i<512;i++)
	{
		outData[i]=i%4;//rand()%4;i%4
	}

	OutEndpt=QKDController->EndPoints[1];
	OutEndpt->Reset();
	outContext = OutEndpt->BeginDataXfer(outData,outlen,&outOvLap);
	OutEndpt->WaitForXfer(&outOvLap,1000);
	successout = OutEndpt->FinishDataXfer(outData,outlen, &outOvLap,outContext);*/

	//然后向USb发送写FPGA的指令
	LONG buflen =  2;
	ept=QKDController->ControlEndPt;

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA2;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[2]; 
    ZeroMemory(buf, 2); 

	buf[0]=0xA2;
	buf[1]=0x01;		//向FPGA写入数据
    ept->XferData(buf,buflen);
	 
}

void CQKDControllerDlg::OnReadData()				//USB将数据从FPGA中读取，并返回到计算机
{
	// TODO: Add your control notification handler code here
	//应该先发送读取FPGA指令，使数据从FPGA读入USb，然后执行返回计算机操作
	LONG buflen =  2;
	ept=QKDController->ControlEndPt;

	//控制位
	ept->Target    = TGT_DEVICE; 
    ept->ReqType   = REQ_VENDOR; 
    ept->Direction = DIR_TO_DEVICE;  
    ept->ReqCode   = 0xA2;   
    ept->Value     = 0;  
    ept->Index     = 0; 

	PUCHAR buf=new UCHAR[2]; 
    ZeroMemory(buf, 2); 

	buf[0]=0xA2;
	buf[1]=0x02;		//读取FPGA采集数据
    ept->XferData(buf,buflen);

	//可以等待一小会儿，以保证从FPGA读取完毕
	//Sleep(1000);		//仅测试

	//开始读取操作
	UCHAR  *inContext;
	LONG inlen;	//似乎要放在这里才好
	OVERLAPPED inOvLap;

	CCyUSBEndPoint *InEndpt;
	BOOL successin;
	inlen=xfer;

	PUCHAR inData = new UCHAR[xfer];	ZeroMemory(inData,xfer);
	inOvLap.hEvent   = CreateEvent(NULL, false, false, "CYUSB_IN");

	InEndpt=QKDController->EndPoints[3];
	InEndpt->Reset();
	inContext = InEndpt->BeginDataXfer(inData,inlen,&inOvLap);
	InEndpt->WaitForXfer(&inOvLap,1000);
	successin = InEndpt->FinishDataXfer(inData,inlen, &inOvLap,inContext); 

	if(successin)
	{
	//以下可以判断读写的数据，以验证程序的正确性
	
	mFile.Open("ReadQKD.txt",CFile::modeReadWrite|CFile::modeCreate);
	mFile.SeekToEnd();
	mFile.Write(inData,xfer);
	mFile.Close();
	}
	else
	{
		MessageBox("wrong!",NULL,MB_OK);
	}


}



void CQKDControllerDlg::OnShow(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}






void CQKDControllerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *PMW = this->GetDlgItem(IDC_Scor_PMW);
CWnd *Delay1 = this->GetDlgItem(IDC_Scor_Delay1);
CWnd *Delay2 = this->GetDlgItem(IDC_Scor_Delay2);
CWnd *AD1 = this->GetDlgItem(IDC_Scor_AD1);
CWnd *AD2 = this->GetDlgItem(IDC_Scor_AD2);
CWnd *AD3 = this->GetDlgItem(IDC_Scor_AD3);

	int nMin,nMax,nCurpos;
	pScrollBar->GetScrollRange(&nMin,&nMax);  //取得滚动条范围
	nCurpos=pScrollBar->GetScrollPos();          //取得当前值
	switch(nSBCode)                 //处理滚动信息
	{
	case SB_LINELEFT:                 //向左的箭头被按下
		nCurpos=nCurpos--;break;   
	case SB_LINERIGHT:
		nCurpos++;break;    //向右的箭头被按下
	case SB_THUMBTRACK:         //鼠标拖动
		nCurpos=nPos;break;
	}
	if(nCurpos>nMax)  nCurpos=nMax;
	pScrollBar->SetScrollPos(nCurpos);  //更新信息
	if (pScrollBar==PMW)
	{
	int PWM;char CPWM[10];
	PWM=nCurpos;
	//	showDA1=(float)DA1*2;
    sprintf(CPWM,"%d",nCurpos*2);
SetDlgItemText(IDC_EDIT4,CPWM);
	LONG buflen =  3; 
	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;
	
	else
		
	{
		
		//控制位
		ept->Target    = TGT_DEVICE; 
		ept->ReqType   = REQ_VENDOR; 
		ept->Direction = DIR_TO_DEVICE;  
		ept->ReqCode   = 0xA1;   
		ept->Value     = 0;  
		ept->Index     = 0; 
		
		PUCHAR buf=new UCHAR[3]; 
		ZeroMemory(buf, 3); 
		
		buf[0]=0xA1;
		buf[1]=0x04;		//Open PWM
		buf[2]=nCurpos;		//数据0-255
		ept->XferData(buf,buflen);
		
	}; }
	if (pScrollBar==Delay1)
	{
		int Delay1;char CDelay1[10];
		Delay1 =nCurpos;
		//showDA1=(float)DA1*10/255;
		sprintf(CDelay1,"%d",Delay1*5);
		SetDlgItemText(IDC_EDIT5,CDelay1);
		LONG buflen =  3; 
		
		ept=QKDController->ControlEndPt;
		if(ept==NULL) return ;
		
		else
			
		{
			
			//控制位
			ept->Target    = TGT_DEVICE; 
			ept->ReqType   = REQ_VENDOR; 
			ept->Direction = DIR_TO_DEVICE;  
			ept->ReqCode   = 0xA1;   
			ept->Value     = 0;  
			ept->Index     = 0; 
			
			PUCHAR buf=new UCHAR[3]; 
			ZeroMemory(buf, 3); 
			
			buf[0]=0xA1;
			buf[1]=0x05;		//Open PWM
			buf[2]=Delay1;		//数据0-255
			ept->XferData(buf,buflen);
			
	};
	};
	if (pScrollBar==Delay2)
	{
	int Delay2;char CDelay2[10];
	Delay2=nCurpos;
	//showDA1=(float)DA1*10/255;
    sprintf(CDelay2,"%d",Delay2*5);
	LONG buflen =  3; 
	SetDlgItemText(IDC_EDIT6,CDelay2);
	ept=QKDController->ControlEndPt;
	if(ept==NULL) return ;
	
	else
		
	{
		
		//控制位
		ept->Target    = TGT_DEVICE; 
		ept->ReqType   = REQ_VENDOR; 
		ept->Direction = DIR_TO_DEVICE;  
		ept->ReqCode   = 0xA1;   
		ept->Value     = 0;  
		ept->Index     = 0; 
		
		PUCHAR buf=new UCHAR[3]; 
		ZeroMemory(buf, 3); 
		
		buf[0]=0xA1;
		buf[1]=0x06;		//Open PWM
		buf[2]=Delay2;		//数据0-255
		ept->XferData(buf,buflen);
		
	};
	};
	if (pScrollBar==AD1)
	{
		int DA1;float showDA1;char CDA1[10];
		DA1=nCurpos;
		showDA1=(float)DA1*10/255;
		sprintf(CDA1, "%.2f",showDA1);
		SetDlgItemText(IDC_EDIT1,CDA1);
		LONG buflen =  3; 
		
		ept=QKDController->ControlEndPt;
		if(ept==NULL) return ;
		
		else
			
		{
			
			//控制位
			ept->Target    = TGT_DEVICE; 
			ept->ReqType   = REQ_VENDOR; 
			ept->Direction = DIR_TO_DEVICE;  
			ept->ReqCode   = 0xA1;   
			ept->Value     = 0;  
			ept->Index     = 0; 
			
			PUCHAR buf=new UCHAR[3]; 
			ZeroMemory(buf, 3); 
			
			buf[0]=0xA1;
			buf[1]=0x01;		//Open DA1
			buf[2]=DA1;		//数据0-255
			ept->XferData(buf,buflen);
			
			
			
			//CString str;
			//str.Format("%0.2f V",10.0/255.0*DA1);
			//SetDlgItemText(IDC_ShowDA1,str);
	};
	};
	if (pScrollBar==AD2)
	{
		int DA2;float showDA2; char CDA2[10];
		
		DA2=nCurpos;
		showDA2=(float)DA2*10/255;
		sprintf(CDA2, "%.2f", showDA2);
		LONG buflen =  3; 
		SetDlgItemText(IDC_EDIT2,CDA2);
		ept=QKDController->ControlEndPt;
		
		//控制位
		if(ept==NULL) return ;
		
		else
			
		{
			ept->Target    = TGT_DEVICE; 
			ept->ReqType   = REQ_VENDOR; 
			ept->Direction = DIR_TO_DEVICE;  
			ept->ReqCode   = 0xA1;   
			ept->Value     = 0;  
			ept->Index     = 0; 
			
			PUCHAR buf=new UCHAR[3]; 
			ZeroMemory(buf, 3); 
			
			buf[0]=0xA1;
			buf[1]=0x02;		//Open DA2
			buf[2]=DA2;		//数据0-255
			ept->XferData(buf,buflen);
			
	};
	};
	if (pScrollBar==AD3)
	{
		int DA3;char CDA3[10];float showDA3;
		DA3=nCurpos;
		showDA3=(float)DA3*10/255;
		sprintf(CDA3, "%.2f", showDA3);
		SetDlgItemText(IDC_EDIT3,CDA3);
		LONG buflen =  3; 
		
		ept=QKDController->ControlEndPt;
		if(ept==NULL) return ;
		
		else
			
		{
			
			//控制位
			ept->Target    = TGT_DEVICE; 
			ept->ReqType   = REQ_VENDOR; 
			ept->Direction = DIR_TO_DEVICE;  
			ept->ReqCode   = 0xA1;   
			ept->Value     = 0;  
			ept->Index     = 0; 
			
			PUCHAR buf=new UCHAR[3]; 
			ZeroMemory(buf, 3); 
			
			buf[0]=0xA1;
			buf[1]=0x03;		//Open DA1
			buf[2]=DA3;		//数据0-255
			ept->XferData(buf,buflen);
			
	};
	};

	//处理你想处理的东西
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CQKDControllerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CQKDControllerDlg::OnscanDA1() 
{
	// TODO: Add your control notification handler code here
		int DA1=0;
	
		while(DA1<255){
			DA1++;
		
				LONG buflen =  3; 
		PUCHAR buf=new UCHAR[3]; 

		ept=QKDController->ControlEndPt;
		if(ept==NULL) return ;
		
		else
			
		{
			
			//控制位
			ept->Target    = TGT_DEVICE; 
			ept->ReqType   = REQ_VENDOR; 
			ept->Direction = DIR_TO_DEVICE;  
			ept->ReqCode   = 0xA1;   
			ept->Value     = 0;  
			ept->Index     = 0; 
			
			
			ZeroMemory(buf, 3); 
			
			buf[0]=0xA1;
			buf[1]=0x01;		//Open DA1
			buf[2]=DA1;		//数据0-255
			ept->XferData(buf,buflen);
			
}
		}
}

