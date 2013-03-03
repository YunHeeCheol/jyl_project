// Transparency.cpp : 구현 파일입니다.
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



// CTransparency 메시지 처리기입니다.


void CTransparency::SetTransparency(int percent,HWND hwnd)
{
	int Num;
	SLWA pSetLayeredWindowAttributes = NULL;  // 함수포인터 선언, 초기화.
	HINSTANCE hmodUSER32 = LoadLibrary("USER32.DLL"); // 인스턴스 얻음.
	pSetLayeredWindowAttributes=(SLWA)GetProcAddress(hmodUSER32,"SetLayeredWindowAttributes");    //함수포인터 얻음.
	SetWindowLong(hwnd, GWL_EXSTYLE,GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	Num = (255 * percent) / 100; //Num에 알파값 대입
	if(Num < 100) 
		Num = 100; //최소값 설정
	pSetLayeredWindowAttributes(hwnd, 0, Num, LWA_ALPHA);
}