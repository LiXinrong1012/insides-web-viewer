
#include "stdafx.h"
#include "resource.h"
#include "HsfShellExt.h"
#include "BStream.h"
#include "BOpcodeHandler.h"

#include <magick/api.h>

CHsfShellExt::~CHsfShellExt()
{
	delete m_tk;
}

STDMETHODIMP CHsfShellExt::IsDirty()
{
	return S_OK;
}

STDMETHODIMP CHsfShellExt::Load( LPCOLESTR wszFile, DWORD grfMode)
{ 
	USES_CONVERSION;
	lstrcpyn ( m_szFilename, W2CT(wszFile), MAX_PATH );
	return S_OK;
}

class TK_My_Thumbnail : public TK_Thumbnail
{
private:
	bool m_valid;

public:
	TK_My_Thumbnail() : TK_Thumbnail(), m_valid(false) {};
	TK_Status Execute (BStreamFileToolkit & tk);
	void Reset ();

	bool isValid() const {return m_valid;};
};

TK_Status TK_My_Thumbnail::Execute (BStreamFileToolkit & tk) {
	m_valid = true;
	return TK_Error;
}

void TK_My_Thumbnail::Reset ()
{
	return;
}

bool CHsfShellExt::ExtractImageFromHSF(TCHAR const * filename)
{
	if(!m_tk){
		m_tk = new BStreamFileToolkit;
		m_thumbnail = new TK_My_Thumbnail;
		m_tk->SetOpcodeHandler(TKE_Thumbnail, m_thumbnail);
		TK_Read_Stream_File(filename, m_tk);
	}
	return m_thumbnail->isValid();
}


#define	GDI_RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define	GDI_RGBA(r,g,b,a) ((COLORREF) (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16) | ((a & 0xff) << 24) )


STDMETHODIMP CHsfShellExt::ExtractThumbnail(TCHAR const * filename, HBITMAP* phBmpImage) 
{
	HRESULT retval = S_FALSE;

	if(ExtractImageFromHSF(m_szFilename)){
		// Retrieve the handle to a display device context for the client 
		// area of the window. 
		HDC hDC = GetDC (NULL);

		// Create a memory device context compatible with the device. 
		HDC hDCMem = CreateCompatibleDC (hDC);

		int iWidth = m_thumbnail->GetSize()[0];
		int iHeight = m_thumbnail->GetSize()[1];

		// Use ImageMagick to scale down the image
		ExceptionInfo e;
		GetExceptionInfo(&e);
		char const * format = m_thumbnail->GetFormat() == TKO_Thumbnail_RGB? "RGB" : "RGBA";
		Image * original = ConstituteImage(iWidth, iHeight, format, CharPixel, m_thumbnail->GetBytes(), &e);
		Image * image = ResizeImage(original, m_requestedSize.cx, m_requestedSize.cy, LanczosFilter, 1, &e);
		DestroyImage(original);

		// Create a bitmap compatible with the device associated with the 
		// device context.
		HBITMAP hBitmap = CreateCompatibleBitmap (hDC, m_requestedSize.cx, m_requestedSize.cy);
		SelectObject(hDCMem, hBitmap);

		// Insert code to use the bitmap.
		for(int row = 0; row < m_requestedSize.cy; ++row){
			for(int col = 0; col < m_requestedSize.cx; ++col){
				PixelPacket const mgk = GetOnePixel(image, col, row);
				unsigned char const r = (unsigned char)mgk.red;
				unsigned char const g = (unsigned char)mgk.green;
				unsigned char const b = (unsigned char)mgk.blue;
				unsigned char const a = 0;
				SetPixel(hDCMem, col, row, GDI_RGBA(r, g, b, a));
			}
		}
		DestroyImage(image);

		// Delete the memory device context and the display device context.
		DeleteDC (hDCMem);
		DeleteDC (hDC);

		*phBmpImage = hBitmap;
		retval = S_OK;
	}

	return retval;
}

STDMETHODIMP CHsfShellExt::GetLocation(
						 LPWSTR pszPathBuffer,
						 DWORD cchMax,
						 DWORD *pdwPriority,
						 const SIZE *prgSize,
						 DWORD dwRecClrDepth,
						 DWORD *pdwFlags
						 )
{
	*pdwFlags = IEIFLAG_CACHE | IEIFLAG_NOSTAMP | IEIFLAG_REFRESH;
	m_requestedSize = *prgSize;
	return E_PENDING;
}


STDMETHODIMP CHsfShellExt::Extract( HBITMAP * phBmpImage )
{
	return ExtractThumbnail(m_szFilename, phBmpImage);
}
