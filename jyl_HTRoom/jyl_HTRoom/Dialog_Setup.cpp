// Dialog_Setup.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "Dialog_Setup.h"
#include "afxdialogex.h"

// CDialog_Setup 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialog_Setup, CDialogEx)

CDialog_Setup::CDialog_Setup(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Setup::IDD, pParent)
{
	OT=0;AS=0;SC=0;//DP=5;
	PRE_SC=70;
}

CDialog_Setup::~CDialog_Setup()
{
}

void CDialog_Setup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_REGION, Combo_Region);
	DDX_Control(pDX, IDC_COMBO_CITY, Combo_City);
	DDX_Control(pDX, IDC_CHECK_ONLYTOP, Check_OnlyTop);
	DDX_Control(pDX, IDC_CHECK_AUTOSTART, Check_Autostart);
	DDX_Control(pDX, IDC_EDIT_DATAPERIOD, Edit_DataPeriod);
	DDX_Control(pDX, IDC_EDIT_SCHOOL, Edit_School);
	DDX_Control(pDX, IDC_SLIDER_CLOAKING, Slider_Cloaking);
	DDX_Control(pDX, IDC_SPIN_DATAPERIOD, Spin_Dataperiod);
	DDX_Control(pDX, IDC_STATICADRESS, m_color_adress);
	DDX_Control(pDX, IDC_STATICDATA, m_color_data);
	DDX_Control(pDX, IDC_STATICTRANS, m_color_trans);
	DDX_Control(pDX, IDC_STATICOPTION, m_color_option);
	DDX_Control(pDX, IDOK, m_button_ok);
	DDX_Control(pDX, IDCANCEL, m_button_cancel);
}


BEGIN_MESSAGE_MAP(CDialog_Setup, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_AUTOSTART, &CDialog_Setup::OnBnClickedCheckAutostart)
	ON_BN_CLICKED(IDC_CHECK_ONLYTOP, &CDialog_Setup::OnBnClickedCheckOnlytop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CLOAKING, &CDialog_Setup::OnNMCustomdrawSliderCloaking)

	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDialog_Setup 메시지 처리기입니다.


void CDialog_Setup::OnBnClickedCheckAutostart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AS=Check_Autostart.GetCheck();
}


void CDialog_Setup::OnBnClickedCheckOnlytop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OT=Check_OnlyTop.GetCheck();
}

BOOL CDialog_Setup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(&wndNoTopMost,0,0,480,290,SWP_NOMOVE);
	SetResource();
	SetFont();
	setupdlginit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDialog_Setup::OnNMCustomdrawSliderCloaking(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SC=Slider_Cloaking.GetPos();
	TP.SetTransparency(SC,AfxGetMainWnd()->m_hWnd);
	*pResult = 0;
}
void CDialog_Setup::SetOnlyTop(int flag)
{
	CWnd *t_CWnd;
	CRect rect;
	//타켓의 CWnd 받기
	t_CWnd=AfxGetMainWnd();
	//타켓에 접근하여 Rect를 구함
	t_CWnd->GetClientRect(&rect);
	if(flag)
		//항상위에 설정
		t_CWnd->SetWindowPos(&wndTopMost,0,0,rect.Width(),rect.Height(),SWP_NOMOVE);
	else
		//항상위에 해재
		t_CWnd->SetWindowPos(&wndNoTopMost,0,0,rect.Width(),rect.Height(),SWP_NOMOVE);
}

void CDialog_Setup::setupdlginit(void)
{
	Spin_Dataperiod.SetRange(5,10);

	CArrString arrstr;
	CString* RegionStr=arrstr.getRegionStr();
	//콤보박스 초기화
	CString tempstr;
	for (int i=0; i<16;i++)
	{	
		Combo_Region.AddString(RegionStr[i]);
	}

	if(OT){
		Check_OnlyTop.SetCheck(1);
	}
	if(AS){
		Check_Autostart.SetCheck(1);
	}
	SetDlgItemInt(IDC_EDIT_DATAPERIOD,DP);

	Slider_Cloaking.SetPos(PRE_SC);

	SetDlgItemText(IDC_EDIT_SCHOOL,str_School);
}

void CDialog_Setup::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	DP=GetDlgItemInt(IDC_EDIT_DATAPERIOD);
	WAutoStart.setAutoStart(AS);
	SetOnlyTop(OT);
	CDialogEx::OnOK();
}


void CDialog_Setup::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Slider_Cloaking.SetPos(PRE_SC);
	CDialogEx::OnCancel();
}





void CDialog_Setup::SetResource(void)
{
	CString m_StrRunPath;
	CString str_background;
	CString str_ok_d,str_ok_c,str_cancel_d,str_cancel_c;
	TCHAR   buf[MAX_PATH];

	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s",buf);
	CSize mSize;
	DWORD fSize;

	str_background.Format("%s\\Skin\\%s",m_StrRunPath,BACKGND_SET);
	m_BackGnd.LoadPictureFile(NULL,str_background,&m_bgImage,mSize,fSize);

	str_ok_d.    Format("%s\\Skin\\%s",m_StrRunPath,OK_NONE);
	str_ok_c.    Format("%s\\Skin\\%s",m_StrRunPath,OK_CLICK);
	str_cancel_d.Format("%s\\Skin\\%s",m_StrRunPath,CANCEL_NONE);
	str_cancel_c.Format("%s\\Skin\\%s",m_StrRunPath,CANCEL_CLICK);

	m_button_ok.    LoadJPG(str_ok_d,str_ok_c,str_ok_d,str_ok_d);
	m_button_cancel.LoadJPG(str_cancel_d,str_cancel_c,str_cancel_d,str_cancel_d);

	GetDlgItem(IDOK)    ->MoveWindow(140,240,80,30,FALSE);
	GetDlgItem(IDCANCEL)->MoveWindow(260,240,80,30,FALSE);

	GetDlgItem(IDC_STATIC_ADRESS)->MoveWindow(20,16,430,60,FALSE);
	GetDlgItem(IDC_STATIC_DATA)  ->MoveWindow(20,95,115,60,FALSE);
	GetDlgItem(IDC_STATIC_TRANS) ->MoveWindow(150,95,300,60,FALSE);
	GetDlgItem(IDC_STATIC_OPTION)->MoveWindow(20,175,430,50,FALSE);

	GetDlgItem(IDC_COMBO_REGION)->MoveWindow(35,40,100,200,FALSE);
	GetDlgItem(IDC_COMBO_CITY)  ->MoveWindow(170,40,100,200,FALSE);
	GetDlgItem(IDC_EDIT_SCHOOL) ->MoveWindow(305,40,100,20,FALSE);

	GetDlgItem(IDC_EDIT_DATAPERIOD)->MoveWindow(36,120,62,20,FALSE);
	GetDlgItem(IDC_SPIN_DATAPERIOD)->MoveWindow(98,120,20,20,FALSE);
	GetDlgItem(IDC_SLIDER_CLOAKING)->MoveWindow(168,117,270,26,FALSE);

	GetDlgItem(IDC_CHECK_AUTOSTART)->MoveWindow(35,195,150,20,FALSE);
	GetDlgItem(IDC_CHECK_ONLYTOP)  ->MoveWindow(260,195,80,20,FALSE);

	GetDlgItem(IDC_STATICADRESS)->MoveWindow(25,7,100,20,FALSE);
	GetDlgItem(IDC_STATICDATA)  ->MoveWindow(25,84,100,20,FALSE);
	GetDlgItem(IDC_STATICTRANS) ->MoveWindow(148,84,80,20,FALSE);
	GetDlgItem(IDC_STATICOPTION)->MoveWindow(25,165,50,20,FALSE);

}


HBRUSH CDialog_Setup::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(m_color_adress.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_data.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_trans.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_option.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
		if(pWnd->GetDlgCtrlID() == IDC_CHECK_AUTOSTART)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	if(pWnd->GetDlgCtrlID() == IDC_CHECK_ONLYTOP)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


void CDialog_Setup::SetFont(void)
{
	m_adress.CreateFontA(18,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_data.  CreateFontA(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_trans. CreateFontA(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_option.CreateFontA(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");

	GetDlgItem(IDC_STATICADRESS)->SetFont(&m_adress);
	GetDlgItem(IDC_STATICDATA)  ->SetFont(&m_data);
	GetDlgItem(IDC_STATICTRANS) ->SetFont(&m_trans);
	GetDlgItem(IDC_STATICOPTION)->SetFont(&m_option);
}


LRESULT CDialog_Setup::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnNcHitTest(point);
	return HTCAPTION;
}


BOOL CDialog_Setup::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	RECT rt;
	GetClientRect(&rt);
	m_BackGnd.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  
	
	return true;
}
