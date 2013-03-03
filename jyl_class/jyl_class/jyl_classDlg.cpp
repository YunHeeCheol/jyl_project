
// jyl_classDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "jyl_class.h"
#include "jyl_classDlg.h"
#include "afxdialogex.h"
#include "Setup_Dlg.h"
#include <MMSystem.h>
#pragma comment(lib, "winmm") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND hwnd;
UINT SerchPortThread(LPVOID pParam);
int FindPort(void);
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cjyl_classDlg ��ȭ ����




Cjyl_classDlg::Cjyl_classDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cjyl_classDlg::IDD, pParent)
	, Tray_Flag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_SC=70;
	m_OT=0;
	m_CAS=0;
	m_HTRoom_IP="";
	m_Grad=0;
	m_Class=0;
	TimeCount=0;
	m_Level=5;
	PreLevel=0;
	m_SOUND=0;
	memset(&DPack,0,sizeof(CDataPack));
}

void Cjyl_classDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CO2, m_color_co2);
	DDX_Control(pDX, IDC_STATIC_TEMP, m_color_temp);
	DDX_Control(pDX, IDC_STATIC_HUMI, m_color_humi);
	DDX_Control(pDX, IDC_STATIC_CO2DATA, m_color_co2data);
	DDX_Control(pDX, IDC_STATIC_TEMPDATA, m_color_tempdata);
	DDX_Control(pDX, IDC_STATIC_HUMIDATA, m_color_humidata);
	DDX_Control(pDX, IDC_STATIC_PPM, m_color_ppm);
	DDX_Control(pDX, IDC_STATIC_C, m_color_c);
	DDX_Control(pDX, IDC_STATIC_PER, m_color_per);
	DDX_Control(pDX, IDC_BUTTON_SETUP, m_button_setup);
	DDX_Control(pDX, IDC_BUTTON_TRAY, m_button_tray);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_button_exit);
}

BEGIN_MESSAGE_MAP(Cjyl_classDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &Cjyl_classDlg::OnBnClickedButtonSetup)
	ON_BN_CLICKED(IDC_BUTTON_TRAY, &Cjyl_classDlg::OnBnClickedButtonTray)
	ON_MESSAGE(TRAY_NOTIFY, OnTrayIconClick)
	ON_COMMAND(ID_TRAY_OPEN, &Cjyl_classDlg::OnTrayOpen)
	ON_COMMAND(ID_TRAY_SETUP, &Cjyl_classDlg::OnTraySetup)
	ON_COMMAND(ID_TRAY_FINISH, &Cjyl_classDlg::OnTrayFinish)
	ON_UPDATE_COMMAND_UI(ID_TRAY_ONLYTOP, &Cjyl_classDlg::OnUpdateTrayOnlytop)
	ON_WM_CTLCOLOR()
	ON_UPDATE_COMMAND_UI(ID_TRAY_AUTOSTART, &Cjyl_classDlg::OnUpdateTrayAutostart)
	ON_MESSAGE(WM_MYFINDPORT,OnFindPort)
	ON_MESSAGE(WM_MYRECEIVE,OnReceive)
	ON_MESSAGE(WM_MYCLOSE,OnClose)
	ON_MESSAGE(WM_MYSOCKCONNECT,OnSockConnect)
	ON_MESSAGE(WM_MYSOCKRECE,OnSockRece)
	ON_MESSAGE(WM_MYSOCKCLOSE,OnSockClose)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &Cjyl_classDlg::OnBnClickedButtonCancle)
END_MESSAGE_MAP()


// Cjyl_classDlg �޽��� ó����

BOOL Cjyl_classDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//���̾�α� ũ�� ����
	SetWindowPos(&wndNoTopMost,0,0,300,270,SWP_NOMOVE);

	if(m_socket.Create()){
		//MessageBox("���� Create");
	}
	else{
		//MessageBox("���� Create ����");
	}

	m_socket    .init(m_hWnd);
	serchport   .setHwnd(GetSafeHwnd());
	
	MainDlgInit();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void Cjyl_classDlg::MainDlgInit(void)
{
	//������ ũ�⸦ ����
	CRect rc;
	GetClientRect(rc);

	CRect shellrc;
	//�۾�ǥ������ �ڵ��� ����
	HWND hWndTrayWnd = ::FindWindow("Shell_TrayWnd", "");
	if(hWndTrayWnd)
	{
		::GetWindowRect(hWndTrayWnd, &shellrc);
	}

	int xr=0,yr=0;

	if(shellrc.Width()>shellrc.Height())
		yr=shellrc.Height();
	else
		xr=shellrc.Width();

	//�����츦 ������ �Ʒ��� �ɾ���
	SetWindowPos(&wndTop,(int)GetSystemMetrics(SM_CXSCREEN)-rc.Width()-xr,
		(int)GetSystemMetrics(SM_CYSCREEN)-rc.Height()-yr,0,0,SWP_NOSIZE);

	//�۾�ü
	setFont();

	//��Ų �ʱ�ȭ
	SetDlgVisual();

	//���� ���� Ŭ����
	CTransparency transparency;

	CString   tok;
	char      str[100];
	char      separater[] = " ,:";
	ifstream  SetupFile;
	
	CString   m_StrRunPath;
	TCHAR     buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	//���� ���� ���
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s\\%s",buf,FILE_SETUP);

	SetupFile.open(m_StrRunPath,ios::in);
	//������ ������ ����
	if ( SetupFile.is_open() == 0 ){
		transparency.SetTransparency((70),AfxGetMainWnd()->m_hWnd);
		return;
	}
	while(!SetupFile.eof()){
		SetupFile.getline(str,sizeof(str));
		tok = strtok( str, separater );
		if( strcmp( tok, "TransParency" )  == 0 ){
			m_SC        = atoi(strtok( NULL, separater));
			transparency.SetTransparency(m_SC,AfxGetMainWnd()->m_hWnd);
		}
		if( strcmp( tok, "OnlyTop" )       == 0 ){
			if(strcmp(strtok( NULL, separater ),"1")==0)
				m_OT    = 1;
			CSetup_Dlg dlg;
			dlg.SetOnlyTop(m_OT);
		}
		if( strcmp( tok, "AutoStart" )     == 0 )
			if(strcmp(strtok( NULL, separater ),"1")==0)
				m_CAS   = 1;
		if( strcmp( tok, "HeadTeacherIP" ) == 0 )
			m_HTRoom_IP = strtok( NULL, separater);
		if( strcmp( tok, "Grad" )          == 0 )
			m_Grad      = atoi(strtok( NULL, separater));
		if( strcmp( tok, "Class" )         == 0 )
			m_Class     = atoi(strtok( NULL, separater));
		if( strcmp( tok, "Sound" )         == 0 )
			if(strcmp(strtok( NULL, separater ),"1")==0)
				m_SOUND = 1;

	}
	SetupFile.close();
}
void Cjyl_classDlg::SetDlgVisual(void)
{

	//���̾�α� ��� �缳��
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+2, rc.top+2, rc.right-2, rc.bottom-2,15,15);
	::SetWindowRgn(m_hWnd,(HRGN)rgn, TRUE);

	//��ư�̹���
	CString m_StrRunPath;
	CString str_bkground;
	CString str_setup_n,str_setup_c;
	CString str_tray_n ,str_tray_c;
	CString str_exit_n ,str_exit_c;

	TCHAR buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s",buf);

	//��ư �̹��� ���
	str_setup_n .Format("%s\\Skin\\%s",m_StrRunPath,SETUP_NONE);
	str_setup_c .Format("%s\\Skin\\%s",m_StrRunPath,SETUP_CLICK);
	str_tray_n  .Format("%s\\Skin\\%s",m_StrRunPath,TRAY_NONE);
	str_tray_c  .Format("%s\\Skin\\%s",m_StrRunPath,TRAY_CLICK);
	str_exit_n  .Format("%s\\Skin\\%s",m_StrRunPath,EXIT_NONE);
	str_exit_c  .Format("%s\\Skin\\%s",m_StrRunPath,EXIT_CLICK);
	//��� �̹��� ���
	str_bkground.Format("%s\\Skin\\%s",m_StrRunPath,BKGROUND);

	//��ƾ �̹��� �ε�
	m_button_setup.LoadJPG(str_setup_n,str_setup_c,str_setup_n,str_setup_n);
	m_button_tray .LoadJPG(str_tray_n,str_tray_c,str_tray_n,str_tray_n);
	m_button_exit .LoadJPG(str_exit_n,str_exit_c,str_exit_n,str_exit_n);
	//��� �̹��� �ε�
	CSize mSize;
	DWORD fSize;
	m_bmTool.LoadPictureFile(NULL,str_bkground, &m_bgImage, mSize, fSize);

	
	CRect* rect;
	int   width,height;
	rect   = &m_button_setup.getSize();
	width  = rect->Width();
	height = rect->Height();

	//��ư,���ڿ� ��ġ �籸��
	GetDlgItem(IDC_BUTTON_SETUP)	->MoveWindow(225,5,width,height,FALSE);
	GetDlgItem(IDC_BUTTON_TRAY)		->MoveWindow(245,5,width,height,FALSE);
	GetDlgItem(IDC_BUTTON_EXIT)		->MoveWindow(265,5,width,height,FALSE);
	GetDlgItem(IDC_STATIC_CO2)		->MoveWindow(140,30,30,20,FALSE);
	GetDlgItem(IDC_STATIC_TEMP)		->MoveWindow(55,150,30,20,FALSE);
	GetDlgItem(IDC_STATIC_HUMI)		->MoveWindow(185,150,30,20,FALSE);
	GetDlgItem(IDC_STATIC_CO2DATA)	->MoveWindow(50,50,200,90,FALSE);
	GetDlgItem(IDC_STATIC_TEMPDATA)	->MoveWindow(20,170,100,70,FALSE);
	GetDlgItem(IDC_STATIC_HUMIDATA)	->MoveWindow(150,170,100,70,FALSE);
	GetDlgItem(IDC_STATIC_PPM)		->MoveWindow(252,119,40,20,FALSE);
	GetDlgItem(IDC_STATIC_C)		->MoveWindow(120,225,20,20,FALSE);
	GetDlgItem(IDC_STATIC_PER)		->MoveWindow(252,223,20,20,FALSE);
}

void Cjyl_classDlg::setFont(void)
{
	//�۲� ����, �۲� �ʺ�, ����, ȸ������, ����, ����Ӳ�, ����, ��Ҽ�, ���� ��Ʈ, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, �۲� �̸�
	m_static_co2     .CreateFont(17,7,0,0,700,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_temp    .CreateFont(15,6,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_humi    .CreateFont(15,6,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_co2data .CreateFont(70,25,0,0,700,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_tempdata.CreateFont(50,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_humidata.CreateFont(50,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_ppm     .CreateFont(21,8,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_c       .CreateFont(20,10,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_static_per     .CreateFont(20,10,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	

	GetDlgItem(IDC_STATIC_CO2)     ->SetFont(&m_static_co2);
	GetDlgItem(IDC_STATIC_TEMP)    ->SetFont(&m_static_temp);
	GetDlgItem(IDC_STATIC_HUMI)	   ->SetFont(&m_static_humi);
	GetDlgItem(IDC_STATIC_CO2DATA) ->SetFont(&m_static_co2data);
	GetDlgItem(IDC_STATIC_TEMPDATA)->SetFont(&m_static_tempdata);
	GetDlgItem(IDC_STATIC_HUMIDATA)->SetFont(&m_static_humidata);
	GetDlgItem(IDC_STATIC_PPM)     ->SetFont(&m_static_ppm);
	GetDlgItem(IDC_STATIC_C)       ->SetFont(&m_static_c);
	GetDlgItem(IDC_STATIC_PER)     ->SetFont(&m_static_per);
}

void Cjyl_classDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	//������ ����
	serchport   .ThreadClose();
	m_sockThread.ThreadClose();
	m_socket    .Close();
	KillTimer(0);

	if(Tray_Flag) //Ʈ���� �������� �Ǿ��ִٸ�
	{
		//���ҽ� ���� 
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd   = m_hWnd;
		nid.uID    = IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE,&nid);//<-�߿�κ�
	}
}

void Cjyl_classDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cjyl_classDlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cjyl_classDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL Cjyl_classDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	RECT rt;
	GetClientRect(&rt);
	m_bmTool.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  
	//return CDialogEx::OnEraseBkgnd(pDC);
	//����� ������� ä���� ����
	return true;
}


LRESULT Cjyl_classDlg::OnNcHitTest(CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//return CDialogEx::OnNcHitTest(point);
	//���̾�α�â Ŭ���� Ÿ��Ʋ�� Ŭ���� ���� ȿ��
	return HTCAPTION;
}

//ȯ�漳�� ��ư
void Cjyl_classDlg::OnBnClickedButtonSetup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Open_setupDlg();
}

void Cjyl_classDlg::Open_setupDlg(void)
{
	CSetup_Dlg dlg;
	dlg.HTRoom_IP = m_HTRoom_IP;
	dlg.OT        = m_OT;
	dlg.CAS       = m_CAS;
	dlg.PRE_SC	  = m_SC;
	dlg.Grad	  = m_Grad;
	dlg.Class     = m_Class;
	dlg.SOUND     = m_SOUND;
	if(dlg.DoModal()==IDOK){
		m_HTRoom_IP = dlg.HTRoom_IP;
		m_OT		= dlg.OT;
		m_CAS	    = dlg.CAS;
		m_SC		= dlg.SC;
		m_Grad	    = dlg.Grad;
		m_Class	    = dlg.Class;
		m_SOUND		= dlg.SOUND;
		savesetup();
	}
}

void Cjyl_classDlg::savesetup(void)
{
	CString   m_StrRunPath;
	TCHAR     buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	//���� ���� ���
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s\\%s",buf,FILE_SETUP);

	ofstream outfile;
	char savestr[200];
	sprintf(savestr,"AutoStart : %d\nOnlyTop : %d\nTransParency : %d\nHeadTeacherIP : %s\nGrad : %d\nClass : %d\nSound : %d\n"
		,m_CAS,m_OT,m_SC,m_HTRoom_IP,m_Grad,m_Class, m_SOUND);

	outfile.open(m_StrRunPath, ios::trunc);
	outfile.write(savestr,strlen(savestr));
	outfile.close();
}

//Ʈ���� ��ư
void Cjyl_classDlg::OnBnClickedButtonTray()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//Ʈ����ȭ
	SetMinimizeToTray();
}

void Cjyl_classDlg::SetMinimizeToTray()
{
	NOTIFYICONDATA nid;
	//Ʈ���� �÷��� Ʈ��
	Tray_Flag=true;

	ShowWindow(SW_SHOWMINIMIZED);
	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = 0;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYICON);
	//CAnimateCtrl icon;
	//icon.SetIcon(m_hIcon,true);
	//icon.AnimateWindow(50,2);
	nid.hWnd = this->m_hWnd;
	CString str;
	GetWindowText(str);
	strcpy(nid.szTip, str.GetBuffer(str.GetLength()+1));
	str.ReleaseBuffer();
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = TRAY_NOTIFY;
	Shell_NotifyIcon(NIM_ADD, &nid);
}

void Cjyl_classDlg::OnTrayOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	SetRestoreFromTray();
}


//Ʈ���̸� �⺻ ������� ����
void Cjyl_classDlg::SetRestoreFromTray()
{
	NOTIFYICONDATA nid;
	Tray_Flag=false;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = 0;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	ShowWindow(SW_RESTORE);
	SetForegroundWindow();
}

//Ʈ���̿��� ȯ��� ����
void Cjyl_classDlg::OnTraySetup()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Open_setupDlg();
}

//Ʈ���� ���� ��ư
void Cjyl_classDlg::OnTrayFinish()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}

//Ʈ���� ������ �޽��� ó���Լ�
LRESULT Cjyl_classDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
		
	case WM_LBUTTONDBLCLK:   // Ʈ���̾����� ���ʹ�ư ����Ŭ���� â�� �ٽ� ������.
		{ 
			SetRestoreFromTray();
		}
		break;
	case WM_RBUTTONDOWN:     // Ʈ���̾����� �����ʹ�ư Ŭ���� �˾��޴�â ����.
		{
			//���콺 ��ǥ ��������
			CPoint ptMouse;
			GetCursorPos(&ptMouse);

			CMenu menu;
			menu.LoadMenu(IDR_MENU_TRAY);			
			CMenu *pMenu = menu.GetSubMenu(0);
			
			if(m_OT)
				CheckMenuItem(menu.GetSafeHmenu(),ID_TRAY_ONLYTOP,MF_CHECKED);
			else
				CheckMenuItem(menu.GetSafeHmenu(),ID_TRAY_ONLYTOP,MF_UNCHECKED);
			if(m_CAS)
				CheckMenuItem(menu.GetSafeHmenu(),ID_TRAY_AUTOSTART,MF_CHECKED);
			else
				CheckMenuItem(menu.GetSafeHmenu(),ID_TRAY_AUTOSTART,MF_UNCHECKED);
			//�޴� ��� �� �ɼ�����
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				ptMouse.x, ptMouse.y, AfxGetMainWnd());
		}
		break;
	}

	return 0;
}

void Cjyl_classDlg::OnUpdateTrayAutostart(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	m_CAS=1-m_CAS;
	CWindowAutoStart autostart;

	autostart.setAutoStart(m_CAS);

	savesetup();
}

void Cjyl_classDlg::OnUpdateTrayOnlytop(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	CWnd *t_CWnd;
	CRect rect;
	//Ÿ���� CWnd �ޱ�
	t_CWnd=AfxGetMainWnd();
	//Ÿ�Ͽ� �����Ͽ� Rect�� ����
	t_CWnd->GetClientRect(&rect);
	m_OT=1-m_OT;
	if(m_OT)
		t_CWnd->SetWindowPos(&wndTopMost,0,0,rect.Width(),rect.Height(),SWP_NOMOVE);
	else
		t_CWnd->SetWindowPos(&wndNoTopMost,0,0,rect.Width(),rect.Height(),SWP_NOMOVE);

	savesetup();
}

HBRUSH Cjyl_classDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	//���ڻ�
	if(m_color_co2.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//���ڻ� ����
		pDC->SetBkMode(TRANSPARENT);//��� ����
		// pDC->SetBkColor(RGB(0,0,255));//���� ����
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_temp.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_humi.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_co2data.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(45,65,109));//���� ����
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_tempdata.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(45,65,109));//���� ����
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_humidata.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(45,65,109));//���� ����
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_ppm.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_c.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_per.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

LRESULT Cjyl_classDlg::OnFindPort(WPARAM port, LPARAM lpara)
{
	char m_port[20];
	sprintf(m_port,"\\\\.\\COM%d",port);

	Comm = new CCommNetwork(m_port,"9600","1","None","8 Bit");
	if(Comm->Create(GetSafeHwnd()) != 0){
		//MessageBox("���� ����","");
		//������ ���� (������ �������� �ٽ� Ȱ��ȭ ���� �ؾߵ�)
		serchport.ThreadStop();
		m_sockThread.setThread(GetSafeHwnd());
	}else{
		delete Comm;
	}
	return 0;
}

LRESULT Cjyl_classDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[60],tempdata[60];
	CString sep=" ,\r,\n";
	memset(tempdata,'\0',60);
	if(Comm)
	{
		Comm->Receive(data,length);
		data[length]='\0';

		for(int i =0 ; i <(int)length ; i++){
			str+=data[i];
		}
		sprintf(tempdata,"%s",str);

		sprintf(str_co2,"%s\0",strtok(tempdata,sep));
		sprintf(str_temp,"%s\0",strtok(NULL,sep));
		sprintf(str_humi,"%s\0",strtok(NULL,sep));

		//���� ���� ���� ���
		MakeLevel();

		SetDlgItemText(IDC_STATIC_CO2DATA,str_co2);
		SetDlgItemText(IDC_STATIC_TEMPDATA,str_temp);
		SetDlgItemText(IDC_STATIC_HUMIDATA,str_humi);

		RestRoom.Lock();//������ ��

		RestRoom.Unlock();//������ ��Ǯ��
	}
	InvalidateRgn(NULL);
	return 0;
}

void Cjyl_classDlg::MakeLevel()
{
	int Check_Co2 = atoi(str_co2);

	if(Check_Co2 < 1000)
		m_Level = STATE_NORMAL;
	else if(Check_Co2 >= 1000 && Check_Co2 < 1500)
		m_Level = STATE_WARNING;
	else if(Check_Co2 >= 1500)
		m_Level = STATE_DANGER;

	if(PreLevel != m_Level){
		sendDataPacket(TYPE_DATA);

		if(m_SOUND)
			SoundOut(m_Level);
		PreLevel = m_Level;
	}

	
}

void Cjyl_classDlg::SoundOut(int type)
{
	CString   m_StrRunPath;
	TCHAR     buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	//���� ���� ���
	GetCurrentDirectory(MAX_PATH, buf);


	if(type      == STATE_WARNING){
		m_StrRunPath.Format("%s\\Sound\\%s",buf,FILE_SOUND_WAR);
		sndPlaySound(m_StrRunPath, SND_ASYNC);
	}
	else if(type == STATE_DANGER){
		m_StrRunPath.Format("%s\\Sound\\%s",buf,FILE_SOUND_DAN);
		sndPlaySound(m_StrRunPath, SND_ASYNC);
	}
}

//�ø��� ��Ʈ ���� ����
LRESULT Cjyl_classDlg::OnClose(WPARAM length, LPARAM lpara)
{
	Comm->Close();
	Comm->HandleClose();
	return 0;
}

LRESULT Cjyl_classDlg::OnSockConnect(WPARAM wpara, LPARAM lpara)
{
	if(lpara==CONN_SUCCES){
		m_sockThread.ThreadStop();
		sendDataPacket(TYPE_INFO);
		sendDataPacket(TYPE_DATA);
		//MessageBox("���� ����");
		return 0;
	}
	else if (lpara==CONN_FAILE){
		//MessageBox("���� ����");
		return 0;
	}

	//�й� ������ ���� ��� ����õ����� ����
	if(m_Grad!=0&&m_Class!=0)
		m_socket.Connect(m_HTRoom_IP,SERVERPORT);
		
	return 0;
}

LRESULT Cjyl_classDlg::OnSockRece(WPARAM wpara, LPARAM lpara)
{
	char buf[1];
	int time;
	memset(buf,'\0',sizeof(buf));
	//����Ƿ� ���� ������ �۽� �ֱ⸦ ����
	m_socket.Receive(buf,sizeof(buf));
	time=buf[0];
	TimeCount=time;
	/*CString te;
	te.Format("%d",buf[0]);
	MessageBox(te);*/
	//�����͸� ������ Ÿ�̸� ����
	SetTimer(0,60000,NULL);
	return 0;
}

void Cjyl_classDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int tic;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent==0){
		if(TimeCount==tic){
			sendDataPacket(TYPE_DATA);
			tic=0;
		}
		tic++;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void Cjyl_classDlg::sendDataPacket(int Type)
{
	if(Type==TYPE_INFO){
		DPack.m_Type   =  Type;
		DPack.m_Co2[0] =  m_Grad;
		DPack.m_Co2[1] =  m_Class;
	}else if(Type==TYPE_DATA){
		DPack.m_Type   =  Type;
		DPack.m_Level  =  m_Level;

		strcpy(DPack.m_Co2  , str_co2);
		strcpy(DPack.m_Temp , str_temp);
		strcpy(DPack.m_Humi , str_humi);

		CString time;
			SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		time.Format("%d-%d-%d %d:%d\0",sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute);
		strcpy(DPack.m_DateTime , time);
	}else
		return;
	m_socket.Send(&DPack,sizeof(DPack),NULL);
}

LRESULT Cjyl_classDlg::OnSockClose(WPARAM wpara, LPARAM lpara)
{
	m_socket.Close();
	m_socket.Create();
	m_sockThread.ThreadReStart();
	MessageBox("���� ����");
	return 0;
}

void Cjyl_classDlg::OnBnClickedButtonCancle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
