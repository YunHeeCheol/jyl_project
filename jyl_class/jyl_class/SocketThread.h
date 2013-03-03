#pragma once


// CSocketThread

class CSocketThread : public CWnd
{
	DECLARE_DYNAMIC(CSocketThread)

public:
	CSocketThread();
	virtual ~CSocketThread();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void setThread(HWND hwnd);
	void ThreadStop(void);
	void ThreadReStart(void);
	void ThreadClose(void);
};


