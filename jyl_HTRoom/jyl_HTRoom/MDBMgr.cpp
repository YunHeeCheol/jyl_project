// CMDBMgr.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "MDBMgr.h"




CMDBMgr::CMDBMgr()
{
	::CoInitialize(NULL);

}

CMDBMgr::~CMDBMgr()
{
	::CoUninitialize();
}




void CMDBMgr::Init(void)
{
	/* Catalog(Database), Table, Column의 Object에 대한 ADOX Object 포인터 정의*/
	ADOX::_CatalogPtr m_pCatalog = NULL;
	ADOX::_TablePtr   m_pTable   = NULL;
	ADOX::_ColumnPtr  m_pColumn  = NULL;
	ADOX::_IndexPtr   m_pIndex   = NULL;

	/* 각 Object에 대한 Instance 생성*/
	m_pCatalog.CreateInstance(__uuidof (Catalog));
	m_pTable  .CreateInstance(__uuidof (Table));
	m_pIndex  .CreateInstance(__uuidof (Index));
	CString str;
	str.Format("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=%s",DB_NAME);
	try
	{
		/* Database 생성*/
		m_pCatalog->Create((const char *)str);

		/* 테이블 생성(Chart) */
		m_pTable->PutName((const char *)TB_NAME);

		/* 필드 생성(Chart Table) */
		m_pTable->Columns->Append("no"   , ADOX::adInteger, 0); // 텍스트(3번째 인자는 크기)
		m_pTable->Columns->Append("grad" , ADOX::adWChar, 1); // 텍스트
		m_pTable->Columns->Append("class", ADOX::adWChar, 1); // 텍스트
		m_pTable->Columns->Append("co2"  , ADOX::adWChar, 4); // 텍스트
		m_pTable->Columns->Append("temp" , ADOX::adWChar, 4); // 텍스트
		m_pTable->Columns->Append("humi" , ADOX::adWChar, 4); // 텍스트
		m_pTable->Columns->Append("dt"   , ADOX::adDate, 0); // 텍스트
		m_pTable->Columns->Append("lev"  , ADOX::adWChar, 1); // 텍스트

		/* "r_Number"필드의 일렬번호(Auto Increment) 속성을 주기위해 해줘야 함, 안하면 런타임 에러 */
		m_pTable->ParentCatalog = m_pCatalog;

		/* Auto Increment 속성으로 설정, 즉 값이 자동 증가함. TRUE로 하면 런타임 에러, true로 해야 함 */
		m_pTable->Columns->GetItem("no")->Properties->GetItem("AutoIncrement")->Value = true;

		/* long으로 캐스팅 해줘야 함, 안하면 런타임 에러*/
		_variant_t varValue1( (long) 1 );
		m_pTable->Columns->GetItem("no")->Properties->GetItem("Seed")->Value = varValue1;
		m_pTable->Columns->GetItem("no")->Properties->GetItem("Increment")->Value = varValue1;

		/* 인덱스와 기본키 설정(기본키를 지정하고 중복 불가능한 Unique한 인덱스 지정), 인덱스 이름은 마음대로 */
		m_pIndex->Name = "CodeIndex";
		m_pIndex->Columns->Append("no", ADOX::adInteger, 0);
		m_pIndex->PutPrimaryKey(-1);// 기본키 지정
		m_pIndex->PutUnique(-1);// 중복 불가능

		/* 설정한 인덱스를 테이블에 붙여넣는다. */
		m_pTable->Indexes->Append(_variant_t((IDispatch*)m_pIndex));

		/* 설정한 테이블을 붙여넣는다. 하나의 테이블 생성 후 제일 마지막에 하는 작업 */
		m_pCatalog->Tables->Append(_variant_t((IDispatch*)m_pTable));
	}catch (_com_error &e){
		//DataBase 생성 에러
		if(e.Error()==DB_E_DUPLICATEDATASOURCE){
			
		}else{
			AfxGetMainWnd()->MessageBox("데이터 베이스 생성 에러");
		}
	}

	HRESULT hr = S_OK;

	hr = m_pConnection.CreateInstance(__uuidof(Connection));

	if(SUCCEEDED(hr))
	{
		/* DB 연결*/
		m_pConnection->ConnectionString = _bstr_t(str);
		m_pConnection->Open("", "", "", adModeUnknown);
	}
}


void CMDBMgr::Append(CClientData* pData)
{
	CDataPack* dPack;

	dPack=pData->m_DPack;

	CString query;// 쿼리문이 저장될 변수

	/* 쿼리*/
	query.Format("INSERT INTO %s (grad,class,co2,temp,humi,dt,lev) values ('%d','%d','%s','%s','%s','%s','%d')",
		TB_NAME,
		pData->m_Grad,
		pData->m_Class,
		dPack->m_Co2,
		dPack->m_Temp,
		dPack->m_Humi,
		dPack->m_DateTime,
		dPack->m_Level
		);

	_bstr_t executeQuery = query;

	/* 트랜잭션 시작*/
	m_pConnection->BeginTrans();

	/* "추가" 쿼리 실행*/
	m_pConnection->Execute(executeQuery, NULL, adCmdText);

	/* 트랜잭션 종료*/
	m_pConnection->CommitTrans();

}


void CMDBMgr::Close(void)
{
	m_pConnection->Close();
	m_pConnection = NULL;
}


void CMDBMgr::Read(void)
{
	int count = 0;
	ADODB::_RecordsetPtr record;// DB의 레코드셋

	_bstr_t bKey;
	_bstr_t bKey2;
	_bstr_t bKey3;
	_bstr_t bKey4;
	_bstr_t bKey5;


	CString query;// 쿼리문이 저장될 변수
	CString m_Index[5][8000];


	/* 쿼리*/
	query.Format("SELECT * FROM %s",TB_NAME);

	_bstr_t executeQuery = query;

	/* 쿼리실행*/
	record = m_pConnection->Execute(executeQuery, NULL, adCmdText);

	while(!record->EndOfFile)
	{
		/* 레코드의 각 필드에서 해당정보를 가져옴*/
		bKey = record->Fields->GetItem("grad")->Value;
		bKey2= record->Fields->GetItem("class")->Value;
		bKey3= record->Fields->GetItem("co2")->Value;
		bKey4= record->Fields->GetItem("temp")->Value;
		bKey5= record->Fields->GetItem("humi")->Value;

		m_Index[0][count].Format("%s", (LPCSTR)bKey);
		m_Index[1][count].Format("%s", (LPCSTR)bKey2);
		m_Index[2][count].Format("%s", (LPCSTR)bKey3);
		m_Index[3][count].Format("%s", (LPCSTR)bKey4);
		m_Index[4][count].Format("%s", (LPCSTR)bKey5);
		/* 다음레코드로진행*/
		record->MoveNext();
		count++;
	}
	CString str,str2[8000];
	for(int i =0; i <count;i++){
		str.Format("%s,%s,%s,%s,%s\n",m_Index[0][i],m_Index[1][i],m_Index[2][i],m_Index[3][i],m_Index[4][i]);
		str2[i].Append(str);
	}
	//AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1,str2[1]);
	//AfxGetMainWnd()->SetDlgItemText(IDC_EDIT1,str2[5000]);
	/* 레코드셋 해제*/
	record->Close();
	record = NULL;
}
