// CSerchPort.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_class.h"
#include "SerchPort.h"


// CSerchPort
HWND parenthwnd;


IMPLEMENT_DYNAMIC(CSerchPort, CWnd)

CSerchPort::CSerchPort()
{

}

CSerchPort::~CSerchPort()
{
}


BEGIN_MESSAGE_MAP(CSerchPort, CWnd)
END_MESSAGE_MAP()



// CSerchPort �޽��� ó�����Դϴ�.


UINT CSerchPortThread(LPVOID pParam)
{
	while(true){
		int num=0;
		char temp[50];
		memset(temp,'\0',50);
		num=FindPort();
		if(!(num<1)){
			SendMessage(parenthwnd,WM_MYFINDPORT,num,NULL);
			Sleep(0);
		}
	}
	return 0;
}

int FindPort(void)
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;
	char str_buffer[100];
	int comport_num;
	hDevInfo = SetupDiGetClassDevs(NULL,
		0, 
		0,
		DIGCF_PRESENT | DIGCF_ALLCLASSES );
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (i=0;SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData);i++)
	{
		DWORD DataT;
		LPTSTR buffer = NULL;
		DWORD buffersize = 0;
		int i=SPDRP_DEVICEDESC;

		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,
			&DataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() ==ERROR_INSUFFICIENT_BUFFER)
			{
				if (buffer) LocalFree(buffer);
				buffer = (char*)LocalAlloc(LPTR,buffersize * 2);
			}
			else
			{
				break;
			}
		}

		sprintf(str_buffer,"%s\n",buffer);
		//����� usb��Ʈ �ø��� �Է�
		if(strstr(str_buffer,"Silicon Labs CP210x USB to UART Bridge"))
		{
			comport_num=0;
			int str_length=strlen(str_buffer);
			if((str_buffer[str_length-4]-'0')>=0&&(str_buffer[str_length-4]-'0')<=9){
				//��Ʈ��ȣ 10�ڸ�
				comport_num=(str_buffer[str_length-4]-'0')*10;
				//��Ʈ��ȣ 1�ڸ�
				comport_num+=str_buffer[str_length-3]-'0';
			}
			else
				//��Ʈ��ȣ 1�ڸ�
				comport_num+=str_buffer[str_length-3]-'0';
			SetupDiDestroyDeviceInfoList(hDevInfo);
			return comport_num;

		}

	}
	if ( GetLastError()!=NO_ERROR &&
		GetLastError()!=ERROR_NO_MORE_ITEMS )
	{
		return -1;
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);
	return -1;

}

void CSerchPort::setHwnd(HWND hwnd)
{
	//m_hWnd=hwnd;
	parenthwnd=hwnd;
	SPThread=AfxBeginThread(CSerchPortThread,0);
}


void CSerchPort::ThreadStop(void)
{
	SPThread->SuspendThread();
}


void CSerchPort::ThreadReStart(void)
{
	SPThread->ResumeThread();
}


int CSerchPort::ThreadClose(void)
{
	DWORD dwExitcode;
	if(SPThread!= NULL && GetExitCodeThread(SPThread->m_hThread, &dwExitcode)){
		TerminateThread(SPThread->m_hThread,dwExitcode);
		delete SPThread;
		SPThread=NULL;
	}
	return 0;
}
