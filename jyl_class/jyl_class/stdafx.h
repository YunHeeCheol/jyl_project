
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#include <afxsock.h>            // MFC ���� Ȯ��
#include "Transparency.h"
#include "WindowAutoStart.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include "CommNetwork.h"
#include <SetupAPI.h>
#include "SerchPort.h"
#include "SocketThread.h"
#include "ComSocket.h"
#include "BitBtn.h"
#include "BitmapTool.h"

using namespace std;


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define FILE_SETUP       "setup.txt"

#define FILE_SOUND_WAR   "co2yellow.wav"
#define FILE_SOUND_DAN   "co2red.wav"

#define TYPE_INFO		 0
#define TYPE_DATA        1

#define CONN_SUCCES      1
#define CONN_FAILE       2

#define STATE_NORMAL     1
#define STATE_WARNING    2
#define STATE_DANGER     3

#define SOUND_WARNING	 "co2yellow.wav"
#define SOUND_DANGER	 "co2red.wav"

#define SERVERPORT       5002

#define	WM_MYRECEIVE	 (WM_USER+1)
#define	WM_MYCLOSE		 (WM_USER+2)
#define	WM_MYRECEIVE2	 (WM_USER+3)
#define	WM_MYFINDPORT	 (WM_USER+4)
#define	WM_MYSOCKRECE    (WM_USER+5)
#define	WM_MYSOCKCONNECT (WM_USER+6)
#define	WM_MYSOCKCLOSE	 (WM_USER+7)

struct CDataPack{
	int   m_Type;
	char  m_Co2 [5];
	char  m_Temp[5];
	char  m_Humi[5];
	char  m_DateTime[17];
	int   m_Level;
};

#define SETUP_NONE   "Setup_None.jpg"
#define SETUP_CLICK  "Setup_Click.jpg"
#define TRAY_NONE    "Tray_None.jpg"
#define TRAY_CLICK   "Tray_Click.jpg"
#define EXIT_NONE    "Exit_None.jpg"
#define EXIT_CLICK   "Exit_Click.jpg"
#define BKGROUND     "���2.bmp"
#define OK_NONE      "OK_None.jpg"
#define OK_CLICK     "OK_Click.jpg"
#define CANCLE_NONE  "Cancle_None.jpg"
#define CANCLE_CLICK "Cancle_Click.jpg"
#define SETDLG_BK    "BKground2.bmp"