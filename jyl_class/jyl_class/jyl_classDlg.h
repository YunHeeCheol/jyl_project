
// jyl_classDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxext.h"

#define TRAY_NOTIFY        (WM_APP + 100)

// Cjyl_classDlg ��ȭ ����
class Cjyl_classDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	Cjyl_classDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_JYL_CLASS_DIALOG };
	CSliderCtrl m_ctrlSlider;
	int PreLevel, m_Level;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


	// �����Դϴ�.
private:

protected:
	//�������� ���
	CString str_soundPath_war,str_soundPath_dan;
	//����
	CComSocket m_socket;
	//CO2 �µ� ���� IP
	char str_co2[5],str_temp[5],str_humi[5];
	CString m_HTRoom_IP;
	//Ÿ�̸� ī��Ʈ
	int TimeCount;
	//������ ��Ŷ
	CDataPack DPack;
	//���Ϲ� �ø������ ������ Ŭ����
	CSocketThread m_sockThread;
	CSerchPort serchport;
	//�ø��� ��� Ŭ����
	CCommNetwork *Comm;

	HICON m_hIcon;
	//���� �ɼ� ����
	int m_OT,m_CAS,m_SC,m_Grad,m_Class,m_SOUND;

	CCriticalSection RestRoom;

	void MainDlgInit(void);
	void savesetup(void);
	void SetRestoreFromTray();	//Ʈ���� ���� �Լ�
	void SetMinimizeToTray();	//Ʈ���� �ּ�ȭ �Լ�
	void SoundOut(int type);	//���� ��� �Լ�
	void MakeLevel();
	LRESULT OnSockClose(WPARAM wpara, LPARAM lpara);
	LRESULT OnSockRece(WPARAM wpara, LPARAM lpara);
	LRESULT OnSockConnect(WPARAM wpara, LPARAM lpara);
	LRESULT OnFindPort(WPARAM port, LPARAM lpara);
	LRESULT OnClose(WPARAM length, LPARAM lpara);
	LRESULT OnReceive(WPARAM length, LPARAM lpara);
	LRESULT OnTrayIconClick(WPARAM wParam, LPARAM lParam);
	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//��Ʈ ���� ����
	CStatic m_color_co2,m_color_temp,m_color_humi;
	CStatic m_color_co2data,m_color_tempdata,m_color_humidata;
	CStatic m_color_ppm,m_color_c,m_color_per;
	CFont m_static_co2,m_static_temp,m_static_humi;
	CFont m_static_co2data,m_static_tempdata,m_static_humidata;
	CFont m_static_ppm,m_static_c,m_static_per;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedButtonSetup();
	afx_msg void OnBnClickedButtonTray();
	afx_msg void OnTrayOpen();
	afx_msg void OnTraySetup();
	afx_msg void OnTrayFinish();
	afx_msg void OnUpdateTrayOnlytop(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButtonCancle();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateTrayAutostart(CCmdUI *pCmdUI);
	afx_msg void OnDestroy();
	void Open_setupDlg(void);
	void setFont(void);
	void sendDataPacket(int Type);
	void SetDlgVisual(void);
	
	bool Tray_Flag;
	CBitBtn m_button_setup,m_button_tray,m_button_exit;
	CBitmapTool m_bmTool;
	CBitmap m_bgImage;
};

