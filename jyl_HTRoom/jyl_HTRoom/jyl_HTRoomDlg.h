
// jyl_HTRoomDlg.h : ��� ����
//

#define TRAY_NOTIFY        (WM_APP + 100)

#pragma once
#include "afxwin.h"
#include "BitBtn.h"
#include "MDBMgr.h"

// Cjyl_HTRoomDlg ��ȭ ����
class Cjyl_HTRoomDlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cjyl_HTRoomDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JYL_HTROOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	CServerMgr		m_ServerMgr;
	CDialog_Detail* pDlg;
	CSocServer		m_socServer;
	CSocCom*		m_socCom;
	void SetOnlyTop(int flag);
	void MaindlgInit(void);
	void savesetup(void);
	void Skin_init(void);
	void Open_setupDlg(void);
	void SetRestoreFromTray();	//Ʈ���� ���� �Լ�
	void SetMinimizeToTray();   //Ʈ���� �ּ�ȭ �Լ�
	void OpenDetaildlg(int grad_num,int class_num);
	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	bool		 Tray_Flag;
	CBitmapTool  m_BackGnd;
	CBitmap		 m_bgImage;
	CBitBtn		 Icon_Setup;
	CBitBtn		 Icon_Tray;
	CBitBtn		 Icon_Close;
	CMDBMgr		 m_MDBMgr;
	int			 m_OT;
	int			 m_AS;
	int			 m_SC;
	int			 m_DP;
	CDataPack	 ClassData[7][13];
	CBitBtn		 GradClass[7][13];
	CString		 m_str_region;
	CString		 m_str_City;
	CString		 m_str_School;
	HICON		 m_hIcon;

public:
	LPARAM OnAccept(WPARAM wParam, LPARAM lParam);
	LPARAM OnReceive(WPARAM wParam, LPARAM lParam);
	LPARAM OnClose(WPARAM wParam, LPARAM lParam);
	LPARAM OnBtnSet(WPARAM wParam, LPARAM lParam);
	LPARAM OnDisCon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonTray();
	afx_msg void OnTraySetup();
	afx_msg void OnTrayOnlytop();
	afx_msg void OnTrayAutostart();
	afx_msg void OnTrayOpen();
	afx_msg void OnTrayFinish();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedSetup();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	LRESULT OnTrayIconClick(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton1();
	inline void SetFrameTitle(CString str) {SetWindowText(str);};
};