
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

#include "Dialog_Setup.h"
#include "Transparency.h"
#include "WindowAutoStart.h"
#include <iostream>
#include <fstream>
#include "ArrString.h"
#include "BitBtn.h"
#include "BitmapTool.h"
#include "Dialog_Detail.h"
#include "Dialog_Info.h"
#include "SocServer.h"
#include "SocCom.h"
#include "ServerMgr.h"

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

#define WIN_RECT_WIDTH  1000
#define WIN_RECT_HEIGHT 700

#define FILE_SETUP		"HTsetup.txt"

#define	SERVERPORT      5002

#define UM_ACCEPT       (WM_USER+1)
#define UM_RECEIVE      (WM_USER+2)
#define UM_CLOSE		(WM_USER+3)
#define UM_BTNSET		(WM_USER+4)
#define UM_DISCON		(WM_USER+5)

#define STATE_D_FNAME   "netural_d.bmp"
#define STATE_W_FNAME   "netural_w.bmp"
#define STATE_N_FNAME   "netural_n.bmp"
#define NON_D_FNAME     "nodata_d.bmp"
#define NON_C_FNAME     "nodata_c.bmp"
#define NON_F_FNAME     "nodata_f.bmp"
#define NOR_D_FNAME     "normal_d.bmp"
#define NOR_C_FNAME     "normal_c.bmp"
#define NOR_F_FNAME     "normal_f.bmp"
#define WAR_D_FNAME     "warning_d.bmp"
#define WAR_C_FNAME     "warning_c.bmp"
#define WAR_F_FNAME     "warning_f.bmp"
#define DAN_D_FNAME     "danger_d.bmp"
#define DAN_C_FNAME     "danger_c.bmp"
#define DAN_F_FNAME     "danger_f.bmp"
#define SET_D_FNAME     "Icon_setup_d.bmp"
#define SET_C_FNAME     "Icon_setup_c.bmp"
#define TRA_D_FNAME     "Icon_tray_d.bmp"
#define TRA_C_FNAME     "Icon_tray_c.bmp"
#define CLO_D_FNAME     "Icon_close_d.bmp"
#define CLO_C_FNAME     "Icon_close_c.bmp"
#define BACKGND_FNAME   "BackGnd2.bmp"
#define BACKGND_SET     "BKgroundset.bmp"
#define OK_NONE         "OK_None.jpg"
#define OK_CLICK        "OK_Click.jpg"
#define CANCEL_NONE     "Cancle_None.jpg"
#define CANCEL_CLICK    "Cancle_Click.jpg"


#define TYPE_INFO		0
#define TYPE_DATA		1

#define _SetTitle(str) { ((Cjyl_HTRoomDlg*)AfxGetMainWnd())->SetFrameTitle( (str) ); ::SetActiveWindow ( AfxGetMainWnd()->m_hWnd ); SetActiveWindow(); }
