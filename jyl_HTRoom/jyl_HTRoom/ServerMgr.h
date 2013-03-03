#pragma once
#include "ReptrList.h"

struct CDataPack{
	int   m_Type;
	char  m_Co2 [5];
	char  m_Temp[5];
	char  m_Humi[5];
	char  m_DateTime[17];
	int   m_Level;
};

struct CClientData{
	int	       m_Grad;
	int		   m_Class;
	CSocCom*   m_Client;
	CDataPack* m_DPack;
	CClientData(){
		m_Grad  =0;
		m_Class =0;
		m_Client=NULL;
		m_DPack =NULL;
	}
	virtual ~CClientData(){
		m_Grad =0;
		m_Class=0;
		if(m_Client){
			m_Client->Close();
			free(m_Client);
			m_Client=NULL;
		}
		if(m_DPack){
			free(m_DPack);
			m_DPack =NULL;
		}
	}
};

// CServerMgr

class CServerMgr : public CWnd
{
	DECLARE_DYNAMIC(CServerMgr)

public:
	CServerMgr();
	virtual ~CServerMgr();

protected:
	//HWND m_pHwnd;
	DECLARE_MESSAGE_MAP()
public:
	HWND m_pHwnd;
	CSocServer*		m_pServerSocket;	
	CSocCom*		m_pClientSocket;
	CReptrList		m_ptrList;
	void InitServer(HWND hwnd);
	void CreateServer();
	void DestroyServer();
	void DistinctionData(CDataPack* data,CClientData* pClient);
	LONG OnAccept(WPARAM wParam, LPARAM lParam);
	LONG OnReceive(WPARAM wParam, LPARAM lParam);
	LONG OnClose(WPARAM wParam, LPARAM lParam);
};


