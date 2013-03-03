#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSetup_Dlg ��ȭ �����Դϴ�.

class CSetup_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetup_Dlg)

public:
	int PRE_SC;
	int SC;
	int CAS;
	int OT;
	int SOUND;
	CString HTRoom_IP;
	int Grad;
	int Class;

	CSetup_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSetup_Dlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SETUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CWindowAutoStart WAutoStart;
	CTransparency TP;
	CButton CheckAutoStart;
	CButton CheckOnlyTop;
	CButton CheckSound;
	CStatic m_color_class,m_color_ip,m_color_option,m_color_trans;
	CFont m_static_class, m_static_ip, m_static_option, m_static_trans;
	CSliderCtrl SliderCloaking;
	afx_msg void OnBnClickedCheckautostart();
	afx_msg void OnBnClickedCheckonlytop();
	afx_msg void OnNMCustomdrawSlidercloaking(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void setupdlginit(void);
	void SetOnlyTop(int flag);
	void setFont(void);
	CComboBox CB_Grad;
	CComboBox CB_Class;
	afx_msg void OnCbnSelchangeComboGrad();
	afx_msg void OnCbnSelchangeComboClass();
	afx_msg void OnBnClickedChecksound();
	afx_msg void OnBnClickedCancle();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	
	void SetDlgVisual(void);

	CBitmapTool m_bmTool;
	CBitmap m_bgImage;
	CBitBtn m_button_ok,m_button_cancel;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
