// Setup_Dlg.cpp : 구현 grads.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "Setup_Dlg.h"

#define MAX_CLASS		12
#define MAX_GRAD		6

// CSetup_Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetup_Dlg, CDialogEx)

CSetup_Dlg::CSetup_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetup_Dlg::IDD, pParent)
{
	SC=0;CAS=0;OT=0;HTRoom_IP="";Grad=0;Class=0;
}

CSetup_Dlg::~CSetup_Dlg()
{
}

void CSetup_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECKAUTOSTART, CheckAutoStart);
	DDX_Control(pDX, IDC_CHECKONLYTOP, CheckOnlyTop);
	DDX_Control(pDX, IDC_CHECKSOUND, CheckSound);
	DDX_Control(pDX, IDC_SLIDERCLOAKING, SliderCloaking);
	DDX_Control(pDX, IDC_COMBO_GRAD, CB_Grad);
	DDX_Control(pDX, IDC_COMBO_CLASS, CB_Class);
	DDX_Control(pDX, IDOK, m_button_ok);
	DDX_Control(pDX, IDC_STATIC_CLASS, m_color_class);
	DDX_Control(pDX, IDC_STATIC_IP, m_color_ip);
	DDX_Control(pDX, IDC_STATIC_OPTION, m_color_option);
	DDX_Control(pDX, IDC_STATIC_TRANS, m_color_trans);
	DDX_Control(pDX, IDCANCEL, m_button_cancel);
}


BEGIN_MESSAGE_MAP(CSetup_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECKAUTOSTART, &CSetup_Dlg::OnBnClickedCheckautostart)
	ON_BN_CLICKED(IDC_CHECKONLYTOP, &CSetup_Dlg::OnBnClickedCheckonlytop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERCLOAKING, &CSetup_Dlg::OnNMCustomdrawSlidercloaking)
	ON_BN_CLICKED(IDCANCEL, &CSetup_Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CSetup_Dlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_GRAD, &CSetup_Dlg::OnCbnSelchangeComboGrad)
	ON_CBN_SELCHANGE(IDC_COMBO_CLASS, &CSetup_Dlg::OnCbnSelchangeComboClass)
	ON_BN_CLICKED(IDC_CHECKSOUND, &CSetup_Dlg::OnBnClickedChecksound)
	ON_BN_CLICKED(IDCANCLE, &CSetup_Dlg::OnBnClickedCancle)
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSetup_Dlg 메시지 처리기입니다.





void CSetup_Dlg::OnBnClickedCheckautostart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAS=CheckAutoStart.GetCheck();
}


void CSetup_Dlg::OnBnClickedCheckonlytop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OT=CheckOnlyTop.GetCheck();
}


void CSetup_Dlg::OnNMCustomdrawSlidercloaking(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//스크롤 값을 받는다.
	SC=SliderCloaking.GetPos();
	//투명도 퍼센트와 핸들을 넘겨준다.
	TP.SetTransparency(SC,AfxGetMainWnd()->m_hWnd);
	*pResult = 0;
}



void CSetup_Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//취소시 이전 스크롤값으로 전환
	SliderCloaking.SetPos(PRE_SC);
	CDialogEx::OnCancel();

}


BOOL CSetup_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgVisual();
	setFont();//글씨체
	//setup다이얼로그 초기화
	setupdlginit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSetup_Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//자동시작 on/off
	WAutoStart.setAutoStart(CAS);

	//항상위 on/off
	SetOnlyTop(OT);
	
	//IP받아오기
	GetDlgItemText(IDC_EDIT_IP,HTRoom_IP);

	CDialogEx::OnOK();
}



//세팅 초기화
void CSetup_Dlg::setupdlginit(void)
{
	//콤보박스 초기화
	CString tempstr;
	for (int i =1; i<=MAX_GRAD;i++)
	{	
		tempstr.Format("%d학년",i);
		CB_Grad.AddString(tempstr);
	}
	for (int i =1; i<=MAX_CLASS;i++)
	{	
		tempstr.Format("%d반",i);
		CB_Class.InsertString(i-1,tempstr);
	}


	if(OT){
		CheckOnlyTop.SetCheck(1);
	}
	if(CAS){
		CheckAutoStart.SetCheck(1);
	}
	if(SOUND){
		CheckSound.SetCheck(1);
	}
	SliderCloaking.SetPos(PRE_SC);

	SetDlgItemText(IDC_EDIT_IP,HTRoom_IP);

	CB_Grad.SetCurSel(Grad-1);

	CB_Class.SetCurSel(Class-1);

}


void CSetup_Dlg::SetOnlyTop(int flag)
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


void CSetup_Dlg::OnCbnSelchangeComboGrad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Grad=CB_Grad.GetCurSel()+1;
}


void CSetup_Dlg::OnCbnSelchangeComboClass()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Class=CB_Class.GetCurSel()+1;
}


void CSetup_Dlg::OnBnClickedChecksound()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SOUND = CheckSound.GetCheck();
}

void CSetup_Dlg::setFont(void)
{
	//글꼴 높이, 글꼴 너비, 방향, 회전각도, 굵기, 기울임꼴, 밑줄, 취소선, 문자 세트, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 글꼴 이름
	m_static_class .CreateFont(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_ip    .CreateFont(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_option.CreateFont(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	m_static_trans .CreateFont(17,7,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (본문)");
	

	GetDlgItem(IDC_STATIC_CLASS)  ->SetFont(&m_static_class);
	GetDlgItem(IDC_STATIC_IP)     ->SetFont(&m_static_ip);
	GetDlgItem(IDC_STATIC_OPTION) ->SetFont(&m_static_option);
	GetDlgItem(IDC_STATIC_TRANS)  ->SetFont(&m_static_trans);
}



void CSetup_Dlg::SetDlgVisual(void)
{
	SetWindowPos(&wndNoTopMost,0,0,260,390,SWP_NOMOVE);//크기 설정

	//다이얼로그 모양 재설정
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+4, rc.top+4, rc.right+2, rc.bottom-2,15,15);
	::SetWindowRgn(this->m_hWnd,(HRGN)rgn, TRUE);

	//버튼 이미지. 다이얼로그 이미지 입히기
	CString m_StrRunPath;
	CString str_bkground;
	CString str_ok_n,str_ok_c;
	CString str_cancle_n,str_cancle_c;

	CRect rect;
	CSize mSize;
	DWORD fSize;
	int width,height;

	rect=m_button_ok.getSize();
	width=rect.Width();
	height=rect.Height();

	TCHAR buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	m_StrRunPath.Format("%s",buf);

	str_ok_n.Format("%s\\Skin\\%s",m_StrRunPath,OK_NONE);
	str_ok_c.Format("%s\\Skin\\%s",m_StrRunPath,OK_CLICK);
	str_cancle_n.Format("%s\\Skin\\%s",m_StrRunPath,CANCLE_NONE);
	str_cancle_c.Format("%s\\Skin\\%s",m_StrRunPath,CANCLE_CLICK);

	m_button_ok.LoadJPG(str_ok_n,str_ok_c,str_ok_n,str_ok_n);
	m_button_cancel.LoadJPG(str_cancle_n,str_cancle_c,str_cancle_n,str_cancle_n);

	//버튼,문자열 위치 재구성
	GetDlgItem(IDOK)->MoveWindow(40,330,78,32,FALSE);
	GetDlgItem(IDCANCEL)->MoveWindow(140,330,78,32,FALSE);

	GetDlgItem(IDC_STATIC_CLASS)->MoveWindow(25,7,40,20,FALSE);
	GetDlgItem(IDC_STATIC_IP)->MoveWindow(25,77,100,60,FALSE);
	GetDlgItem(IDC_STATIC_OPTION)->MoveWindow(25,147,500,30,FALSE);
	GetDlgItem(IDC_STATIC_TRANS)->MoveWindow(25,255,70,30,FALSE);

	GetDlgItem(IDC_STATICCLASS)->MoveWindow(20,18,210,55,FALSE);
	GetDlgItem(IDC_STATICIP)->MoveWindow(20,87,210,55,FALSE);
	GetDlgItem(IDC_STATICOPTION)->MoveWindow(20,158,210,90,FALSE);
	GetDlgItem(IDC_STATICTRANS)->MoveWindow(20,265,210,55,FALSE);

	GetDlgItem(IDC_COMBO_GRAD)->MoveWindow(40,37,70,125,FALSE);
	GetDlgItem(IDC_COMBO_CLASS)->MoveWindow(140,37,70,100,FALSE);
	GetDlgItem(IDC_EDIT_IP)->MoveWindow(40,105,170,25,FALSE);
	GetDlgItem(IDC_CHECKAUTOSTART)->MoveWindow(35,173,120,15,FALSE);
	GetDlgItem(IDC_CHECKONLYTOP)->MoveWindow(35,198,120,15,FALSE);
	GetDlgItem(IDC_CHECKSOUND)->MoveWindow(35,223,120,15,FALSE);
	GetDlgItem(IDC_SLIDERCLOAKING)->MoveWindow(40,283,170,25,FALSE);


	str_bkground.Format("%s\\Skin\\%s",m_StrRunPath,SETDLG_BK);
	m_bmTool.LoadPictureFile(NULL,str_bkground, &m_bgImage, mSize, fSize);
}


void CSetup_Dlg::OnBnClickedCancle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


HBRUSH CSetup_Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(m_color_class.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(m_color_ip.m_hWnd==pWnd->m_hWnd)
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
	if(m_color_trans.m_hWnd==pWnd->m_hWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));//글자색 변경
		pDC->SetBkMode(TRANSPARENT);//배경 투명
		// pDC->SetBkColor(RGB(0,0,255));//배경색 변경
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	if(pWnd->GetDlgCtrlID() == IDC_CHECKAUTOSTART)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	if(pWnd->GetDlgCtrlID() == IDC_CHECKONLYTOP)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}

	if(pWnd->GetDlgCtrlID() == IDC_CHECKSOUND)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}


LRESULT CSetup_Dlg::OnNcHitTest(CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CDialogEx::OnNcHitTest(point);
	return HTCAPTION;
}


BOOL CSetup_Dlg::OnEraseBkgnd(CDC* pDC)
{
	RECT rt;
	GetClientRect(&rt);
	m_bmTool.Transpatent(*pDC, &m_bgImage, rt.left, rt.top, rt.right, rt.bottom);  

	return true;
}
