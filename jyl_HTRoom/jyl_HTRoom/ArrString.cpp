// ArrString.cpp : 구현 파일입니다.
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
	static CString str_cr[]={"강원도","경기도","경상남도","경상북도","광주광역시"
		,"대구광역시","대전광역시","부산광역시","서울특별시","울산광역시"
		,"인천광역시","전라남도","전라북도","제주도","충청남도","충청북도"};
	return str_cr;
}
