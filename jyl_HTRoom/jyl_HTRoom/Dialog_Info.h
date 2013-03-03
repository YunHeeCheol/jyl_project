#pragma once


// CDialog_Info 대화 상자입니다.

class CDialog_Info : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Info)

public:
	CDialog_Info(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialog_Info();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetRgn(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetDialogPosition(void);
	int m_grad;
	int m_class;
	int m_state;
	void SetText(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
