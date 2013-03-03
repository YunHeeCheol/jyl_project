#pragma once
#include "BitBtn.h"


// CDialog_Detail 대화 상자입니다.

class CDialog_Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Detail)

public:
	CDialog_Detail(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialog_Detail();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_DETAIL };

protected:
	CBitmap		*m_BitPicture;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int Grad;
	int Class;
	int State;
	CString Co2data;
	CString Tempdata;
	CString Humidata;

	virtual BOOL OnInitDialog();
	void SetFont(void);
	void dlginit(void);
	void SetResource(void);
	
	CFont m_grade,m_str1,m_class,m_str2;
	CFont m_co2,m_temp,m_humi;
	CFont m_co2data,m_tempdata,m_humidata;
	CFont m_ppm,m_c,m_per;
	
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	CBitBtn m_PicState;
	afx_msg void OnStnClickedStaticStr();
	
};
