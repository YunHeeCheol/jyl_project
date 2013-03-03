// Dialog_Detail.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "Dialog_Detail.h"
#include "afxdialogex.h"
#include "BitmapTool.h"

// CDialog_Detail ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialog_Detail, CDialogEx)

CDialog_Detail::CDialog_Detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Detail::IDD, pParent)
{
}

CDialog_Detail::~CDialog_Detail()
{
}

void CDialog_Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STATE, m_PicState);
}


BEGIN_MESSAGE_MAP(CDialog_Detail, CDialogEx)
	ON_WM_NCHITTEST()
	ON_STN_CLICKED(IDC_STATIC_STR, &CDialog_Detail::OnStnClickedStaticStr)
END_MESSAGE_MAP()


// CDialog_Detail �޽��� ó�����Դϴ�.


BOOL CDialog_Detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(&wndNoTopMost,0,0,300,200,SWP_NOMOVE);
	SetResource();
	SetFont();
	dlginit();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDialog_Detail::dlginit(void)
{
	CRgn rgn;
	CRect rc;
	GetClientRect(rc);
	rgn.CreateRoundRectRgn(rc.left+2, rc.top+2, rc.right-2, rc.bottom-2,15,15);
	::SetWindowRgn(m_hWnd,(HRGN)rgn, TRUE);

	SetDlgItemInt(IDC_STATIC_GRAD,Grad);
	SetDlgItemInt(IDC_STATIC_CLASS,Class);
	SetDlgItemText(IDC_STATIC_CO2DATA,Co2data);
	SetDlgItemText(IDC_STATIC_TEMPDATA,Tempdata);
	SetDlgItemText(IDC_STATIC_HUMIDATA,Humidata);

	CString str_Path,fName_d,fName_w,fName_n;
	TCHAR buf[MAX_PATH];
	memset(buf,0x00,sizeof(buf));
	GetCurrentDirectory(MAX_PATH, buf);
	str_Path.Format("%s",buf);
	fName_d.Format("%s\\Skin\\%s",str_Path,STATE_D_FNAME);
	fName_w.Format("%s\\Skin\\%s",str_Path,STATE_W_FNAME);
	fName_n.Format("%s\\Skin\\%s",str_Path,STATE_N_FNAME);
	m_PicState.LoadJPG(fName_n,NULL,NULL,NULL,
		fName_w,NULL,NULL,NULL,
		fName_d,NULL,NULL,NULL
		);
	m_PicState.SetBitmapSize(150,200);
	m_PicState.Change_State(State);
}


void CDialog_Detail::SetResource(void)
{
	GetDlgItem(IDC_STATIC_STATE)->MoveWindow(150,0,50,50,FALSE);
	GetDlgItem(IDOK)->MoveWindow(25,160,100,30,FALSE);
	 
	GetDlgItem(IDC_STATIC_GRAD) ->MoveWindow(25,20,30,20,FALSE);
	GetDlgItem(IDC_STATIC_STR)  ->MoveWindow(35,20,40,20,FALSE);
	GetDlgItem(IDC_STATIC_CLASS)->MoveWindow(80,20,40,20,FALSE);
	GetDlgItem(IDC_STATIC_STR2) ->MoveWindow(100,20,30,20,FALSE);

	GetDlgItem(IDC_STATIC_CO2) ->MoveWindow(15,60,60,20,FALSE);
	GetDlgItem(IDC_STATIC_TEMP)->MoveWindow(15,90,60,20,FALSE);
	GetDlgItem(IDC_STATIC_HUMI)->MoveWindow(15,120,60,20,FALSE);

	GetDlgItem(IDC_STATIC_CO2DATA) ->MoveWindow(65,60,50,20,FALSE);
	GetDlgItem(IDC_STATIC_TEMPDATA)->MoveWindow(65,90,50,20,FALSE);
	GetDlgItem(IDC_STATIC_HUMIDATA)->MoveWindow(65,120,50,20,FALSE);

	GetDlgItem(IDC_STATIC_PPM)->MoveWindow(110,60,60,20,FALSE);
	GetDlgItem(IDC_STATIC_C)  ->MoveWindow(110,90,60,20,FALSE);
	GetDlgItem(IDC_STATIC_PER)->MoveWindow(110,120,60,20,FALSE);
}


void CDialog_Detail::SetFont(void)
{
	m_grade.CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_str1. CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_class.CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_str2. CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");

	m_co2. CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_temp.CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_humi.CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");

	m_co2data. CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_tempdata.CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_humidata.CreateFontA(20,9,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");

	m_ppm.CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_c.  CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");
	m_per.CreateFontA(17,8,0,0,1500,0,0,0,0,OUT_DEFAULT_PRECIS,0,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Century Gothic (����)");

	GetDlgItem(IDC_STATIC_GRAD) ->SetFont(&m_grade);
	GetDlgItem(IDC_STATIC_STR)  ->SetFont(&m_str1);
	GetDlgItem(IDC_STATIC_CLASS)->SetFont(&m_grade);
	GetDlgItem(IDC_STATIC_STR2) ->SetFont(&m_class);

	GetDlgItem(IDC_STATIC_CO2) ->SetFont(&m_co2);
	GetDlgItem(IDC_STATIC_TEMP)->SetFont(&m_temp);
	GetDlgItem(IDC_STATIC_HUMI)->SetFont(&m_humi);

	GetDlgItem(IDC_STATIC_CO2DATA) ->SetFont(&m_co2data);
	GetDlgItem(IDC_STATIC_TEMPDATA)->SetFont(&m_tempdata);
	GetDlgItem(IDC_STATIC_HUMIDATA)->SetFont(&m_humidata);

	GetDlgItem(IDC_STATIC_PPM)->SetFont(&m_ppm);
	GetDlgItem(IDC_STATIC_C)  ->SetFont(&m_c);
	GetDlgItem(IDC_STATIC_PER)->SetFont(&m_per);

}


LRESULT CDialog_Detail::OnNcHitTest(CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//return CDialogEx::OnNcHitTest(point);
	return HTCAPTION;
}



void CDialog_Detail::OnStnClickedStaticStr()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
