#pragma once


// CDialog_Info ��ȭ �����Դϴ�.

class CDialog_Info : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Info)

public:
	CDialog_Info(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialog_Info();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
