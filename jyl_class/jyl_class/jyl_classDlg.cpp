
// jyl_classDlg.cpp : 구현 파일
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
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// Cjyl_classDlg 대화 상자




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


// Cjyl_classDlg 메시지 처리기

BOOL Cjyl_classDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//다이얼로그 크기 고정
	SetWindowPos(&wndNoTopMost,0,0,300,270,SWP_NOMOVE);

	if(m_socket.Create()){
		//MessageBox("소켓 Create");
	}
	else{
		//MessageBox("소켓 Create 실패");
	}

	m_socket    .init(m_hWnd);
	serchport   .setHwnd(GetSafeHwnd());
	
	MainDlgInit();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cjyl_classDlg::MainDlgInit(void)
{
	//윈도우 크기를 얻어옴
	CRect rc;
	GetClientRect(rc);

	CRect shellrc;
	//작업표시줄의 핸들을 받음
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

	//윈도우를 오른쪽 아래로 꽃아줌
	SetWindowPos(&wndTop,(int)GetSystemMetrics(SM_CXSCREEN)-rc.Width()-xr,
		(int)GetSystemMetrics(SM_CYSCREEN)-rc.Height()-yr,0,0,SWP_NOSIZE);

	//글씨체
	setFont();

	//스킨 초기화
	SetDlgVisual();

	//투명 조절 클래스
	CTransparency transparency;

	CString   tok;
	char      str[100];
	char      separater[] = " ,:";
	ifstream  SetupFile;
	
	CString   m_StrRunPath;
	TCHAR     buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	//실행 파일 경로
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s\\%s",buf,FILE_SETUP);

	SetupFile.open(m_StrRunPath,ios::in);
	//파일이 없으면 리턴
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

	//다이얼로그 모양 재설정
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+2, rc.top+2, rc.right-2, rc.bottom-2,15,15);
	::SetWindowRgn(m_hWnd,(HRGN)rgn, TRUE);

	//버튼이미지
	CString m_StrRunPath;
	CString str_bkground;
	CString str_setup_n,str_setup_c;
	CString str_tray_n ,str_tray_c;
	CString str_exit_n ,str_exit_c;

	TCHAR buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s",buf);

	//버튼 이미지 경로
	str_setup_n .Format("%s\\Skin\\%s",m_StrRunPath,SETUP_NONE);
	str_setup_c .Format("%s\\Skin\\%s",m_StrRunPath,SETUP_CLICK);
	str_tray_n  .Format("%s\\Skin\\%s",m_StrRunPath,TRAY_NONE);
	str_tray_c  .Format("%s\\Skin\\%s",m_StrRunPath,TRAY_CLICK);
	str_exit_n  .Format("%s\\Skin\\%s",m_StrRunPath,EXIT_NONE);
	str_exit_c  .Format("%s\\Skin\\%s",m_StrRunPath,EXIT_CLICK);
	//배경 이미지 경로
	str_bkground.Format("%s\\Skin\\%s",m_StrRunPath,BKGROUND);

	//버틴 이미지 로드
	m_button_setup.LoadJPG(str_setup_n,str_setup_c,str_setup_n,str_setup_n);
	m_button_tray .LoadJPG(str_tray_n,str_tray_c,str_tray_n,str_tray_n);
	m_button_exit .LoadJPG(str_exit_n,str_exit_c,str_exit_n,str_exit_n);
	//배경 이미지 로드
	CSize mSize;
	DWORD fSize;
	m_bmTool.LoadPictureFile(NULL,str_bkground, &m_bgImage, mSize, fSize);

	
	CRect* rect;
	int   width,height;
	rect   = &m_button_setup.getSize();
	width  = rect->Width();
	height = rect->Height();

	//버튼,문자열 위치 재구성
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
	//글꼴 높이, 글꼴 너비, 방향, 회전각도, 굵기, 기울임꼴, 밑줄, 취소선, 문자 세트, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 글꼴 이름
	m_static_co2     .CreateFont(17,7,0,0,700,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_temp    .CreateFont(15,6,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_humi    .CreateFont(15,6,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_co2data .CreateFont(70,25,0,0,700,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (제목)");
	m_static_tempdata.CreateFont(50,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (제목)");
	m_static_humidata.CreateFont(50,20,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (제목)");
	m_static_ppm     .CreateFont(21,8,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_c       .CreateFont(20,10,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_per     .CreateFont(20,10,0,0,1000,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	

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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	//스레드 종료
	serchport   .ThreadClose();
	m_sockThread.ThreadClose();
	m_socket    .Close();
	KillTimer(0);

	if(Tray_Flag) //트레이 아이콘이 되어있다면
	{
		//리소스 해제 
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd   = m_hWnd;
		nid.uID    = IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE,&nid);//<-중요부분
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cjyl_classDlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cjyl_classDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL Cjyl_classDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	RECT rt;
	GetClientRect(&rt);
	m_bmTool.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  
	//return CDialogEx::OnEraseBkgnd(pDC);
	//배경을 흰색으로 채우지 않음
	return true;
}


LRESULT Cjyl_classDlg::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnNcHitTest(point);
	//다이얼로그창 클릭시 타이틀바 클릭과 같은 효과
	return HTCAPTION;
}

//환경설정 버튼
void Cjyl_classDlg::OnBnClickedButtonSetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	//실행 파일 경로
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

//트레이 버튼
void Cjyl_classDlg::OnBnClickedButtonTray()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//트레이화
	SetMinimizeToTray();
}

void Cjyl_classDlg::SetMinimizeToTray()
{
	NOTIFYICONDATA nid;
	//트레이 플레그 트루
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetRestoreFromTray();
}


//트레이를 기본 윈도우로 복원
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

//트레이에서 환경경 설정
void Cjyl_classDlg::OnTraySetup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Open_setupDlg();
}

//트레이 종료 버튼
void Cjyl_classDlg::OnTrayFinish()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DestroyWindow();
}

//트레이 아이콘 메시지 처리함수
LRESULT Cjyl_classDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
		
	case WM_LBUTTONDBLCLK:   // 트레이아이콘 왼쪽버튼 더블클릭시 창이 다시 열린다.
		{ 
			SetRestoreFromTray();
		}
		break;
	case WM_RBUTTONDOWN:     // 트레이아이콘 오른쪽버튼 클릭시 팝업메뉴창 띄운다.
		{
			//마우스 좌표 가져오기
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
			//메뉴 등록 및 옵션적용
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				ptMouse.x, ptMouse.y, AfxGetMainWnd());
		}
		break;
	}

	return 0;
}

void Cjyl_classDlg::OnUpdateTrayAutostart(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	m_CAS=1-m_CAS;
	CWindowAutoStart autostart;

	autostart.setAutoStart(m_CAS);

	savesetup();
}

void Cjyl_classDlg::OnUpdateTrayOnlytop(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CWnd *t_CWnd;
	CRect rect;
	//타켓의 CWnd 받기
	t_CWnd=AfxGetMainWnd();
	//타켓에 접근하여 Rect를 구함
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

	// TODO:  여기서 DC의 특성을 변경합니다.
	//글자색
	if(m_color_co2.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
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
		//pDC->SetBkColor(RGB(45,65,109));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_tempdata.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(45,65,109));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_humidata.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetBkColor(RGB(45,65,109));//배경색 변경
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

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

LRESULT Cjyl_classDlg::OnFindPort(WPARAM port, LPARAM lpara)
{
	char m_port[20];
	sprintf(m_port,"\\\\.\\COM%d",port);

	Comm = new CCommNetwork(m_port,"9600","1","None","8 Bit");
	if(Comm->Create(GetSafeHwnd()) != 0){
		//MessageBox("연결 성공","");
		//스레드 중지 (연결이 끊어지면 다시 활성화 구현 해야됨)
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

		//래밸 계산및 사운드 출력
		MakeLevel();

		SetDlgItemText(IDC_STATIC_CO2DATA,str_co2);
		SetDlgItemText(IDC_STATIC_TEMPDATA,str_temp);
		SetDlgItemText(IDC_STATIC_HUMIDATA,str_humi);

		RestRoom.Lock();//쓰레드 락

		RestRoom.Unlock();//쓰레드 락풀기
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
	//실행 파일 경로
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

//시리얼 포트 연결 해제
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
		//MessageBox("접속 성공");
		return 0;
	}
	else if (lpara==CONN_FAILE){
		//MessageBox("접속 실패");
		return 0;
	}

	//학반 정보가 없을 경우 연결시도하지 않음
	if(m_Grad!=0&&m_Class!=0)
		m_socket.Connect(m_HTRoom_IP,SERVERPORT);
		
	return 0;
}

LRESULT Cjyl_classDlg::OnSockRece(WPARAM wpara, LPARAM lpara)
{
	char buf[1];
	int time;
	memset(buf,'\0',sizeof(buf));
	//교장실로 부터 데이터 송신 주기를 받음
	m_socket.Receive(buf,sizeof(buf));
	time=buf[0];
	TimeCount=time;
	/*CString te;
	te.Format("%d",buf[0]);
	MessageBox(te);*/
	//데이터를 전송할 타이머 설정
	SetTimer(0,60000,NULL);
	return 0;
}

void Cjyl_classDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int tic;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	MessageBox("소켓 닫힘");
	return 0;
}

void Cjyl_classDlg::OnBnClickedButtonCancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
