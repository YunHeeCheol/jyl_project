// SocketThread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "SocketThread.h"


HWND m_hwnd;
UINT SocketThread(LPVOID pParam);
CWinThread* STThread;
// CSocketThread

IMPLEMENT_DYNAMIC(CSocketThread, CWnd)

CSocketThread::CSocketThread()
{

}

CSocketThread::~CSocketThread()
{
}


BEGIN_MESSAGE_MAP(CSocketThread, CWnd)
END_MESSAGE_MAP()



// CSocketThread 메시지 처리기입니다.

void CSocketThread::setThread(HWND hwnd)
{
	m_hwnd=hwnd;
	STThread=AfxBeginThread(SocketThread,0);
}
UINT SocketThread(LPVOID pParam)
{
	
	while(1){
		Sleep(2000);
		SendMessage(m_hwnd,WM_MYSOCKCONNECT,NULL,0);
	}
}


void CSocketThread::ThreadStop(void)
{
	STThread->SuspendThread();
}


void CSocketThread::ThreadReStart(void)
{
	STThread->ResumeThread();
}


void CSocketThread::ThreadClose(void)
{
	DWORD dwExitcode;
	if(STThread!= NULL && GetExitCodeThread(STThread->m_hThread, &dwExitcode)){
		TerminateThread(STThread->m_hThread,dwExitcode);
		delete STThread;
		STThread=NULL;
	}
}


