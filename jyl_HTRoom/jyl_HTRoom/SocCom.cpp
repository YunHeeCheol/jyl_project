// SocCom.cpp : ���� �����Դϴ�.
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


// CSocCom ��� �Լ�
void CSocCom::Init(HWND hWnd)
{
	m_hWnd = hWnd;
}




void CSocCom::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, UM_RECEIVE, (WPARAM)this, 0);
	CAsyncSocket::OnReceive(nErrorCode);
}


void CSocCom::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, UM_CLOSE, (WPARAM)this, 0);
	CAsyncSocket::OnClose(nErrorCode);
}
