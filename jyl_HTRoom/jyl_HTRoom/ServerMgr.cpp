// ServerMgr.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "ServerMgr.h"


// CServerMgr

IMPLEMENT_DYNAMIC(CServerMgr, CWnd)

CServerMgr::CServerMgr()
{

}

CServerMgr::~CServerMgr()
{
}


BEGIN_MESSAGE_MAP(CServerMgr, CWnd)
END_MESSAGE_MAP()



// CServerMgr 메시지 처리기입니다.

void CServerMgr::InitServer(HWND hwnd)
{
	m_pHwnd = hwnd;
}

void CServerMgr::CreateServer()
{
	m_pServerSocket = new CSocServer;
	m_pServerSocket->Init(m_pHwnd);

	m_pServerSocket->Create(SERVERPORT);
	m_pServerSocket->Listen();	
}

void CServerMgr::DestroyServer()
{
	if( m_pServerSocket )
	{
		m_pServerSocket->ShutDown();
		delete m_pServerSocket;
		m_pServerSocket = NULL;
	}
}

LONG CServerMgr::OnAccept(WPARAM wParam, LPARAM lParam)
{
	char str_dataperiod[1];

	str_dataperiod[0]=(int)lParam;

	m_pClientSocket = new CSocCom;
	m_pClientSocket->Init(m_pHwnd);

	m_pServerSocket->Accept( *m_pClientSocket );
	
	//클라이언트 정보를 담는 구조체
	CClientData* data	= new CClientData;
	CDataPack*   packet = new CDataPack;

	data->m_Client=m_pClientSocket;
	data->m_DPack =packet;

	m_pClientSocket->Send(str_dataperiod,sizeof(str_dataperiod));

	m_ptrList.AddTail(data);

	return TRUE;
}

LONG CServerMgr::OnReceive(WPARAM wParam, LPARAM lParam)
{
	CDataPack data;

	if( m_ptrList.GetCount() < 1 )
		return TRUE;
	
	for( int i = 0 ; i < m_ptrList.GetCount() ; i++ )
	{
		POSITION	   pos		= m_ptrList.FindIndex(i);
		CClientData*   pData	= (CClientData*)m_ptrList.GetAt(pos);
		CSocCom*       pSocket	= pData->m_Client;

		if( pSocket == (CSocCom*)wParam )
		{			
			do
			{
				pSocket->Receive( &data, sizeof(data) );
			
				DistinctionData(&data, pData);
			}
			while( pSocket->IsSerializable() );
		}
	}

	return TRUE;
}

void CServerMgr::DistinctionData(CDataPack* data,CClientData* pClient){
	if( m_ptrList.GetCount() < 1 )
	return;

	CClientData* pData;
	POSITION     pos;

	for( int i = 0 ; i < m_ptrList.GetCount() ; i++ )
	{
		pos	   = m_ptrList.FindIndex(i);				
		pData  = (CClientData*)m_ptrList.GetAt(pos);
		if( pData == pClient ){					
			break;				
		}
		pData = NULL;
	}	
	switch( data->m_Type )
	{
	case TYPE_INFO:		
		pData->m_Grad  = data->m_Co2[0];
		pData->m_Class = data->m_Co2[1];
		break;
	case TYPE_DATA:
		pData->m_DPack = data;
		AfxGetMainWnd()->SendMessage(UM_BTNSET,(WPARAM)pData,NULL);
		break;
	}
}

LONG CServerMgr::OnClose(WPARAM wParam, LPARAM lParam)
{	
	if( m_ptrList.GetCount() < 1 )
		return TRUE;

	for( int i = 0 ; i < m_ptrList.GetCount() ; i++ )
	{
		POSITION	   pos		= m_ptrList.FindIndex(i);
		CClientData*   pData	= (CClientData*)m_ptrList.GetAt(pos);
		CSocCom*       pSocket	= pData->m_Client;

		if( pSocket == (CSocCom*)wParam )
		{	
			AfxGetMainWnd()->SendMessage(UM_DISCON,(WPARAM)pData,NULL);
			m_ptrList.RemoveAt(pos);
			free(pData);
			pData=NULL;
		}
	}
	return TRUE;
}