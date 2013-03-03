#pragma once
#include "SocServer.h"
#include "SocCom.h"
// CSocCom 명령 대상입니다.

class CSocCom : public CAsyncSocket
{
public:
	CSocCom();
	virtual ~CSocCom();
	HWND m_hWnd;
	void Init(HWND hWnd);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


