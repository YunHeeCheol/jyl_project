// ReptrList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "ReptrList.h"

CReptrList::CReptrList()
{

}

CReptrList::~CReptrList()
{
	for(POSITION pos = this->GetHeadPosition(); pos != NULL;)
	{
		CClientData* pData = (CClientData*) this->GetNext(pos);
		free(pData);
		pData=NULL;
		//���� �Ҵ�� ��� ������ �����Ѵ�.
	}
	this->RemoveAll();
}



