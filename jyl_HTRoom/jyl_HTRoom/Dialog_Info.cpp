// Dialog_Info.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "Dialog_Info.h"
#include "afxdialogex.h"


// CDialog_Info 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialog_Info, CDialogEx)

CDialog_Info::CDialog_Info(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Info::IDD, pParent)
	, m_grad(0)
	, m_class(0)
	, m_state(0)
{

}

CDialog_Info::~CDialog_Info()
{
}

void CDialog_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_Info, CDialogEx)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDialog_Info 메시지 처리기입니다.


BOOL CDialog_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//윈도우 크기 고정
	SetWindowPos(&wndNoTopMost,0,0,200,100,SWP_NOMOVE);

	//다이얼로그창 위치 설정
	SetDialogPosition();

	//글자 설정
	SetText();

	//rgn 세팅
	SetRgn();

	//애니메이션
	AnimateWindow(1000,AW_HOR_POSITIVE);

	//다이얼로그 닫힘 타이머 작동
	SetTimer(0,3000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDialog_Info::SetRgn(void)
{
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+2, rc.top+2, rc.right-2, rc.bottom-2,15,15);
	::SetWindowRgn(m_hWnd,(HRGN)rgn, TRUE);

}


void CDialog_Info::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	EndDialog(0);
	CDialogEx::OnTimer(nIDEvent);
}


void CDialog_Info::SetDialogPosition(void)
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
}


void CDialog_Info::SetText(void)
{
	GetDlgItem(IDC_STATIC_IGRAD)->MoveWindow(30,10,15,15,FALSE);
	GetDlgItem(IDC_STATIC_STR_GRAD)->MoveWindow(50,10,15,15,FALSE);
	GetDlgItem(IDC_STATIC_ICLASS)->MoveWindow(30,40,15,15,FALSE);
	GetDlgItem(IDC_STATIC_STR_CLASS)->MoveWindow(50,40,15,15,FALSE);

	SetDlgItemInt(IDC_STATIC_IGRAD,m_grad);
	SetDlgItemInt(IDC_STATIC_ICLASS,m_class);
}


void CDialog_Info::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	EndDialog(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
