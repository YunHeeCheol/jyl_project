
// jyl_HTRoomDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "jyl_HTRoomDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 127.0.0.1
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
#define INCREASE_XPOS 65
#define INCREASE_YPOS 100

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


// Cjyl_HTRoomDlg ��ȭ ����




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
	int Max     = IDC_BUTTON_612;	//������ ��ư�� ID
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


// Cjyl_HTRoomDlg �޽��� ó����

BOOL Cjyl_HTRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	_SetTitle(_T("CO2 ���� �ý���"));

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
	//MoveWindow(0,0,1050,780);
	//������ ũ�� ���� (����)
	SetWindowPos(&wndNoTopMost,0,0,1000,700,SWP_NOMOVE);
	CenterWindow();
	
	m_MDBMgr.Init();

	MaindlgInit();

	//���� �ʱ�ȭ�� ����
	m_ServerMgr.InitServer(this->m_hWnd);
	m_ServerMgr.CreateServer();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void Cjyl_HTRoomDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_ServerMgr.DestroyServer();

	m_MDBMgr.Close();

	if(Tray_Flag) //Ʈ���� �������� �Ǿ��ִٸ�
	{
		//���ҽ� ���� 
		NOTIFYICONDATA nid;
		nid.cbSize = sizeof(nid);
		nid.hWnd = m_hWnd;
		nid.uID = IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE,&nid);//<-�߿�κ�
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cjyl_HTRoomDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
	// ���ӵ� ������ �����Ͱ� ����������
	m_ServerMgr.OnReceive(wParam, lParam);
	return TRUE;
}

LPARAM Cjyl_HTRoomDlg::OnClose(WPARAM wParam, LPARAM lParam)
{
	//Ŭ���̾�Ʈ���� ������ ���� ���
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
	//�� ���̾�α�â�� �����ִ°��
	if(pDlg!=NULL){
		//���ú��� ������ �й��� ���̾�α�â�� �йݰ� ��ġ�Ұ�� ������ ���ε�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	//���� ���� ���
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s\\%s",buf,FILE_SETUP);

	outfile.open(m_StrRunPath, ios::trunc);
	outfile.write(savestr,strlen(savestr));
	outfile.close();
}

void Cjyl_HTRoomDlg::OnBnClickedSetup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	//Ư�� ���� �����ϰ�
	SetLayeredWindowAttributes(RGB(255,0,255),0,LWA_ALPHA);

	//���� ���� Ŭ����
	CTransparency transparency;

	CString   tok;
	char      str[200];
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

	////////��׶��� �̹���///////////////////////////////
	CString str_backgnd;
	CSize mSize;
	DWORD fSize;
	str_backgnd.Format("%s\\Skin\\%s",m_StrRunPath,BACKGND_FNAME);
	m_BackGnd.LoadPictureFile(NULL,str_backgnd,&m_bgImage,mSize,fSize);

	//////////���� ��ư��///////////////////////////////////

	CString str_nodata_d,str_nodata_c,str_nodata_f;
	CString str_normal_d,str_normal_c,str_normal_f;
	CString str_warning_d,str_warning_c,str_warning_f;
	CString str_danger_d,str_danger_c,str_danger_f;
	

	str_nodata_d .Format("%s\\Skin\\%s",m_StrRunPath,NON_D_FNAME);		//������ ���� ����Ʈ �̹���
	str_nodata_c .Format("%s\\Skin\\%s",m_StrRunPath,NON_C_FNAME);		//������ ���� Ŭ  �� �̹���
	str_nodata_f .Format("%s\\Skin\\%s",m_StrRunPath,NON_F_FNAME);		//������ ���� ��Ŀ�� �̹���

	str_normal_d .Format("%s\\Skin\\%s",m_StrRunPath,NOR_D_FNAME);		//���� ���� ����Ʈ �̹���
	str_normal_c .Format("%s\\Skin\\%s",m_StrRunPath,NOR_C_FNAME);		//���� ���� Ŭ  �� �̹���
	str_normal_f .Format("%s\\Skin\\%s",m_StrRunPath,NOR_F_FNAME);		//���� ���� ��Ŀ�� �̹���

	str_warning_d.Format("%s\\Skin\\%s",m_StrRunPath,WAR_D_FNAME);		//���� ��� ����Ʈ �̹���
	str_warning_c.Format("%s\\Skin\\%s",m_StrRunPath,WAR_C_FNAME);		//���� ��� Ŭ  �� �̹���
	str_warning_f.Format("%s\\Skin\\%s",m_StrRunPath,WAR_F_FNAME);		//���� ��� ��Ŀ�� �̹���

	str_danger_d .Format("%s\\Skin\\%s",m_StrRunPath,DAN_D_FNAME);		//���� ���� ����Ʈ �̹���
	str_danger_c .Format("%s\\Skin\\%s",m_StrRunPath,DAN_C_FNAME);		//���� ���� Ŭ  �� �̹���
	str_danger_f .Format("%s\\Skin\\%s",m_StrRunPath,DAN_F_FNAME);		//���� ���� ��Ŀ�� �̹���
	
	//�̹��� �ε�
	GradClass[1][0].JPGCopy(str_normal_d ,str_normal_d ,str_normal_f ,str_nodata_d
		,str_warning_d,str_warning_d,str_warning_f,str_nodata_d
		,str_danger_d ,str_danger_d ,str_danger_f ,str_nodata_d);
	for(int i=1;i<7;i++){
		for(int j=1;j<13;j++){
			GradClass[i][j].JPGCopy();
		}
	}
	
	//----------//Ÿ��Ʋ�� ������//----------//
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
	//�̹��� ũ�� ��������
	CRect rect;
	int   width;				//�̹��� ����
	int   height;               //�̹��� ����

	rect=GradClass[1][1].getSize();
	width=rect.Width();
	height=rect.Height();

	//�� ���ҽ� ��ġ����

	//GetDlgItem(IDC_STATIC_BACKGND)->MoveWindow(0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,FALSE);

	int xPos = 70;				//ù��° ��ư ��ǥ
	int yPos = 110;				//ù��° ��ư ��ǥ
	int Max  = IDC_BUTTON_612;	//������ ��ư�� ID
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	//���̾�α�â ����
	dlg.Grad     = grad_num;
	dlg.Class    = class_num;
	dlg.Co2data  = ClassData[grad_num][class_num].m_Co2;
	dlg.Tempdata = ClassData[grad_num][class_num].m_Temp;
	dlg.Humidata = ClassData[grad_num][class_num].m_Humi;
	dlg.State = ClassData[grad_num][class_num].m_Level;
	//���̾�α�â ����
	dlg.DoModal();
	pDlg=NULL;
}

BOOL Cjyl_HTRoomDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	RECT rt;
	GetClientRect(&rt);
	m_BackGnd.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  
	
	return true;
}

void Cjyl_HTRoomDlg::OnBnClickedButtonClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}

void Cjyl_HTRoomDlg::OnBnClickedButtonTray()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	//Ʈ���� �÷��� Ʈ��
	Tray_Flag=true;
}

void Cjyl_HTRoomDlg::OnTrayOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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

//Ʈ���� ������ �޽��� ó���Լ�
LRESULT Cjyl_HTRoomDlg::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
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
			if(m_AS)
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

void Cjyl_HTRoomDlg::OnTraySetup()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Open_setupDlg();
}


void Cjyl_HTRoomDlg::OnTrayOnlytop()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_OT=1-m_OT;
	if(m_OT)
		SetWindowPos(&wndTopMost,0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,SWP_NOMOVE);
	else
		SetWindowPos(&wndNoTopMost,0,0,WIN_RECT_WIDTH,WIN_RECT_HEIGHT,SWP_NOMOVE);

	savesetup();
}


void Cjyl_HTRoomDlg::OnTrayAutostart()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_AS=1-m_AS;
	CWindowAutoStart autostart;

	autostart.setAutoStart(m_AS);
	savesetup();
}





void Cjyl_HTRoomDlg::OnTrayFinish()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


