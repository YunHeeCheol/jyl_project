// BitmapTool.h: interface for the CBitmapTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDBITMAPTOOL_H__DE9053D6_CC88_4BF7_8DD2_B41D2B2E19A1__INCLUDED_)
#define AFX_GDBITMAPTOOL_H__DE9053D6_CC88_4BF7_8DD2_B41D2B2E19A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBitmapTool  
{
public:
	CBitmapTool();
	virtual ~CBitmapTool();

private:


public:
	BOOL		CopyBitmapFrom (CBitmap *pBitmap, CBitmap **dpBitmap);
	BOOL		LoadBitmapFromFile(LPCTSTR lpszFilename, CBitmap **dpBitmap);
	BOOL		LoadBitmapFromResource(UINT	nIDResource, CBitmap **dpBitmap);
	BOOL		Transpatent(CDC &dc, CBitmap *curBitmap, int x, int y, int cx, int cy);
	BOOL		Transpatent2(CDC &dc, CBitmap *curBitmap, int x, int y, int cx, int cy);
	void    DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, BOOL Stretch, BOOL resize=FALSE, int newcx=0, int newcy=0);
	void    LoadPictureFile(HDC hdc, LPCTSTR szFile, CBitmap* pBitmap, CSize& mSize, DWORD& fSize);
	void    LoadJPGFile(LPCTSTR szFile, CBitmap* pBitmap);
	void		LoadJPGFile(HDC hdc, LPCTSTR szFile, CBitmap* pBitmap, CSize& mSize, DWORD& fSize);
	//	BOOL		SetBitmapPixels(CDC*     pDC,  HBITMAP  hBmp,   COLORREF rgbTransparent, int     nXOffset, int      nYOffset);

};

#endif // !defined(AFX_GDBITMAPTOOL_H__DE9053D6_CC88_4BF7_8DD2_B41D2B2E19A1__INCLUDED_)
