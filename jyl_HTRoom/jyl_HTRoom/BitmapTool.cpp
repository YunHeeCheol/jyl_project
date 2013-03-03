// BitmapTool.cpp: implementation of the CBitmapTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "WonderView.h"
#include "BitmapTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitmapTool::CBitmapTool()
{

}

CBitmapTool::~CBitmapTool()
{

}


BOOL CBitmapTool :: CopyBitmapFrom (CBitmap *pBitmap, CBitmap **dpBitMap)
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

	// Automatically delete the object

	// Make the window transparent if needed
	return TRUE;
}


BOOL CBitmapTool :: LoadBitmapFromFile(LPCTSTR lpszFilename, CBitmap **dpBitmap)
{
	if( NULL != lpszFilename && strlen((char *)lpszFilename) )
	{
		HBITMAP hbm = (HBITMAP) LoadImage (NULL, lpszFilename, IMAGE_BITMAP, 0, 0,
									LR_LOADFROMFILE|LR_CREATEDIBSECTION);
		
		if (hbm == NULL) 
		{
			return FALSE;
		}


		// Get the CBitmap object
		if(	!CopyBitmapFrom (CBitmap::FromHandle(hbm), dpBitmap) )
		{
			DeleteObject(hbm);		
			return FALSE;
		}

		DeleteObject(hbm);

		return TRUE;
	}

	return FALSE;
}

BOOL CBitmapTool::LoadBitmapFromResource(UINT	nIDResource, CBitmap **dpBitmap)
{
	if( NULL != nIDResource )
	{
		*dpBitmap = new CBitmap;

		if( !(*dpBitmap)->LoadBitmap (nIDResource) )
		{
			delete	*dpBitmap;
			return	FALSE;
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CBitmapTool::Transpatent2(CDC &dc, CBitmap *curBitmap, int x, int y, int cx, int cy)
{
	CDC		 l_BufferDC ;
			 l_BufferDC.CreateCompatibleDC( &dc ) ;

	CBitmap  l_BufferBitmap ;
			 l_BufferBitmap.CreateCompatibleBitmap( &dc, cx, cy ) ;

	CBitmap* l_pOldBufferBitmap = l_BufferDC.SelectObject( &l_BufferBitmap ) ;

	CDC		 l_MaskDC ;
			 l_MaskDC.CreateCompatibleDC( &dc ) ;

	CBitmap  l_MaskBitmap ;
			 l_MaskBitmap.CreateBitmap( cx, cy, 1, 1, NULL ) ;

	CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ;

	#define ROP4_TRANSPARENTBLIT		0xCCAA0020
	#define SRCMASK						0x00220326

	////////////////////////////////////////////////////////////////////////////
	// Fill with transparent color
	////////////////////////////////////////////////////////////////////////////

	l_BufferDC.FillSolidRect(x, y, cx, cy, RGB( 0, 0, 2 ) ) ;
	//l_BufferDC.FillSolidRect( &l_rcClient, RGB( 255, 0, 255 ) ) ;
	//l_BufferDC.FillSolidRect( &l_rcClient, RGB( 153, 153, 153 ) ) ;
	////////////////////////////////////////////////////////////////////////////
	// Blit the bitmap to the buffer
	////////////////////////////////////////////////////////////////////////////

	CDC		 l_MemoryDC ;
			 l_MemoryDC.CreateCompatibleDC( &dc ) ;

	CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( *curBitmap ) ) ;

	l_BufferDC.BitBlt( 0, 0, cx, cy, &l_MemoryDC, 0, 0, SRCCOPY ) ;

	l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ;

	////////////////////////////////////////////////////////////////////////////
	// Create the mask.
	////////////////////////////////////////////////////////////////////////////

	COLORREF l_crOldBack = l_BufferDC.SetBkColor( RGB( 0, 0, 2 ) ) ;
		
	l_MaskDC.BitBlt( 0, 0, cx, cy, &l_BufferDC, 0, 0, SRCCOPY ) ;

	l_BufferDC.SetBkColor( l_crOldBack ) ;

	////////////////////////////////////////////////////////////////////////////
	// Draw the bitmap transparently now, since not all devices support this
	// and Windows 98 does not (duh?), if this fails, we do it the long way.
	////////////////////////////////////////////////////////////////////////////

	if( ! dc.MaskBlt( x, 
					  y, 
					  cx,
					  cy,
					  &l_BufferDC,
					  0,
					  0,
					  l_MaskBitmap,
			   		  0,
				   	  0,
				   	  ROP4_TRANSPARENTBLIT ) )
	{
		CDC		 l_CopyDC ;
				 l_CopyDC.CreateCompatibleDC( &dc ) ;

		CBitmap  l_CopyBitmap ;
				 l_CopyBitmap.CreateCompatibleBitmap( &dc, cx, cy ) ;

		CBitmap* l_pOldCopyBitmap = l_CopyDC.SelectObject( &l_CopyBitmap ) ;

		l_CopyDC.BitBlt  ( x, y, cx, cy, &dc,         0, 0, SRCCOPY  ) ;
		l_CopyDC.BitBlt  ( x, y, cx, cy, &l_MaskDC,   0, 0, SRCAND   ) ;
		l_BufferDC.BitBlt( x, y, cx, cy, &l_MaskDC,   0, 0, SRCMASK  ) ;
		l_CopyDC.BitBlt  ( x, y, cx, cy, &l_BufferDC, 0, 0, SRCPAINT ) ;
		dc.BitBlt        ( x, y, cx, cy, &l_CopyDC,   0, 0, SRCCOPY  ) ;

		l_CopyDC.SelectObject( l_pOldCopyBitmap ) ;
	}

	////////////////////////////////////////////////////////////////////////////
	// Clean up.
	////////////////////////////////////////////////////////////////////////////

	l_MaskDC.SelectObject( l_pOldMaskBitmap ) ;
	l_BufferDC.SelectObject( l_pOldBufferBitmap ) ;

	l_MaskDC.DeleteDC();
	l_BufferDC.DeleteDC();
	return TRUE;
}
BOOL CBitmapTool::Transpatent(CDC &dc, CBitmap *curBitmap, int x, int y, int cx, int cy)
{
	CDC		 l_BufferDC ;
			 l_BufferDC.CreateCompatibleDC( &dc ) ;

	CBitmap  l_BufferBitmap ;
			 l_BufferBitmap.CreateCompatibleBitmap( &dc, cx, cy ) ;

	CBitmap* l_pOldBufferBitmap = l_BufferDC.SelectObject( &l_BufferBitmap ) ;

	CDC		 l_MaskDC ;
			 l_MaskDC.CreateCompatibleDC( &dc ) ;

	CBitmap  l_MaskBitmap ;
			 l_MaskBitmap.CreateBitmap( cx, cy, 1, 1, NULL ) ;

	CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ;

	#define ROP4_TRANSPARENTBLIT		0xCCAA0020
	#define SRCMASK						0x00220326

	////////////////////////////////////////////////////////////////////////////
	// Fill with transparent color
	////////////////////////////////////////////////////////////////////////////

	l_BufferDC.FillSolidRect(x, y, cx, cy, RGB( 255, 0, 255 ) ) ;
	//l_BufferDC.FillSolidRect( &l_rcClient, RGB( 255, 0, 255 ) ) ;
	//l_BufferDC.FillSolidRect( &l_rcClient, RGB( 153, 153, 153 ) ) ;
	////////////////////////////////////////////////////////////////////////////
	// Blit the bitmap to the buffer
	////////////////////////////////////////////////////////////////////////////

	CDC		 l_MemoryDC ;
			 l_MemoryDC.CreateCompatibleDC( &dc ) ;

	CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( *curBitmap ) ) ;

	l_BufferDC.BitBlt( 0, 0, cx, cy, &l_MemoryDC, 0, 0, SRCCOPY ) ;

	l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ;

	////////////////////////////////////////////////////////////////////////////
	// Create the mask.
	////////////////////////////////////////////////////////////////////////////

	COLORREF l_crOldBack = l_BufferDC.SetBkColor( RGB( 255, 0, 255 ) ) ;
		
	l_MaskDC.BitBlt( 0, 0, cx, cy, &l_BufferDC, 0, 0, SRCCOPY ) ;

	l_BufferDC.SetBkColor( l_crOldBack ) ;

	////////////////////////////////////////////////////////////////////////////
	// Draw the bitmap transparently now, since not all devices support this
	// and Windows 98 does not (duh?), if this fails, we do it the long way.
	////////////////////////////////////////////////////////////////////////////

	if( ! dc.MaskBlt( x, 
					  y, 
					  cx,
					  cy,
					  &l_BufferDC,
					  0,
					  0,
					  l_MaskBitmap,
			   		  0,
				   	  0,
				   	  ROP4_TRANSPARENTBLIT ) )
	{
		CDC		 l_CopyDC ;
				 l_CopyDC.CreateCompatibleDC( &dc ) ;

		CBitmap  l_CopyBitmap ;
				 l_CopyBitmap.CreateCompatibleBitmap( &dc, cx, cy ) ;

		CBitmap* l_pOldCopyBitmap = l_CopyDC.SelectObject( &l_CopyBitmap ) ;

		l_CopyDC.BitBlt  ( x, y, cx, cy, &dc,         0, 0, SRCCOPY  ) ;
		l_CopyDC.BitBlt  ( x, y, cx, cy, &l_MaskDC,   0, 0, SRCAND   ) ;
		l_BufferDC.BitBlt( x, y, cx, cy, &l_MaskDC,   0, 0, SRCMASK  ) ;
		l_CopyDC.BitBlt  ( x, y, cx, cy, &l_BufferDC, 0, 0, SRCPAINT ) ;
		//dc.BitBlt        ( x, y, cx, cy, &l_CopyDC,   0, 0, SRCCOPY  ) ;
		dc.TransparentBlt( x, y, cx, cy,&l_CopyDC,0,0,cx, cy, RGB(255,0,255));
		l_CopyDC.SelectObject( l_pOldCopyBitmap ) ;
	}

	////////////////////////////////////////////////////////////////////////////
	// Clean up.
	////////////////////////////////////////////////////////////////////////////

	l_MaskDC.SelectObject( l_pOldMaskBitmap ) ;
	l_BufferDC.SelectObject( l_pOldBufferBitmap ) ;

	l_MaskDC.DeleteDC();
	l_BufferDC.DeleteDC();
	return TRUE;
}
void CBitmapTool::DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, BOOL Stretch, BOOL resize, int newcx, int newcy)
{
	if(!hbmp) return;

	CDC memdc;
	int w, h;

	if( resize == TRUE ) // Resize.. 
	{
		HBITMAP hbmp2;
		hbmp2 = (HBITMAP)CopyImage(hbmp, IMAGE_BITMAP, newcx, newcy, LR_CREATEDIBSECTION);
		memdc.CreateCompatibleDC(dc);
		memdc.SelectObject(hbmp2);
		w = newcx;
		h = newcy;
	}
	else
	{
		memdc.CreateCompatibleDC(dc);
		memdc.SelectObject(hbmp);
		w = r.right - r.left;
		h = r.bottom - r.top;
	}


	if(!Stretch)
	{
		dc->BitBlt(r.left, r.top, w, h, &memdc, 0, 0, SRCCOPY);
	}
	else
	{
		dc->StretchBlt(r.left, r.top, w, h, &memdc, 0, 0, w, h, SRCCOPY); 
	}
	DeleteDC(memdc);
}
void CBitmapTool::LoadJPGFile(LPCTSTR szFile, CBitmap* pBitmap)
{
  CSize  mSize;
  DWORD  fSize;
	LoadPictureFile(NULL, szFile, pBitmap, mSize, fSize);
}
void CBitmapTool::LoadJPGFile(HDC hdc, LPCTSTR szFile, CBitmap* pBitmap, CSize& mSize, DWORD& fSize)
{
	LoadPictureFile(hdc, szFile, pBitmap, mSize, fSize);
}


void CBitmapTool::LoadPictureFile(HDC hdc, LPCTSTR szFile, CBitmap* pBitmap, CSize& mSize, DWORD& fSize)
{
	// open file
	HANDLE hFile = CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if( INVALID_HANDLE_VALUE == hFile )
	{
    //AfxMessageBox(szFile);
    //_ASSERTE(INVALID_HANDLE_VALUE != hFile);
    return;
	}

	// get file size
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	_ASSERTE(-1 != dwFileSize);

	LPVOID pvData = NULL;
	// alloc memory based on file size
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	_ASSERTE(NULL != hGlobal);

	pvData = GlobalLock(hGlobal);
	_ASSERTE(NULL != pvData);

	DWORD dwBytesRead = 0;
	// read file and store in global memory
	BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
	_ASSERTE(FALSE != bRead);
	GlobalUnlock(hGlobal);
	CloseHandle(hFile);

	LPSTREAM pstm = NULL;
	// create IStream* from global memory
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
	_ASSERTE(SUCCEEDED(hr) && pstm);

	// Create IPicture from image file
	LPPICTURE gpPicture;

	hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&gpPicture);
	_ASSERTE(SUCCEEDED(hr) && gpPicture);	
	pstm->Release();

	OLE_HANDLE m_picHandle;
	/*
	long hmWidth, hmHeight;
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);
	int nWidth	= MulDiv(hmWidth, GetDeviceCaps(hdc, LOGPIXELSX), HIMETRIC_INCH);
	int nHeight	= MulDiv(hmHeight, GetDeviceCaps(hdc, LOGPIXELSY), HIMETRIC_INCH);
	*/
	gpPicture->get_Handle(&m_picHandle);
	pBitmap->DeleteObject();
	pBitmap->Attach((HGDIOBJ) m_picHandle);

	BITMAP bm;
	GetObject(pBitmap->m_hObject, sizeof(bm), &bm);
	mSize.cx = bm.bmWidth; //nWidth;
	mSize.cy = bm.bmHeight; //nHeight;
    fSize  = dwFileSize;
}

/*
BOOL CBitmapTool::SetBitmapPixels(CDC*     pDC,  HBITMAP  hBmp,   COLORREF rgbTransparent, int     nXOffset, int      nYOffset)
{
	//Sanity..
	if (hBmp    == NULL || pDC     == NULL)
		return FALSE;

	// Create a memory DC inside which we will scan the bitmap conten
	HDC hMemDC = CreateCompatibleDC(NULL);
	ASSERT(hMemDC);

	if (hMemDC)
	{
		// Get bitmap siz
		BITMAP bm;
		GetObject(hBmp, sizeof(bm), &bm);

		//Make sure x and Y offset are relativ
		//to center of the bitmap; thi
		//way the bitmap will appear centere
		//on (nXOffset,nYOffset
		nXOffset -= bm.bmWidth /2;
		nYOffset -= bm.bmHeight/2;

		// Create a 32 bits depth bitmap and select it into the memory DC
		BITMAPINFOHEADER RGB32BITSBITMAPINFO =
		{	
			sizeof(BITMAPINFOHEADER),// biSize
			bm.bmWidth,				 // biWidth;
           -bm.bmHeight,			 // biHeight
			1,						 // biPlanes;
			32,						 // biBitCount
			BI_RGB,					 // biCompression;
			0,						 // biSizeImage;
			0,						 // biXPelsPerMeter;
			0,						 // biYPelsPerMeter;
			0,						 // biClrUsed;
			0						 // biClrImportant;
		};

		VOID * pbits32; 

		HBITMAP hbm32 = CreateDIBSection(
		                hMemDC,
		                (BITMAPINFO *)&RGB32BITSBITMAPINFO,
							 DIB_RGB_COLORS,
							 &pbits32,
							 NULL,
							 0);

		if (hbm32)
		{
			HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

			// Create a DC just to copy the bitmap into the memory D
			HDC hDC = CreateCompatibleDC(hMemDC);

			if (hDC)
			{
				// Get how many bytes per row w
				//have for the bitmap bit
				//(rounded up to 32 bits
				BITMAP bm32;
				VERIFY(GetObject(hbm32, sizeof(bm32), &bm32));

				while (bm32.bmWidthBytes % 4)
					bm32.bmWidthBytes++;

				// Copy the bitmap into the memory D
				HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
				VERIFY(BitBlt(hMemDC,
					           0,
								  0,
								  bm.bmWidth,
								  bm.bmHeight,
								  hDC,
								  0,
								  0,
								  SRCCOPY));

				//Scan each bitmap row from bottom to to
				//(the bitmap is inverted vertically
				BYTE *p32 = (BYTE *)bm32.bmBits +
				            (bm32.bmHeight - 1) * bm32.bmWidthBytes;

				//Scan each bitmap pixel from left to right
				//Search for a continuous lin
				//of non transparent pixel
				for (int y = 0; y < bm.bmHeight; y++)
				{
					for (int x = 0; x < bm.bmWidth; x++)
					{
						int  x0 = x; //Ptr to start of region to fil
						LONG *p = (LONG *)p32 + x;

						COLORREF
						rgbBase =RGB(GetBValue((DWORD)(*p)),
								   	 GetGValue((DWORD)(*p)),
										 GetRValue((DWORD)(*p)));

						COLORREF rgbCurr = rgbBase;

						if (rgbBase != rgbTransparent)
						{
							while(rgbCurr == rgbBase &&
							      x        < bm.bmWidth)
							{
								p++;
								x++;
  								rgbCurr = RGB(GetBValue((DWORD)(*p)),
							  	   			  GetGValue((DWORD)(*p)),
												  GetRValue((DWORD)(*p)));
							}

							CRgn rgnTemp;

							rgnTemp.CreateRectRgn(
									  x0 + nXOffset,
									  y  + nYOffset,
									  x  + nXOffset,
									  y+1+ nYOffset);

							CBrush  brTemp(rgbBase);
							pDC->FillRgn(&rgnTemp,&brTemp);

							x--; //Decrement to account for x for loo
						}	//end if not transparent
					}	//end for 

					// Go to next ro
					//(remember, the bitmap is inverted vertically
					p32 -= bm32.bmWidthBytes;
				}	//end for 

				// Clean u
				SelectObject(hDC, holdBmp);
				DeleteDC(hDC);
			}

			DeleteObject(SelectObject(hMemDC, holdBmp));
		}

		DeleteDC(hMemDC);
	}	

	return TRUE;
}
*/