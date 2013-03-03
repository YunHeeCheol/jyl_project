#pragma once
#define RUNKEY             "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define AUTORUN_VALUENAME  "TestTray01_Run"
#define AUTORUN_ADDARGU    "/logon" 

// CWindowAutoStart

class CWindowAutoStart : public CWnd
{
	DECLARE_DYNAMIC(CWindowAutoStart)

public:
	int setAutoStart(int flag);
	BOOL SHRegReadString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize);
	BOOL SHRegWriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData);
	BOOL SHRegDeleteValue(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue);
	CWindowAutoStart();
	virtual ~CWindowAutoStart();

protected:
	DECLARE_MESSAGE_MAP()
};


