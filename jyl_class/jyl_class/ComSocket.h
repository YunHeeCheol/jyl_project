#pragma once

// CComSocket ��� ����Դϴ�.

class CComSocket : public CAsyncSocket
{
public:
	HWND m_hwnd;
	CComSocket();
	virtual ~CComSocket();

	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	void init(HWND hwnd);
};


