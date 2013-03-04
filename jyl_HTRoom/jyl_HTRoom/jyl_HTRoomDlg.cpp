
// jyl_HTRoomDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "jyl_HTRoomDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 127.0.0.1
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
#define INCREASE_XPOS 65
#define INCREASE_YPOS 100

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


// Cjyl_HTRoomDlg 대화 상자




Cjyl_HTRoomDlg::Cjyl_HTRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cjyl_HTRoomDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_OT=0;
	m_AS=0;
	m_SC=0;
	m_DP=5;
	m_str_region="";
	m_str_City="";
	m_str_School="";
	pDlg=NULL;
	Tray_Flag=false;
	memset(ClassData,0,sizeof(ClassData));
}

void Cjyl_HTRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	int Max     = IDC_BUTTON_612;	//마지막 버튼의 ID
	int t_Grad  = 1;
	int t_Class = 1;
	for(int i=IDC_BUTTON_11;i<=Max;i++){
		DDX_Control(pDX, i, GradClass[t_Grad][t_Class]);
		t_Class++;
		if(t_Class==13){
			t_Grad++;
			t_Class=1;
		}
	}

	DDX_Control(pDX, IDC_BUTTON_SETUP, Icon_Setup);
	DDX_Control(pDX, IDC_BUTTON_TRAY, Icon_Tray);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, Icon_Close);
}

BEGIN_MESSAGE_MAP(Cjyl_HTRoomDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_SETUP, &Cjyl_HTRoomDlg::OnBnClickedSetup)
	ON_MESSAGE(UM_ACCEPT, OnAccept)
	ON_MESSAGE(UM_RECEIVE, OnReceive)
	ON_MESSAGE(UM_CLOSE, OnClose)
	ON_MESSAGE(UM_BTNSET, OnBtnSet)
	ON_MESSAGE(UM_DISCON, OnDisCon)
	ON_MESSAGE(TRAY_NOTIFY, OnTrayIconClick)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &Cjyl_HTRoomDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_TRAY, &Cjyl_HTRoomDlg::OnBnClickedButtonTray)
	ON_COMMAND(ID_TRAY_SETUP, &Cjyl_HTRoomDlg::OnTraySetup)
	ON_COMMAND(ID_TRAY_ONLYTOP, &Cjyl_HTRoomDlg::OnTrayOnlytop)
	ON_COMMAND(ID_TRAY_AUTOSTART, &Cjyl_HTRoomDlg::OnTrayAutostart)
	ON_COMMAND(ID_TRAY_OPEN, &Cjyl_HTRoomDlg::OnTrayOpen)
	ON_COMMAND(ID_TRAY_FINISH, &Cjyl_HTRoomDlg::OnTrayFinish)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Cjyl_HTRoomDlg 메시지 처리기

BOOL Cjyl_HTRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	_SetTitle(_T("CO2 감시 시스템"));

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
	//MoveWindow(0,0,1050,780);
	//윈도우 크기 설정 (고정)
	SetWindowPos(&wndNoTopMost,0,0,1000,700,SWP_NOMOVE);
	CenterWindow();
	
	m_MDBMgr.Init();

	MaindlgInit();

	//서버 초기화면 생성
	m_ServerMgr.InitServer(this->m_hWnd);
	m_ServerMgr.CreateServer();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cjyl_HTRoomDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_ServerMgr.DestroyServer();

	m_MDBMgr.Close();

	if(Tray_Flag) //트레이 아이콘이 되어있다면
	{
		//리소스 해제 
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE,&nid);//<-중요부분
	}


}

void Cjyl_HTRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cjyl_HTRoomDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
HCURSOR Cjyl_HTRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LPARAM Cjyl_HTRoomDlg::OnAccept(WPARAM wParam, LPARAM lParam)
{
	m_ServerMgr.OnAccept(wParam, m_DP);
	return TRUE;
}


LPARAM Cjyl_HTRoomDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	// 접속된 곳에서 데이터가 도착했을때
	m_ServerMgr.OnReceive(wParam, lParam);
	return TRUE;
}

LPARAM Cjyl_HTRoomDlg::OnClose(WPARAM wParam, LPARAM lParam)
{
	//클라이언트에서 소켓이 닫힌 경우
	m_ServerMgr.OnClose(wParam, lParam);
	return TRUE;
}

LPARAM Cjyl_HTRoomDlg::OnBtnSet(WPARAM wParam, LPARAM lParam)
{
	int			 n_grad;
	int			 n_class;
	CClientData* pData;
	CDataPack*   DPack;

	pData      = (CClientData*)wParam;
	DPack      = pData->m_DPack;
	n_grad     = pData->m_Grad;
	n_class    = pData->m_Class;

	GradClass[n_grad][n_class].EnableWindow(TRUE);
	GradClass[n_grad][n_class].Change_State(DPack->m_Level);

	strcpy(ClassData[n_grad][n_class].m_Co2		  , DPack->m_Co2);
	strcpy(ClassData[n_grad][n_class].m_Temp      , DPack->m_Temp);
	strcpy(ClassData[n_grad][n_class].m_Humi      , DPack->m_Humi);
	strcpy(ClassData[n_grad][n_class].m_DateTime  , DPack->m_DateTime);
	ClassData[n_grad][n_class].m_Level = DPack->m_Level;
	//상세 다이얼로그창이 열려있는경우
	if(pDlg!=NULL){
		//리시브한 데이터 학반이 다이얼로그창의 학반과 일치할경우 데이터 업로드
		if(pDlg->Grad==n_grad&&pDlg->Class==n_class){
			pDlg->SetDlgItemText(IDC_STATIC_CO2DATA ,DPack->m_Co2);
			pDlg->SetDlgItemText(IDC_STATIC_TEMPDATA,DPack->m_Temp);
			pDlg->SetDlgItemText(IDC_STATIC_HUMIDATA,DPack->m_Humi);
		}

	}
	if(DPack->m_Level>=2){
		if(Tray_Flag){
			CDialog_Info dlg;
			dlg.m_grad=n_grad;
			dlg.m_class=n_class;
			dlg.m_state=ClassData[n_grad][n_class].m_Level;
			dlg.DoModal();
		}
	}

	Invalidate();

	m_MDBMgr.Append(pData);

	return TRUE;
}

LPARAM Cjyl_HTRoomDlg::OnDisCon(WPARAM wParam, LPARAM lParam)
{
	int			 n_grad;
	int			 n_class;
	CClientData* pData;
	CDataPack*   DPack;

	pData      = (CClientData*)wParam;
	DPack      = pData->m_DPack;
	n_grad     = pData->m_Grad;
	n_class    = pData->m_Class;

	GradClass[n_grad][n_class].EnableWindow(FALSE);

	Invalidate();
	return TRUE;
}

LRESULT Cjyl_HTRoomDlg::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnNcHitTest(point);
	return HTCAPTION;
}

void Cjyl_HTRoomDlg::savesetup(void)
{

	ofstream outfile;
	char savestr[100];
	sprintf(savestr
		,"Region : %s\nCity : %s\nSchool : %s\nDataPeriod : %d\nTransparency : %d\nAutoStart : %d\nOnlyTop : %d\n"
		,m_str_region,m_str_City,m_str_School,m_DP,m_SC,m_AS,m_OT);

	CString   m_StrRunPath;
	TCHAR     buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	//실행 파일 경로
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s\\%s",buf,FILE_SETUP);

	outfile.open(m_StrRunPath, ios::trunc);
	outfile.write(savestr,strlen(savestr));
	outfile.close();
}

void Cjyl_HTRoomDlg::OnBnClickedSetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Open_setupDlg();
	
}

void Cjyl_HTRoomDlg::Open_setupDlg(void)
{
	CDialog_Setup dlg;
	dlg.AS         = m_AS;
	dlg.OT         = m_OT;
	dlg.PRE_SC     = m_SC;
	dlg.DP         = m_DP;
	dlg.str_region = m_str_region;
	dlg.str_City   = m_str_City;
	dlg.str_School = m_str_School;
	if(dlg.DoModal()==IDOK){
		m_AS         = dlg.AS;
		m_OT         = dlg.OT;
		m_SC         = dlg.SC;
		m_DP         = dlg.DP;
		m_str_region = dlg.str_region;
		m_str_City   = dlg.str_City;
		m_str_School = dlg.str_School;
		savesetup();
	}
}

void Cjyl_HTRoomDlg::MaindlgInit(void)
{
	//wntjr cjfldlqslek.
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+2, rc.top+2, rc.right-2, rc.bottom-2,15,15);
	::SetWindowRgn(m_hWnd,(HRGN)rgn, TRUE);

	Skin_init();

	//특정 색상 투명하게
	SetLayeredWindowAttributes(RGB(255,0,255),0,LWA_ALPHA);

	//투명 조절 클래스
	CTransparency transparency;

	CString   tok;
	char      str[200];
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
		transparency.SetTransparency((70),this->m_hWnd);
		return;
	}

	while(!SetupFile.eof()){

		SetupFile.getline(str,sizeof(str));
		tok = strtok( str, separater );

		if( strcmp( tok, "Transparency" ) == 0 ){
			m_SC=atoi(strtok( NULL, separater));
			transparency.SetTransparency(m_SC,this->m_hWnd);
		}
		if( strcmp( tok, "OnlyTop"      ) == 0 ){
			if(strcmp(strtok( NULL, separater ),"1")==0){
				CDialog_Setup dlg;
				m_OT=1;
				dlg.SetOnlyTop(m_OT);
			}
		}

		if( strcmp( tok, "AutoStart"    ) == 0 )
			if(strcmp(strtok( NULL, separater ),"1")==0)
				m_AS=1;
		if( strcmp( tok, "DataPeriod"   ) == 0 )
			m_DP=atoi(strtok( NULL, separater ));
		if( strcmp( tok, "School"       ) == 0 )
			m_str_School=strtok( NULL, separater);
		if( strcmp( tok, "City"         ) == 0 )
			m_str_City=strtok( NULL, separater);
		if( strcmp( tok, "Region"       ) == 0 )
			m_str_region=strtok( NULL, separater);
	}
	SetupFile.close();
}


void Cjyl_HTRoomDlg::Skin_init(void)
{
	CString m_StrRunPath;
	TCHAR   buf[MAX_PATH];

	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s",buf);

	////////백그라운드 이미지///////////////////////////////
	CString str_backgnd;
	CSize mSize;
	DWORD fSize;
	str_backgnd.Format("%s\\Skin\\%s",m_StrRunPath,BACKGND_FNAME);
	m_BackGnd.LoadPictureFile(NULL,str_backgnd,&m_bgImage,mSize,fSize);

	//////////상태 버튼들///////////////////////////////////

	CString str_nodata_d,str_nodata_c,str_nodata_f;
	CString str_normal_d,str_normal_c,str_normal_f;
	CString str_warning_d,str_warning_c,str_warning_f;
	CString str_danger_d,str_danger_c,str_danger_f;
	

	str_nodata_d .Format("%s\\Skin\\%s",m_StrRunPath,NON_D_FNAME);		//데이터 없음 디폴트 이미지
	str_nodata_c .Format("%s\\Skin\\%s",m_StrRunPath,NON_C_FNAME);		//데이터 없음 클  릭 이미지
	str_nodata_f .Format("%s\\Skin\\%s",m_StrRunPath,NON_F_FNAME);		//데이터 없음 포커스 이미지

	str_normal_d .Format("%s\\Skin\\%s",m_StrRunPath,NOR_D_FNAME);		//상태 정상 디폴트 이미지
	str_normal_c .Format("%s\\Skin\\%s",m_StrRunPath,NOR_C_FNAME);		//상태 정상 클  릭 이미지
	str_normal_f .Format("%s\\Skin\\%s",m_StrRunPath,NOR_F_FNAME);		//상태 정상 포커스 이미지

	str_warning_d.Format("%s\\Skin\\%s",m_StrRunPath,WAR_D_FNAME);		//상태 경고 디폴트 이미지
	str_warning_c.Format("%s\\Skin\\%s",m_StrRunPath,WAR_C_FNAME);		//상태 경고 클  릭 이미지
	str_warning_f.Format("%s\\Skin\\%s",m_StrRunPath,WAR_F_FNAME);		//상태 경고 포커스 이미지

	str_danger_d .Format("%s\\Skin\\%s",m_StrRunPath,DAN_D_FNAME);		//상태 위험 디폴트 이미지
	str_danger_c .Format("%s\\Skin\\%s",m_StrRunPath,DAN_C_FNAME);		//상태 위험 클  릭 이미지
	str_danger_f .Format("%s\\Skin\\%s",m_StrRunPath,DAN_F_FNAME);		//상태 위험 포커스 이미지
	
	//이미지 로드
	GradClass[1][0].JPGCopy(str_normal_d ,str_normal_d ,str_normal_f ,str_nodata_d
		,str_warning_d,str_warning_d,str_warning_f,str_nodata_d
		,str_danger_d ,str_danger_d ,str_danger_f ,str_nodata_d);
	for(int i=1;i<7;i++){
		for(int j=1;j<13;j++){
			GradClass[i][j].JPGCopy();
		}
	}
	
	//----------//타이틀바 아이콘//----------//
	CString str_setup_d,str_setup_c,str_setup_f;
	CString str_tray_d ,str_tray_c ,str_tray_f;
	CString str_close_d,str_close_c,str_close_f;

	str_setup_d.Format("%s\\Skin\\%s",m_StrRunPath,SET_D_FNAME);
	str_setup_c.Format("%s\\Skin\\%s",m_StrRunPath,SET_C_FNAME);
	str_tray_d .Format("%s\\Skin\\%s",m_StrRunPath,TRA_D_FNAME);
	str_tray_c .Format("%s\\Skin\\%s",m_StrRunPath,TRA_C_FNAME);
	str_close_d.Format("%s\\Skin\\%s",m_StrRunPath,CLO_D_FNAME);
	str_close_c.Format("%s\\Skin\\%s",m_StrRunPath,CLO_C_FNAME);


	Icon_Setup.LoadJPG(str_setup_d,str_setup_c,str_setup_d,str_setup_d);
	Icon_Tray .LoadJPG(str_tray_d,str_tray_c,str_tray_d,str_tray_d);
	Icon_Close.LoadJPG(str_close_d,str_close_c,str_close_d,str_close_d);

////////////////////////////////////////////////////////////////////////
	//이미지 크기 가져오기
	CRect rect;
	int   width;				//이미지 넓이
	int   height;               //이미지 높이

	rect=GradClass[1][1].getSize();
	width=rect.Width();
	height=rect.Height();

	//각 리소스 위치지정

	//GetDlgItem(IDC_STATIC_BACKGND)->MoveWindow(0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,FALSE);

	int xPos = 70;				//첫번째 버튼 좌표
	int yPos = 110;				//첫번째 버튼 좌표
	int Max  = IDC_BUTTON_612;	//마지막 버튼의 ID
	for(int i=IDC_BUTTON_11;i<=Max;i++){
		GetDlgItem(i)->MoveWindow(xPos,yPos,width,height,FALSE);
		xPos+=75;
		if(xPos>895){
			xPos=70;
			yPos+=98;
		}
	}

	GetDlgItem(IDC_BUTTON_SETUP)  ->MoveWindow(840,10,42,42,FALSE);
	GetDlgItem(IDC_BUTTON_TRAY)   ->MoveWindow(890,10,42,42,FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)  ->MoveWindow(940,10,42,42,FALSE);
	
}


BOOL Cjyl_HTRoomDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	int grad_num,class_num;
	int temp;
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(IDC_BUTTON_11<=nID&&IDC_BUTTON_612>=nID){
		class_num=(nID-1010)%12;
		if(class_num==0){
			grad_num=(nID-1010)/12;
			class_num=12;
		}
		else
			grad_num=(nID-1010)/12+1;
		OpenDetaildlg(grad_num,class_num);
	}
	return CDialogEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void Cjyl_HTRoomDlg::OpenDetaildlg(int grad_num,int class_num )
{
	CDialog_Detail dlg;
	pDlg=&dlg;
	//다이얼로그창 세팅
	dlg.Grad     = grad_num;
	dlg.Class    = class_num;
	dlg.Co2data  = ClassData[grad_num][class_num].m_Co2;
	dlg.Tempdata = ClassData[grad_num][class_num].m_Temp;
	dlg.Humidata = ClassData[grad_num][class_num].m_Humi;
	dlg.State = ClassData[grad_num][class_num].m_Level;
	//다이얼로그창 열기
	dlg.DoModal();
	pDlg=NULL;
}

BOOL Cjyl_HTRoomDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	RECT rt;
	GetClientRect(&rt);
	m_BackGnd.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  
	
	return true;
}

void Cjyl_HTRoomDlg::OnBnClickedButtonClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
}

void Cjyl_HTRoomDlg::OnBnClickedButtonTray()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetMinimizeToTray();
}

void Cjyl_HTRoomDlg::SetMinimizeToTray()
{
	NOTIFYICONDATA nid;

	ShowWindow(SW_SHOWMINIMIZED);
	PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd   = this->m_hWnd;
	nid.uID    = 0;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hIcon  = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//CAnimateCtrl icon;
	//icon.SetIcon(m_hIcon,true);
	//icon.AnimateWindow(50,2);
	nid.hWnd = this->m_hWnd;
	CString str;
	GetWindowText(str);
	strcpy(nid.szTip, str.GetBuffer(str.GetLength()+1));
	str.ReleaseBuffer();
	nid.uID              = 0;
	nid.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = TRAY_NOTIFY;
	Shell_NotifyIcon(NIM_ADD, &nid);

	//트레이 플레그 트루
	Tray_Flag=true;
}

void Cjyl_HTRoomDlg::OnTrayOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetRestoreFromTray();
}

void Cjyl_HTRoomDlg::SetRestoreFromTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize   = sizeof(NOTIFYICONDATA);
	nid.hWnd     = this->m_hWnd;
	nid.uID      = 0;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	ShowWindow(SW_RESTORE);
	SetForegroundWindow();

	Tray_Flag=false;
}

//트레이 아이콘 메시지 처리함수
LRESULT Cjyl_HTRoomDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
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
			if(m_AS)
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

void Cjyl_HTRoomDlg::OnTraySetup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Open_setupDlg();
}


void Cjyl_HTRoomDlg::OnTrayOnlytop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_OT=1-m_OT;
	if(m_OT)
		SetWindowPos(&wndTopMost,0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,SWP_NOMOVE);
	else
		SetWindowPos(&wndNoTopMost,0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,SWP_NOMOVE);

	savesetup();
}


void Cjyl_HTRoomDlg::OnTrayAutostart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_AS=1-m_AS;
	CWindowAutoStart autostart;

	autostart.setAutoStart(m_AS);
	savesetup();
}





void Cjyl_HTRoomDlg::OnTrayFinish()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	DestroyWindow();
}


