
// jyl_class.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cjyl_classApp:
// �� Ŭ������ ������ ���ؼ��� jyl_class.cpp�� �����Ͻʽÿ�.
//

class Cjyl_classApp : public CWinApp
{
public:
	Cjyl_classApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cjyl_classApp theApp;