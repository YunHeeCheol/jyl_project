// ComSocket.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "ComSocket.h"


// CComSocket

CComSocket::CComSocket()
{
}

CComSocket::~CComSocket()
{
}


// CComSocket 멤버 함수

void CComSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hwnd,WM_MYSOCKRECE,NULL,NULL);
	CAsyncSocket::OnReceive(nErrorCode);
}





void CComSocket::OnConnect(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(nErrorCode==0)
		SendMessage(m_hwnd,WM_MYSOCKCONNECT,NULL,CONN_SUCCES);
	else
		SendMessage(m_hwnd,WM_MYSOCKCONNECT,NULL,CONN_FAILE);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CComSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hwnd,WM_MYSOCKCLOSE,NULL,NULL);
	CAsyncSocket::OnClose(nErrorCode);
}


void CComSocket::init(HWND hwnd)
{
	m_hwnd=hwnd;
}
