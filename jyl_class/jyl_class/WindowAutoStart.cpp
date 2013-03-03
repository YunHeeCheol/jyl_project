// WindowAutoStart.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "WindowAutoStart.h"


// CWindowAutoStart

IMPLEMENT_DYNAMIC(CWindowAutoStart, CWnd)

CWindowAutoStart::CWindowAutoStart()
{

}

CWindowAutoStart::~CWindowAutoStart()
{
}


BEGIN_MESSAGE_MAP(CWindowAutoStart, CWnd)
END_MESSAGE_MAP()



// CWindowAutoStart 메시지 처리기입니다.


BOOL CWindowAutoStart::SHRegReadString(HKEY hKey, LPCTSTR lpKey, 
	LPCTSTR lpValue, LPCTSTR lpDefault, LPTSTR lpRet, DWORD nSize) 
{
	HKEY  key;
	DWORD dwDisp;
	DWORD Size;

	if (RegCreateKeyEx(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_READ,NULL,&key,&dwDisp)!=ERROR_SUCCESS) 
		return FALSE;

	Size=nSize;

	if (RegQueryValueEx(key, lpValue, 0, NULL,(LPBYTE)lpRet, &Size)
		!=ERROR_SUCCESS)
	{
		strcpy(lpRet, lpDefault);
		return FALSE;
	}

	RegCloseKey(key);

	return TRUE;
}

BOOL CWindowAutoStart::SHRegWriteString(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, LPCTSTR lpData)
{
	HKEY  key;
	DWORD dwDisp;

	if (RegCreateKeyEx(hKey, lpKey,0,NULL,
		REG_OPTION_NON_VOLATILE, KEY_WRITE,NULL,&key,&dwDisp)!=ERROR_SUCCESS) 
		return FALSE;

	if (RegSetValueEx(key, lpValue,0,REG_SZ,(LPBYTE)lpData,strlen(lpData)+1)!=ERROR_SUCCESS) 
		return FALSE;

	RegCloseKey(key);

	return TRUE;
}


BOOL CWindowAutoStart::SHRegDeleteValue(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue)
{
	HKEY  key;

	if (RegOpenKeyEx(hKey, lpKey, 0, KEY_ALL_ACCESS, &key)!=ERROR_SUCCESS) 
		return FALSE;

	if (RegDeleteValue(key, lpValue)!=ERROR_SUCCESS) 
		return FALSE;

	RegCloseKey(key);

	return TRUE;
}

int CWindowAutoStart::setAutoStart(int flag)
{
	CString strWrite;
	char    szStr[MAX_PATH*3]={0};
	AfxGetMainWnd()->UpdateData(TRUE);
	if(flag)
	{
		if (SHRegReadString(HKEY_LOCAL_MACHINE, RUNKEY, AUTORUN_VALUENAME, " ", szStr, MAX_PATH*2))
		{
		}
		else
		{
			strWrite="\""; 
			strWrite+= __argv[0];
			strWrite+= "\" ";
			strWrite+= AUTORUN_ADDARGU;
			SHRegWriteString(HKEY_LOCAL_MACHINE, RUNKEY, AUTORUN_VALUENAME, strWrite);
		}
	}
	else
	{
		if (SHRegReadString(HKEY_LOCAL_MACHINE, RUNKEY, AUTORUN_VALUENAME, " ", szStr, MAX_PATH*2))
		{
			CString str;
			str=szStr;
			str.TrimLeft();
			str.TrimRight();
			if (str.GetLength() > 0)
			{
				if (str.GetAt(0)=='\"') str.Delete(0);

				int index1=str.Find(' ');
				str.Delete(index1-1, str.GetLength()+1-index1);			
			}

			if (str.CompareNoCase(__argv[0])==0)
			{
			}
			else
				SHRegDeleteValue(HKEY_LOCAL_MACHINE, RUNKEY, AUTORUN_VALUENAME);
		}
		
	}
	AfxGetMainWnd()->UpdateData(FALSE);
	return 0;
}
