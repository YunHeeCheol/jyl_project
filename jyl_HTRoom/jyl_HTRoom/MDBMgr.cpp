// CMDBMgr.cpp : ���� �����Դϴ�.
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
	/* Catalog(Database), Table, Column�� Object�� ���� ADOX Object ������ ����*/
	ADOX::_CatalogPtr m_pCatalog = NULL;
	ADOX::_TablePtr   m_pTable   = NULL;
	ADOX::_ColumnPtr  m_pColumn  = NULL;
	ADOX::_IndexPtr   m_pIndex   = NULL;

	/* �� Object�� ���� Instance ����*/
	m_pCatalog.CreateInstance(__uuidof (Catalog));
	m_pTable  .CreateInstance(__uuidof (Table));
	m_pIndex  .CreateInstance(__uuidof (Index));
	CString str;
	str.Format("Provider=Microsoft.Jet.OLEDB.4.0; Data Source=%s",DB_NAME);
	try
	{
		/* Database ����*/
		m_pCatalog->Create((const char *)str);

		/* ���̺� ����(Chart) */
		m_pTable->PutName((const char *)TB_NAME);

		/* �ʵ� ����(Chart Table) */
		m_pTable->Columns->Append("no"   , ADOX::adInteger, 0); // �ؽ�Ʈ(3��° ���ڴ� ũ��)
		m_pTable->Columns->Append("grad" , ADOX::adWChar, 1); // �ؽ�Ʈ
		m_pTable->Columns->Append("class", ADOX::adWChar, 1); // �ؽ�Ʈ
		m_pTable->Columns->Append("co2"  , ADOX::adWChar, 4); // �ؽ�Ʈ
		m_pTable->Columns->Append("temp" , ADOX::adWChar, 4); // �ؽ�Ʈ
		m_pTable->Columns->Append("humi" , ADOX::adWChar, 4); // �ؽ�Ʈ
		m_pTable->Columns->Append("dt"   , ADOX::adDate, 0); // �ؽ�Ʈ
		m_pTable->Columns->Append("lev"  , ADOX::adWChar, 1); // �ؽ�Ʈ

		/* "r_Number"�ʵ��� �ϷĹ�ȣ(Auto Increment) �Ӽ��� �ֱ����� ����� ��, ���ϸ� ��Ÿ�� ���� */
		m_pTable->ParentCatalog = m_pCatalog;

		/* Auto Increment �Ӽ����� ����, �� ���� �ڵ� ������. TRUE�� �ϸ� ��Ÿ�� ����, true�� �ؾ� �� */
		m_pTable->Columns->GetItem("no")->Properties->GetItem("AutoIncrement")->Value = true;

		/* long���� ĳ���� ����� ��, ���ϸ� ��Ÿ�� ����*/
		_variant_t varValue1( (long) 1 );
		m_pTable->Columns->GetItem("no")->Properties->GetItem("Seed")->Value = varValue1;
		m_pTable->Columns->GetItem("no")->Properties->GetItem("Increment")->Value = varValue1;

		/* �ε����� �⺻Ű ����(�⺻Ű�� �����ϰ� �ߺ� �Ұ����� Unique�� �ε��� ����), �ε��� �̸��� ������� */
		m_pIndex->Name = "CodeIndex";
		m_pIndex->Columns->Append("no", ADOX::adInteger, 0);
		m_pIndex->PutPrimaryKey(-1);// �⺻Ű ����
		m_pIndex->PutUnique(-1);// �ߺ� �Ұ���

		/* ������ �ε����� ���̺� �ٿ��ִ´�. */
		m_pTable->Indexes->Append(_variant_t((IDispatch*)m_pIndex));

		/* ������ ���̺��� �ٿ��ִ´�. �ϳ��� ���̺� ���� �� ���� �������� �ϴ� �۾� */
		m_pCatalog->Tables->Append(_variant_t((IDispatch*)m_pTable));
	}catch (_com_error &e){
		//DataBase ���� ����
		if(e.Error()==DB_E_DUPLICATEDATASOURCE){
			
		}else{
			AfxGetMainWnd()->MessageBox("������ ���̽� ���� ����");
		}
	}

	HRESULT hr = S_OK;

	hr = m_pConnection.CreateInstance(__uuidof(Connection));

	if(SUCCEEDED(hr))
	{
		/* DB ����*/
		m_pConnection->ConnectionString = _bstr_t(str);
		m_pConnection->Open("", "", "", adModeUnknown);
	}
}


void CMDBMgr::Append(CClientData* pData)
{
	CDataPack* dPack;

	dPack=pData->m_DPack;

	CString query;// �������� ����� ����

	/* ����*/
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

	/* Ʈ����� ����*/
	m_pConnection->BeginTrans();

	/* "�߰�" ���� ����*/
	m_pConnection->Execute(executeQuery, NULL, adCmdText);

	/* Ʈ����� ����*/
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
	ADODB::_RecordsetPtr record;// DB�� ���ڵ��

	_bstr_t bKey;
	_bstr_t bKey2;
	_bstr_t bKey3;
	_bstr_t bKey4;
	_bstr_t bKey5;


	CString query;// �������� ����� ����
	CString m_Index[5][8000];


	/* ����*/
	query.Format("SELECT * FROM %s",TB_NAME);

	_bstr_t executeQuery = query;

	/* ��������*/
	record = m_pConnection->Execute(executeQuery, NULL, adCmdText);

	while(!record->EndOfFile)
	{
		/* ���ڵ��� �� �ʵ忡�� �ش������� ������*/
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
		/* �������ڵ������*/
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
	/* ���ڵ�� ����*/
	record->Close();
	record = NULL;
}
