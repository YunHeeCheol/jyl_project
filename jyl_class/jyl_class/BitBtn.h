#if !defined(AFX_CBitBtn_H__54B2D889_3973_4ECA_BF65_D4D3C996E27A__INCLUDED_)
#define AFX_CBitBtn_H__54B2D889_3973_4ECA_BF65_D4D3C996E27A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CBitBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitBtn window

#include	"BitmapTool.h"

#define		STATE_UP		0
#define		STATE_DOWN		1
#define		STATE_FOCUS		2
#define		STATE_DISABLE	3

#define		NODATA		0
#define		NORMAL		1
#define		WARNING		2
#define		DANGER		3

#define     RADIO_UNSELECT  0
#define     RADIO_SELECT    1
#define     RADIO_DISABLE   3

class CBitBtn : public CButton, public CBitmapTool
{
	// Construction
public:
	CBitBtn();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitBtn)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CBitBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitBtn)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	CBitmap		*m_BitUp;
	CBitmap		*m_BitDown;
	CBitmap		*m_BitFocus;
	CBitmap		*m_BitDisable;
	CBitmap		*m_BitUp2;
	CBitmap		*m_BitDown2;
	CBitmap		*m_BitFocus2;
	CBitmap		*m_BitDisable2;
	CBitmap		*m_BitUp3;
	CBitmap		*m_BitDown3;
	CBitmap		*m_BitFocus3;
	CBitmap		*m_BitDisable3;
	//	BOOL		CopyBitmapFrom (CBitmap *pBitmap, CBitmap **dpBitMap);
	void		MakeWindowRgn();

	int			m_sizeX;
	int			m_sizeY;

	int			m_state;
	int			m_airstate;

	//HWND		m_hCBitBtn;

	CRect		m_rect;

	BOOL		m_bTransparent;


	void		OnMouseLeave(void);
	void		OnMouseEnter(void);
	BOOL		m_bMouseTracking;
	int         m_ID;
	BOOL		m_bIsRadioBtn;
public:
	
	void		SetHWND(HWND	hParent);
	BOOL		LoadJPG(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable);
	BOOL		LoadJPG(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable
						,LPCTSTR fNameUp2, LPCTSTR fNameDown2, LPCTSTR fNameFocus2, LPCTSTR fNameDisable2
						,LPCTSTR fNameUp3, LPCTSTR fNameDown3, LPCTSTR fNameFocus3, LPCTSTR fNameDisable3);
	BOOL		LoadBitmap(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable);
	BOOL		LoadBitmapByResource(UINT nIDResourceUp, UINT nIDResourceDown, UINT nIDResourceFocus, UINT nIDResourceDisable);
	void		SetBitmapSize(int iSizeX, int iSizeY);

	void		SetTransparent (BOOL bTransparent);
	void        SetBtnID(int id);
	void		SetBtnRadio( bool isSet);
	void		SetRadioState(int state);
	int			GetRadioState();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	CRect getSize(void);
	void Change_State(int state);
	void JPGCopy(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable
		,LPCTSTR fNameUp2, LPCTSTR fNameDown2, LPCTSTR fNameFocus2, LPCTSTR fNameDisable2
		,LPCTSTR fNameUp3, LPCTSTR fNameDown3, LPCTSTR fNameFocus3, LPCTSTR fNameDisable3);
	void JPGCopy(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBitBtn_H__54B2D889_3973_4ECA_BF65_D4D3C996E27A__INCLUDED_)
static LPCTSTR CopyfNameUp;
static LPCTSTR CopyfNameDown;
static LPCTSTR CopyfNameFocus;
static LPCTSTR CopyfNameDisable;
static LPCTSTR CopyfNameUp2;
static LPCTSTR CopyfNameDown2;
static LPCTSTR CopyfNameFocus2;
static LPCTSTR CopyfNameDisable2;
static LPCTSTR CopyfNameUp3;
static LPCTSTR CopyfNameDown3;
static LPCTSTR CopyfNameFocus3;
static LPCTSTR CopyfNameDisable3;