// ComSocket.cpp : ���� �����Դϴ�.
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


// CComSocket ��� �Լ�

void CComSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hwnd,WM_MYSOCKRECE,NULL,NULL);
	CAsyncSocket::OnReceive(nErrorCode);
}





void CComSocket::OnConnect(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if(nErrorCode==0)
		SendMessage(m_hwnd,WM_MYSOCKCONNECT,NULL,CONN_SUCCES);
	else
		SendMessage(m_hwnd,WM_MYSOCKCONNECT,NULL,CONN_FAILE);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CComSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hwnd,WM_MYSOCKCLOSE,NULL,NULL);
	CAsyncSocket::OnClose(nErrorCode);
}


void CComSocket::init(HWND hwnd)
{
	m_hwnd=hwnd;
}
