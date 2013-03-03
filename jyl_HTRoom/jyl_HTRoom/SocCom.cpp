// SocCom.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SocCom.h"


// CSocCom

CSocCom::CSocCom()
{
}

CSocCom::~CSocCom()
{
}


// CSocCom 멤버 함수
void CSocCom::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}




void CSocCom::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_RECEIVE, (WPARAM)this, 0);
	CAsyncSocket::OnReceive(nErrorCode);
}


void CSocCom::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, UM_CLOSE, (WPARAM)this, 0);
	CAsyncSocket::OnClose(nErrorCode);
}
