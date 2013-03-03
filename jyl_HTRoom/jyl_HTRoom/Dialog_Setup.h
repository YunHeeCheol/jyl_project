#pragma once
#include "Resource.h"
#include "Transparency.h"
#include "WindowAutoStart.h"
#include "afxwin.h"
#include "BitBtn.h"
// CDialog_Setup 대화 상자입니다.

class CDialog_Setup : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Setup)

public:
	CDialog_Setup(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialog_Setup();


// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SETUP };

protected:

	CWindowAutoStart WAutoStart;
	CTransparency TP;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int OT;
	int AS;
	int SC,PRE_SC;
	int DP;
	CString str_region;
	CString str_City;
	CString str_School;
	CComboBox Combo_Region;
	CComboBox Combo_City;
	CButton Check_OnlyTop;
	CButton Check_Autostart;
	CEdit Edit_DataPeriod;
	CEdit Edit_School;
	CSliderCtrl Slider_Cloaking;
	CSpinButtonCtrl Spin_Dataperiod;
	
	afx_msg void OnBnClickedCheckAutostart();
	afx_msg void OnBnClickedCheckOnlytop();
	afx_msg void OnNMCustomdrawSliderCloaking(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	void SetResource(void);
	void SetFont(void);
	void setupdlginit(void);
	void SetOnlyTop(int flag);

	CStatic m_color_adress,m_color_data,m_color_trans,m_color_option;
	CFont m_adress,m_data,m_trans,m_option;
	
	CBitmapTool m_BackGnd;
	CBitmap m_bgImage;
	CBitBtn m_button_ok,m_button_cancel;
	
};
