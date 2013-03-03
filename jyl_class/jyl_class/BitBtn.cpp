// CBitBtn.cpp : implementation file
//

#include "stdafx.h"
#include "BitBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitBtn

CBitBtn::CBitBtn()
{
	m_bTransparent			=	FALSE;
	//m_hCBitBtn			=	NULL;
	m_bMouseTracking		=	FALSE;
	m_state					=	STATE_UP;
	m_airstate              =   STATE_NORMAL;
	m_bIsRadioBtn			=   FALSE;
	m_BitUp					=	NULL;
	m_BitDown				=	NULL;
	m_BitFocus				=	NULL;
	m_BitDisable			=	NULL;
	m_BitUp2				=	NULL;
	m_BitDown2				=	NULL;
	m_BitFocus2				=	NULL;
	m_BitDisable2			=	NULL;
	m_BitUp3				=	NULL;
	m_BitDown3				=	NULL;
	m_BitFocus3				=	NULL;
	m_BitDisable3			=	NULL;

}

CBitBtn::~CBitBtn()
{
	if( m_BitUp != NULL )
	{
		m_BitUp->DeleteObject();
		delete m_BitUp;
	}

	if( m_BitDown != NULL )
	{
		m_BitDown->DeleteObject();
		delete m_BitDown;
	}


	if( m_BitFocus != NULL )
	{
		m_BitFocus->DeleteObject();
		delete m_BitFocus;
	}


	if( m_BitDisable != NULL )
	{
		m_BitDisable->DeleteObject();
		delete m_BitDisable;
	}

}


BEGIN_MESSAGE_MAP(CBitBtn, CButton)
	//{{AFX_MSG_MAP(CBitBtn)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ENABLE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	//ON_MESSAGE(BM_SETCHECK , OnBMSetCheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitBtn message handlers

/*
BOOL CBitBtn :: CopyBitmapFrom (CBitmap *pBitmap, CBitmap **dpBitMap)
{

// Get the bitmap information
BITMAP bmSrc;
pBitmap->GetBitmap (&bmSrc);

// Get a DC to the source bitmap
CDC dcSrc;
dcSrc.CreateCompatibleDC (NULL);
CBitmap *bmSrcOld = dcSrc.SelectObject (pBitmap);

// Create a new bitmap
*dpBitMap = new CBitmap;

if (! (*dpBitMap)->CreateCompatibleBitmap(&dcSrc, bmSrc.bmWidth, bmSrc.bmHeight))
return FALSE;

// Get a DC to the destination bitmap
CDC dcDst;
dcDst.CreateCompatibleDC (NULL);
CBitmap *bmDstOld = dcDst.SelectObject (*dpBitMap);

// Copy the bitmap
dcDst.BitBlt (0, 0, bmSrc.bmWidth, bmSrc.bmHeight, &dcSrc, 0, 0, SRCCOPY);

// Release
dcSrc.SelectObject (bmSrcOld);
dcDst.SelectObject (bmDstOld);
dcSrc.DeleteDC ();
dcDst.DeleteDC ();

MakeWindowRgn ();

return TRUE;
}
*/
void CBitBtn :: MakeWindowRgn ()
{
	CRect rc;
	GetWindowRect (rc);
	CRgn rgn;
	rgn.CreateRectRgn (0, 0, rc.Width(), rc.Height());
	SetWindowRgn (rgn, TRUE);
}

void CBitBtn :: SetTransparent (BOOL bTransparent)
{
	m_bTransparent = bTransparent;
	MakeWindowRgn ();
}


void CBitBtn::SetBitmapSize(int iSizeX, int iSizeY)
{
	m_sizeX = iSizeX;
	m_sizeY	= iSizeY;
	Invalidate();
}

BOOL CBitBtn::LoadBitmapByResource(UINT nIDResourceUp, UINT nIDResourceDown, UINT nIDResourceFocus, UINT nIDResourceDisable)
{

	// Load the bitmap
	if( NULL != nIDResourceUp )
	{
		m_BitUp = new CBitmap;

		if( !m_BitUp->LoadBitmap (nIDResourceUp) )	return FALSE;

	}

	if( NULL != nIDResourceDown )
	{
		m_BitDown = new CBitmap;

		if( !m_BitDown->LoadBitmap (nIDResourceDown) )	return FALSE;

	}

	if( NULL != nIDResourceFocus )
	{
		m_BitFocus = new CBitmap;

		if( !m_BitFocus->LoadBitmap (nIDResourceFocus) )	return FALSE;

	}

	if( NULL != nIDResourceDisable )
	{
		m_BitDisable = new CBitmap;

		if( !m_BitDisable->LoadBitmap (nIDResourceDisable) )	return FALSE;
	}


	MakeWindowRgn();

	return TRUE;
}

BOOL CBitBtn::LoadJPG(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable )
{
	CSize mSizexx;
	CSize mSize;
	DWORD fSize;

	if( m_BitUp != NULL )
	{
		m_BitUp->DeleteObject();
		delete m_BitUp;
	}

	if( m_BitDown != NULL )
	{
		m_BitDown->DeleteObject();
		delete m_BitDown;
		m_state = STATE_UP;
	}


	if( m_BitFocus != NULL )
	{
		m_BitFocus->DeleteObject();
		delete m_BitFocus;
	}


	if( m_BitDisable != NULL )
	{
		m_BitDisable->DeleteObject();
		delete m_BitDisable;
	}

	m_state = STATE_UP;

	m_BitUp = new CBitmap();
	m_BitDown = new CBitmap();
	m_BitFocus = new CBitmap();
	m_BitDisable = new CBitmap();

	// Up Img
	if( NULL != fNameUp && strlen((char *)fNameUp) )
	{
		LoadJPGFile(NULL, fNameUp, m_BitUp, mSize, fSize);
	}

	mSizexx = mSize;
	// Down Img
	if( NULL != fNameDown && strlen((char *)fNameDown) )
	{
		LoadJPGFile(NULL, fNameDown, m_BitDown,mSize, fSize);
	}

	// Focus Img
	if( NULL != fNameFocus && strlen((char *)fNameFocus) )
	{
		LoadJPGFile(NULL, fNameFocus, m_BitFocus, mSize, fSize);
	}

	// Disable Img
	if( NULL != fNameDisable && strlen((char *)fNameDisable) )
	{
		LoadJPGFile(NULL, fNameDisable, m_BitDisable, mSize, fSize);
	}

	m_sizeX = mSizexx.cx;
	m_sizeY	= mSizexx.cy;

	MakeWindowRgn();

	return TRUE;
}

void CBitBtn::JPGCopy(void)
{
	LoadJPG(CopyfNameUp,CopyfNameDown,CopyfNameFocus,CopyfNameDisable,
		CopyfNameUp2,CopyfNameDown2,CopyfNameFocus2,CopyfNameDisable2,
		CopyfNameUp3,CopyfNameDown3,CopyfNameFocus3,CopyfNameDisable3);
}

void CBitBtn::JPGCopy(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable
	,LPCTSTR fNameUp2, LPCTSTR fNameDown2, LPCTSTR fNameFocus2, LPCTSTR fNameDisable2
	,LPCTSTR fNameUp3, LPCTSTR fNameDown3, LPCTSTR fNameFocus3, LPCTSTR fNameDisable3)
{
	CopyfNameUp       = fNameUp;
	CopyfNameDown     = fNameDown;
	CopyfNameFocus    = fNameFocus;
	CopyfNameDisable  = fNameDisable;
	CopyfNameUp2      = fNameUp2;
	CopyfNameDown2    = fNameDown2;
	CopyfNameFocus2   = fNameFocus2;
	CopyfNameDisable2 = fNameDisable2;
	CopyfNameUp3      = fNameUp3;
	CopyfNameDown3    = fNameDown3;
	CopyfNameFocus3   = fNameFocus3;
	CopyfNameDisable3 = fNameDisable3;
}

BOOL CBitBtn::LoadJPG(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable
	,LPCTSTR fNameUp2, LPCTSTR fNameDown2, LPCTSTR fNameFocus2, LPCTSTR fNameDisable2
	,LPCTSTR fNameUp3, LPCTSTR fNameDown3, LPCTSTR fNameFocus3, LPCTSTR fNameDisable3)
{
	
	CSize mSizexx;
	CSize mSize;
	DWORD fSize;

	if( m_BitUp != NULL )
	{
		m_BitUp->DeleteObject();
		delete m_BitUp;
	}

	if( m_BitDown != NULL )
	{
		m_BitDown->DeleteObject();
		delete m_BitDown;
		m_state = STATE_UP;
	}


	if( m_BitFocus != NULL )
	{
		m_BitFocus->DeleteObject();
		delete m_BitFocus;
	}


	if( m_BitDisable != NULL )
	{
		m_BitDisable->DeleteObject();
		delete m_BitDisable;
	}

	if( m_BitUp2 != NULL )
	{
		m_BitUp2->DeleteObject();
		delete m_BitUp2;
	}

	if( m_BitDown2 != NULL )
	{
		m_BitDown2->DeleteObject();
		delete m_BitDown2;
		m_state = STATE_UP;
	}


	if( m_BitFocus2 != NULL )
	{
		m_BitFocus2->DeleteObject();
		delete m_BitFocus2;
	}


	if( m_BitDisable2 != NULL )
	{
		m_BitDisable2->DeleteObject();
		delete m_BitDisable2;
	}

	if( m_BitUp3 != NULL )
	{
		m_BitUp3->DeleteObject();
		delete m_BitUp3;
	}

	if( m_BitDown3 != NULL )
	{
		m_BitDown3->DeleteObject();
		delete m_BitDown3;
		m_state = STATE_UP;
	}


	if( m_BitFocus3 != NULL )
	{
		m_BitFocus3->DeleteObject();
		delete m_BitFocus3;
	}


	if( m_BitDisable3 != NULL )
	{
		m_BitDisable3->DeleteObject();
		delete m_BitDisable3;
	}

	m_state = STATE_UP;
	
	m_BitUp       = new CBitmap();
	m_BitDown     = new CBitmap();
	m_BitFocus    = new CBitmap();
	m_BitDisable  = new CBitmap();
	m_BitUp2      = new CBitmap();
	m_BitDown2    = new CBitmap();
	m_BitFocus2   = new CBitmap();
	m_BitDisable2 = new CBitmap();
	m_BitUp3      = new CBitmap();
	m_BitDown3    = new CBitmap();
	m_BitFocus3   = new CBitmap();
	m_BitDisable3 = new CBitmap();

	// Up Img
	if( NULL != fNameUp && strlen((char *)fNameUp) )
	{
		LoadJPGFile(NULL, fNameUp, m_BitUp, mSize, fSize);
	}

	mSizexx = mSize;
	// Down Img
	if( NULL != fNameDown && strlen((char *)fNameDown) )
	{
		LoadJPGFile(NULL, fNameDown, m_BitDown,mSize, fSize);
	}

	// Focus Img
	if( NULL != fNameFocus && strlen((char *)fNameFocus) )
	{
		LoadJPGFile(NULL, fNameFocus, m_BitFocus, mSize, fSize);
	}

	// Disable Img
	if( NULL != fNameDisable && strlen((char *)fNameDisable) )
	{
		LoadJPGFile(NULL, fNameDisable, m_BitDisable, mSize, fSize);
	}

	// Up Img
	if( NULL != fNameUp2 && strlen((char *)fNameUp2) )
	{
		LoadJPGFile(NULL, fNameUp2, m_BitUp2, mSize, fSize);
	}

	mSizexx = mSize;
	// Down Img
	if( NULL != fNameDown2 && strlen((char *)fNameDown2) )
	{
		LoadJPGFile(NULL, fNameDown2, m_BitDown2,mSize, fSize);
	}

	// Focus Img
	if( NULL != fNameFocus2 && strlen((char *)fNameFocus2) )
	{
		LoadJPGFile(NULL, fNameFocus2, m_BitFocus2, mSize, fSize);
	}

	// Disable Img
	if( NULL != fNameDisable2 && strlen((char *)fNameDisable2) )
	{
		LoadJPGFile(NULL, fNameDisable2, m_BitDisable2, mSize, fSize);
	}

	// Up Img
	if( NULL != fNameUp3 && strlen((char *)fNameUp3) )
	{
		LoadJPGFile(NULL, fNameUp3, m_BitUp3, mSize, fSize);
	}

	mSizexx = mSize;
	// Down Img
	if( NULL != fNameDown3 && strlen((char *)fNameDown3) )
	{
		LoadJPGFile(NULL, fNameDown3, m_BitDown3,mSize, fSize);
	}

	// Focus Img
	if( NULL != fNameFocus3 && strlen((char *)fNameFocus3) )
	{
		LoadJPGFile(NULL, fNameFocus3, m_BitFocus3, mSize, fSize);
	}

	// Disable Img
	if( NULL != fNameDisable3 && strlen((char *)fNameDisable3) )
	{
		LoadJPGFile(NULL, fNameDisable3, m_BitDisable3, mSize, fSize);
	}
	m_sizeX = mSizexx.cx;
	m_sizeY	= mSizexx.cy;

	MakeWindowRgn();

	return TRUE;
}
BOOL CBitBtn::LoadBitmap(LPCTSTR fNameUp, LPCTSTR fNameDown, LPCTSTR fNameFocus, LPCTSTR fNameDisable)
{
	HBITMAP hbm;

	// Up Img
	if( NULL != fNameUp && strlen((char *)fNameUp) )
	{

		hbm = (HBITMAP) LoadImage (NULL, fNameUp, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (hbm == NULL) return FALSE;


		// Get the CBitmap object
		if(	!CopyBitmapFrom (CBitmap::FromHandle(hbm), &m_BitUp) ) return FALSE;

		DeleteObject(hbm);
	}

	// Down Img
	if( NULL != fNameDown && strlen((char *)fNameDown) )
	{


		hbm = (HBITMAP) LoadImage (NULL, fNameDown, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (hbm == NULL) return FALSE;


		// Get the CBitmap object
		if(	!CopyBitmapFrom (CBitmap::FromHandle(hbm), &m_BitDown) ) return FALSE;

		DeleteObject(hbm);
	}

	// Focus Img
	if( NULL != fNameFocus && strlen((char *)fNameFocus) )
	{


		hbm = (HBITMAP) LoadImage (NULL, fNameFocus, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (hbm == NULL) return FALSE;


		// Get the CBitmap object
		if(	!CopyBitmapFrom (CBitmap::FromHandle(hbm), &m_BitFocus) ) return FALSE;

		DeleteObject(hbm);
	}

	// Disable Img
	if( NULL != fNameDisable && strlen((char *)fNameDisable) )
	{


		hbm = (HBITMAP) LoadImage (NULL, fNameDisable, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE|LR_CREATEDIBSECTION);

		if (hbm == NULL) return FALSE;


		// Get the CBitmap object
		if(	!CopyBitmapFrom (CBitmap::FromHandle(hbm), &m_BitDisable) ) return FALSE;

		DeleteObject(hbm);
	}

	MakeWindowRgn();

	return TRUE;

}

void CBitBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if( m_bIsRadioBtn == TRUE )
	{

		CBitmap* pOldBitmap;
		CDC		cdc;
		cdc.CreateCompatibleDC(&dc);
		switch( m_state )
		{
		default:
		case STATE_UP:
			if( m_BitUp == NULL ) return;
			pOldBitmap = cdc.SelectObject(m_BitUp);
			break;
		case STATE_DOWN:
			if( m_BitDown == NULL ) return;
			pOldBitmap = cdc.SelectObject(m_BitDown);
			break;
		case STATE_FOCUS:
			if( m_BitFocus == NULL ) return;
			pOldBitmap = cdc.SelectObject(m_BitFocus);
			break;
		case STATE_DISABLE:
			if( m_BitDisable == NULL ) return;
			pOldBitmap = cdc.SelectObject(m_BitDisable);
			break;
		}

		//dc.BitBlt(0, 0, m_sizeX, m_sizeY, &cdc, 0, 0, SRCCOPY);
		dc.TransparentBlt( 0, 0, m_sizeX, m_sizeY,&cdc,0,0,m_sizeX, m_sizeY, RGB(255,0,255));

		cdc.SelectObject(pOldBitmap);
		cdc.DeleteDC();
	}

}
void CBitBtn::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	if( bEnable )
		m_state = STATE_UP;
	else
		m_state = STATE_DISABLE;

	Invalidate();

	//if( m_hGDCBitBtn )
	//	::PostMessage(m_hGDCBitBtn, GDBTN_ABLE_BTN, bEnable, 0);
}


void CBitBtn::SetHWND(HWND	hParent)
{
	//if( NULL != hParent )
	//	m_hCBitBtn	=	hParent;
}

void CBitBtn::SetBtnID(int id)
{
	m_ID = id;
}

void CBitBtn::SetBtnRadio(bool isSet)
{
	m_bIsRadioBtn = isSet;
}

int CBitBtn::GetRadioState()
{
	return m_state;
}
void CBitBtn::SetRadioState(int state)
{
	if( m_bIsRadioBtn == TRUE )
	{
		m_state = state;
		Invalidate();
	}
}

void CBitBtn::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( m_bIsRadioBtn == TRUE ) 
	{
		CButton::OnLButtonDown(nFlags, point); 
		return;
	}

	m_state = STATE_DOWN;
	Invalidate();

	CButton::OnLButtonDown(nFlags, point);
	//	if( m_hCBitBtn )
	//		::PostMessage(m_hCBitBtn, BTN_MOUSE_LBUTTON_DOWN, m_ID, (LPARAM)&point);

}

void CBitBtn::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_bIsRadioBtn == TRUE ) 
	{    
		CButton::OnLButtonUp(nFlags, point); 
		return;
	}

	m_state = STATE_UP;
	Invalidate();

	CButton::OnLButtonUp(nFlags, point);	
	//	if( m_hCBitBtn )
	//		::PostMessage(m_hCBitBtn, BTN_MOUSE_LBUTTON_UP, m_ID, (LPARAM)&point);

}

void CBitBtn::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);

	if( m_bIsRadioBtn == TRUE ) return;

	if( m_state == STATE_DISABLE ) return;

	//m_state = STATE_FOCUS;
	m_state = STATE_UP;
	Invalidate();

	//	if( m_hCBitBtn )
	//		::PostMessage(m_hCBitBtn, BTN_SET_FOCUS, m_ID, (LPARAM)&point);
}

void CBitBtn::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);

	if( m_bIsRadioBtn == TRUE ) return;

	if( m_state == STATE_DISABLE ) return;

	m_state = STATE_UP;
	Invalidate();

	//	if( m_hCBitBtn )
	//		::PostMessage(m_hCBitBtn, BTN_KILL_FOCUS, 0, (LPARAM)pNewWnd);

}



void CBitBtn::OnMouseMove(UINT nFlags, CPoint point) 
{

	CButton::OnMouseMove(nFlags, point);

	if( m_bIsRadioBtn == TRUE ) return;
	if( m_state == STATE_DISABLE ) return;

	// 1. Mouse has moved and we are not tracking this button, or 
	// 2. mouse has moved and the cursor was not above this window
	// == Is equivalent to WM_MOUSEENTER (for which there is no message)
	if((!m_bMouseTracking || GetCapture()!=this) && m_state == STATE_UP )
	{

		OnMouseEnter();
	}
	else 
	{
		if(m_state == STATE_FOCUS)
		{
			CRect rc;
			GetClientRect(&rc);
			if(!rc.PtInRect(point))	// The mouse cursor is no longer above this button
				OnMouseLeave();
		}
	}

}

void CBitBtn::OnMouseEnter(void)
{
	if( m_bIsRadioBtn == TRUE ) return;
	if( m_state == STATE_DISABLE ) return;

	// We are now tracking the mouse, OVER this button
	m_bMouseTracking = TRUE;
	m_state = STATE_FOCUS;

	// Ensure that mouse input is sent to the button
	SetCapture();
	Invalidate();
	//UpdateWindow();
}

void CBitBtn::OnMouseLeave(void)
{
	if( m_bIsRadioBtn == TRUE ) return;
	if( m_state == STATE_DISABLE ) return;

	// We are not tracking the mouse, this button is OFF.
	m_state = STATE_UP;
	m_bMouseTracking = FALSE;

	// Release mouse capture from the button and restore normal mouse input
	Invalidate();
	UpdateWindow();
	ReleaseCapture();
}
/*
LRESULT CBitBtn::OnBMSetCheck(WPARAM wparam, LPARAM)
{
BOOL	m_Checked=wparam!=0;
CString xx;

if( m_bIsRadioBtn == TRUE ) 
{
if( m_Checked == TRUE )
{
m_state = STATE_DOWN;
}
else
{
m_state = STATE_UP;
}

Invalidate();
}
return 0L;
}
*/

BOOL CBitBtn::OnEraseBkgnd(CDC* pDC) 
{
	// Get a DC for the bitmap
	CDC dcImage;
	dcImage.CreateCompatibleDC (pDC);


	CBitmap	*pOldBitmap;
	BITMAP	bm;

	pOldBitmap = NULL;
	if( IsWindowEnabled() == FALSE )
	{
		m_state = STATE_DISABLE;
	}
	if(m_airstate==NORMAL){
		switch( m_state )
		{
		default:
		case STATE_UP:
			if( m_BitUp != NULL )		
			{
				pOldBitmap = dcImage.SelectObject(m_BitUp);
				m_BitUp->GetBitmap(&bm);
			}
			break;
		case STATE_DOWN:
			if( m_BitDown != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDown);
				m_BitDown->GetBitmap(&bm);
			}
			break;
		case STATE_FOCUS:
			if( m_BitFocus != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitFocus);
				m_BitFocus->GetBitmap(&bm);
			}
			break;
		case STATE_DISABLE:
			if( m_BitDisable != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDisable);
				m_BitDisable->GetBitmap(&bm);
			}
			break;
		}
	}else if(m_airstate==WARNING){
		switch( m_state )
		{
		default:
		case STATE_UP:
			if( m_BitUp2 != NULL )		
			{
				pOldBitmap = dcImage.SelectObject(m_BitUp2);
				m_BitUp2->GetBitmap(&bm);
			}
			break;
		case STATE_DOWN:
			if( m_BitDown2 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDown2);
				m_BitDown2->GetBitmap(&bm);
			}
			break;
		case STATE_FOCUS:
			if( m_BitFocus2 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitFocus2);
				m_BitFocus2->GetBitmap(&bm);
			}
			break;
		case STATE_DISABLE:
			if( m_BitDisable2 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDisable2);
				m_BitDisable2->GetBitmap(&bm);
			}
			break;
		}
	}else if(m_airstate==DANGER){
		switch( m_state )
		{
		default:
		case STATE_UP:
			if( m_BitUp3 != NULL )		
			{
				pOldBitmap = dcImage.SelectObject(m_BitUp3);
				m_BitUp3->GetBitmap(&bm);
			}
			break;
		case STATE_DOWN:
			if( m_BitDown3 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDown3);
				m_BitDown3->GetBitmap(&bm);
			}
			break;
		case STATE_FOCUS:
			if( m_BitFocus3 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitFocus3);
				m_BitFocus3->GetBitmap(&bm);
			}
			break;
		case STATE_DISABLE:
			if( m_BitDisable3 != NULL )
			{
				pOldBitmap = dcImage.SelectObject(m_BitDisable3);
				m_BitDisable3->GetBitmap(&bm);
			}
			break;
		}
	}

	if( pOldBitmap != NULL )
	{
		// Draw the bitmap as the window background
		//pDC->BitBlt (0, 0, m_sizeX, m_sizeY, &dcImage, 0, 0, SRCCOPY);
		//투명 처리 마젠타 
		pDC->TransparentBlt(0,0,m_sizeX,m_sizeY,&dcImage,0,0,m_sizeX,m_sizeY, RGB(255,0,255));
		// Release
		dcImage.SelectObject (pOldBitmap);
		dcImage.DeleteDC ();
	}

	// Return value: Nonzero if it erases the background.
	return TRUE;
}


void CBitBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if((int)lpDrawItemStruct->itemID < 0) return;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CDC cdc;
	CBitmap *pOldBitmap, *curBitmap;

	if(lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		m_state = STATE_DISABLE;
		curBitmap = m_BitDisable;
	}
	else if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		m_state = STATE_DOWN;
		curBitmap = m_BitDown;
	}
	else if(m_state==STATE_FOCUS)
	{
		curBitmap = m_BitFocus;
	}
	else
	{
		m_state = STATE_UP;
		curBitmap = m_BitUp;
	}

	cdc.CreateCompatibleDC(pDC);

	pOldBitmap = cdc.SelectObject(curBitmap);

	//pDC->BitBlt(0, 0, m_sizeX, m_sizeY, &cdc, 0, 0, SRCCOPY);
	pDC->TransparentBlt( 0, 0, m_sizeX, m_sizeY,&cdc,0,0,m_sizeX, m_sizeY, RGB(255,0,255));
	cdc.SelectObject(pOldBitmap);
	cdc.DeleteDC();
}

CRect CBitBtn::getSize(void)
{
	CRect rect;
	rect.right=m_sizeX;
	rect.bottom=m_sizeY;
	return rect;
}



void CBitBtn::Change_State(int state)
{
	m_airstate=state;
}


