#pragma once

#include "ServerMgr.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "EndOfFile")
#import "C:\Program Files\Common Files\System\ado\msadox.dll"


using namespace ADODB;
using namespace ADOX;

// CMDBMgr

class CMDBMgr
{

public:
	CMDBMgr();
	virtual ~CMDBMgr();

protected:
	ADODB::_ConnectionPtr m_pConnection;

public:
	void Init(void);
	void Append(CClientData* pData);
	void Close(void);
	void Read(void);
};

#define		DB_NAME						"ninone.mdb"
#define		TB_NAME						"ninone"
//같은 이름의 데이터 베이스가 존재할경우
#define     DB_E_DUPLICATEDATASOURCE	(HRESULT)0x80040E17L

