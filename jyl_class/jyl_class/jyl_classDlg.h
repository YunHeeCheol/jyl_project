
// jyl_classDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxext.h"

#define TRAY_NOTIFY        (WM_APP + 100)

// Cjyl_classDlg 대화 상자
class Cjyl_classDlg : public CDialogEx
{
	// 생성입니다.
public:
	Cjyl_classDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_JYL_CLASS_DIALOG };
	CSliderCtrl m_ctrlSlider;
	int PreLevel, m_Level;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
private:

protected:
	//사운드파일 경로
	CString str_soundPath_war,str_soundPath_dan;
	//소켓
	CComSocket m_socket;
	//CO2 온도 습도 IP
	char str_co2[5],str_temp[5],str_humi[5];
	CString m_HTRoom_IP;
	//타이머 카운트
	int TimeCount;
	//데이터 패킷
	CDataPack DPack;
	//소켓및 시리얼통신 쓰레드 클래스
	CSocketThread m_sockThread;
	CSerchPort serchport;
	//시리얼 통신 클래스
	CCommNetwork *Comm;

	HICON m_hIcon;
	//설정 옵션 정보
	int m_OT,m_CAS,m_SC,m_Grad,m_Class,m_SOUND;

	CCriticalSection RestRoom;

	void MainDlgInit(void);
	void savesetup(void);
	void SetRestoreFromTray();	//트레이 복구 함수
	void SetMinimizeToTray();	//트레이 최소화 함수
	void SoundOut(int type);	//사운드 출력 함수
	void MakeLevel();
	LRESULT OnSockClose(WPARAM wpara, LPARAM lpara);
	LRESULT OnSockRece(WPARAM wpara, LPARAM lpara);
	LRESULT OnSockConnect(WPARAM wpara, LPARAM lpara);
	LRESULT OnFindPort(WPARAM port, LPARAM lpara);
	LRESULT OnClose(WPARAM length, LPARAM lpara);
	LRESULT OnReceive(WPARAM length, LPARAM lpara);
	LRESULT OnTrayIconClick(WPARAM wParam, LPARAM lParam);
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//폰트 관련 변수
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

