#if !defined(AFX_COMMNETWORK_H__EBFF2555_B30D_4688_9F2F_541C596CA8C1__INCLUDED_)
#define AFX_COMMNETWORK_H__EBFF2555_B30D_4688_9F2F_541C596CA8C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommNetwork.h : header file
//
#include <afxmt.h>

#define	MAXBUF		50000
#define	InBufSize	50000
#define	OutBufSize	50000
#define ASCII_XON	0x11
#define ASCII_XOFF	0x13


/////////////////////////////////////////////////////////////////////////////
// CCommNetwork command target

class CCommNetwork : public CCmdTarget
{
	DECLARE_DYNCREATE(CCommNetwork)

	CCommNetwork();           // protected constructor used by dynamic creation
	CCommNetwork(CString port,CString baudrate,CString parity,CString databit,CString stopbit, int nFlag = 0);
	~CCommNetwork();

// Attributes
public:

// Operations
public:
	int testbit;
	CString teststr;
	
	int FindCommPort(CString PortArr[]);
	int m_nNetFlag;
	void Clear();
	void HandleClose();
	void Close();
	int Receive(LPSTR inbuf, int len);
	BOOL Send(LPCTSTR outbuf, int len);
	void ResetSerial();
	BOOL Create(HWND hWnd);
	
	HANDLE	m_hComDev;
	HWND	m_hWnd;
	
	OVERLAPPED m_OLR,m_OLW;

	CString m_sComPort;
	CString	m_sBaudRate;
	CString	m_sParity;
	CString	m_sDataBit;
	CString	m_sStopBit;
	BOOL	m_bFlowChk;
	BOOL	m_bIsOpenned;
	int		m_nLength;
	char	m_sInBuf[MAXBUF*2];
	CEvent*	m_pEvent;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommNetwork)
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CCommNetwork)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

UINT CommThread(LPVOID p);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMNETWORK_H__EBFF2555_B30D_4688_9F2F_541C596CA8C1__INCLUDED_)
