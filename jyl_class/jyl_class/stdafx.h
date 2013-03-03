
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원


#include <afxsock.h>            // MFC 소켓 확장
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
#define BKGROUND     "배경2.bmp"
#define OK_NONE      "OK_None.jpg"
#define OK_CLICK     "OK_Click.jpg"
#define CANCLE_NONE  "Cancle_None.jpg"
#define CANCLE_CLICK "Cancle_Click.jpg"
#define SETDLG_BK    "BKground2.bmp"