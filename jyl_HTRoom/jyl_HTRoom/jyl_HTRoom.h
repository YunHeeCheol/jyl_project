
// jyl_HTRoom.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cjyl_HTRoomApp:
// �� Ŭ������ ������ ���ؼ��� jyl_HTRoom.cpp�� �����Ͻʽÿ�.
//

class Cjyl_HTRoomApp : public CWinApp
{
public:
	Cjyl_HTRoomApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cjyl_HTRoomApp theApp;