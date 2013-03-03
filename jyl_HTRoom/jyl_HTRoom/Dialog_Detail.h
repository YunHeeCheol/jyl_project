#pragma once
#include "BitBtn.h"


// CDialog_Detail ��ȭ �����Դϴ�.

class CDialog_Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Detail)

public:
	CDialog_Detail(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialog_Detail();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_DETAIL };

protected:
	CBitmap		*m_BitPicture;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
