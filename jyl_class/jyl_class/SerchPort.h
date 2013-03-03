#pragma once


// CSerchPort

class CSerchPort : public CWnd
{
	DECLARE_DYNAMIC(CSerchPort)

public:
	CSerchPort();
	virtual ~CSerchPort();
protected:
	DECLARE_MESSAGE_MAP()
public:
	CWinThread* SPThread;
	void setHwnd(HWND hwnd);
	void ThreadStop(void);
	void ThreadReStart(void);
	int ThreadClose(void);
};
int FindPort(void);
UINT CSerchPortThread(LPVOID pParam);
