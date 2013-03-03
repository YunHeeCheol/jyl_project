// Transparency.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "Transparency.h"


// CTransparency

IMPLEMENT_DYNAMIC(CTransparency, CWnd)

CTransparency::CTransparency()
{

}

CTransparency::~CTransparency()
{
}


BEGIN_MESSAGE_MAP(CTransparency, CWnd)
END_MESSAGE_MAP()



// CTransparency �޽��� ó�����Դϴ�.


void CTransparency::SetTransparency(int percent,HWND hwnd)
{
	int Num;
	SLWA pSetLayeredWindowAttributes = NULL;  // �Լ������� ����, �ʱ�ȭ.
	HINSTANCE hmodUSER32 = LoadLibrary("USER32.DLL"); // �ν��Ͻ� ����.
	pSetLayeredWindowAttributes=(SLWA)GetProcAddress(hmodUSER32,"SetLayeredWindowAttributes");    //�Լ������� ����.
	SetWindowLong(hwnd, GWL_EXSTYLE,GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	Num = (255 * percent) / 100; //Num�� ���İ� ����
	if(Num < 100) 
		Num = 100; //�ּҰ� ����
	pSetLayeredWindowAttributes(hwnd, 0, Num, LWA_ALPHA);
}