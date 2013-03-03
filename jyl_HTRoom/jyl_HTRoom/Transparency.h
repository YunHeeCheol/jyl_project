#pragma once

#define WS_EX_LAYERED           0x00080000
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004

typedef BOOL (WINAPI *SLWA)( HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags );

// CTransparency

class CTransparency : public CWnd
{
	DECLARE_DYNAMIC(CTransparency)

public:
	HINSTANCE hmodUSER32;
	void SetTransparency(int percent,HWND hwnd);
	CTransparency();
	virtual ~CTransparency();

protected:
	
	DECLARE_MESSAGE_MAP()
};


