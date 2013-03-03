// ReptrList.cpp : 구현 파일입니다.
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
		//각각 할당된 기억 공간을 제거한다.
	}
	this->RemoveAll();
}



