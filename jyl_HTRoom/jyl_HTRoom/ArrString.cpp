// ArrString.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "jyl_HTRoom.h"
#include "ArrString.h"

CArrString::CArrString()
{
	
}

CArrString::~CArrString()
{
}

CString* CArrString::getRegionStr(void)
{
	static CString str_cr[]={"������","��⵵","��󳲵�","���ϵ�","���ֱ�����"
		,"�뱸������","����������","�λ걤����","����Ư����","��걤����"
		,"��õ������","���󳲵�","����ϵ�","���ֵ�","��û����","��û�ϵ�"};
	return str_cr;
}
