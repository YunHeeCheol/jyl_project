// Dialog_Info.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "Dialog_Info.h"
#include "afxdialogex.h"


// CDialog_Info ��ȭ �����Դϴ�.

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


// CDialog_Info �޽��� ó�����Դϴ�.


BOOL CDialog_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//������ ũ�� ����
	SetWindowPos(&wndNoTopMost,0,0,200,100,SWP_NOMOVE);

	//���̾�α�â ��ġ ����
	SetDialogPosition();

	//���� ����
	SetText();

	//rgn ����
	SetRgn();

	//�ִϸ��̼�
	AnimateWindow(1000,AW_HOR_POSITIVE);

	//���̾�α� ���� Ÿ�̸� �۵�
	SetTimer(0,3000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	EndDialog(0);
	CDialogEx::OnTimer(nIDEvent);
}


void CDialog_Info::SetDialogPosition(void)
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	EndDialog(0);
	CDialogEx::OnLButtonDown(nFlags, point);
}
