#pragma once
#include "SocServer.h"
#include "SocCom.h"
// CSocServer ��� ����Դϴ�.


class CSocServer : public CAsyncSocket
{
public:
	CSocServer();
	virtual ~CSocServer();

	HWND m_hWnd; 
	void Init(HWND hWnd);
	virtual void OnAccept(int nErrorCode);
};


