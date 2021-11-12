#include "SlideShowCtrl.h"

#define _SLIDE_TIMER_ID 444555777

CSlideShowCtrl::CSlideShowCtrl(void)
{
	m_vImages.clear();
	m_iActiveIndex = 0;
	m_CurrentBmp = NULL;
}

CSlideShowCtrl::~CSlideShowCtrl(void)
{
}

BEGIN_MESSAGE_MAP(CSlideShowCtrl, CStatic)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

HBITMAP CSlideShowCtrl::ReadJpegFile(LPWSTR& pFile)
{ 
	HANDLE hFile; 
	HBITMAP hBmp; 
	DWORD dwSize; 
	DWORD dwRead; 
	HGLOBAL hMemJpeg; 
	LPSTREAM lpStream; 
	OLE_HANDLE hJpegBmp; 
	HRESULT hr; 
	LPPICTURE lpPicture = NULL; 
	void *pMemJpeg; 

	/* Open the file and get the size. */ 
	if((hFile = CreateFile(pFile, GENERIC_READ, FILE_SHARE_READ, 
			NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE) 
		return NULL; 
	if((dwSize = GetFileSize(hFile, NULL)) == 0xFFFFFFFF) 
	{ 
		CloseHandle(hFile); 
		return NULL; 
	} 

	/* Allocate space for file, read it in, and then close the file again. */ 
	if((hMemJpeg = GlobalAlloc(GMEM_MOVEABLE, dwSize)) == NULL) 
	{ 
		CloseHandle(hFile); 
		return NULL; 
	} 
	if((pMemJpeg = GlobalLock(hMemJpeg)) == NULL) 
	{ 
		CloseHandle(hFile); 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	if(!ReadFile(hFile, pMemJpeg, dwSize, &dwRead, NULL)) 
	{ 
		CloseHandle(hFile); 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	CloseHandle(hFile); 
	GlobalUnlock(hMemJpeg); 

	/* Create the stream and load the picture. */ 
	if((hr = CreateStreamOnHGlobal(hMemJpeg, TRUE, &lpStream)) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	if(OleLoadPicture(lpStream, dwSize, FALSE, IID_IPicture, (LPVOID*)(&lpPicture)) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->Release(); 
		return NULL; 
	} 

	/* Get the handle to the image, and then copy it. */ 
	if((lpPicture->get_Handle(&hJpegBmp)) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->Release(); 
		lpPicture->Release(); 
		return NULL; 
	} 
	if((hBmp = (HBITMAP)CopyImage((HANDLE *) hJpegBmp, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG)) == NULL) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->Release(); 
		lpPicture->Release(); 
		return NULL; 
	} 

	/* Free the original image and memory. */ 
	GlobalFree(hMemJpeg); 
	lpStream->Release(); 
	lpPicture->Release(); 
	return hBmp; 
}

void CSlideShowCtrl::AddImage(LPWSTR imagePath)
{
	HBITMAP image = ReadJpegFile(imagePath);
	AddImage(image);
}

void CSlideShowCtrl::AddImage(HBITMAP image)
{
	if(image != NULL)
	{
		//Stretch image if needed to fit
		CRect Rect;
		GetClientRect(&Rect);
		int frameW = Rect.Width();
		int frameH = Rect.Height();
		BITMAP bm;
		GetObject(image, sizeof(bm),&bm);
		int bmpW = bm.bmWidth;
		int bmpH = bm.bmHeight;

		double Ratio = 1.0;
		if(bmpW > frameW)
			Ratio = (double)frameW / (double)bmpW;
		if(bmpH > frameH)
		{
			double Temp = frameH / (double)bmpH;
			if (Temp < Ratio)
				Ratio = Temp;
		}
		int width = (int)(bmpW*Ratio);
		int height = (int)(bmpH*Ratio);

		//Save it to vector
		if(Ratio != 1.0)
			m_vImages.push_back(ResizeBmp(image, width, height));
		else
			m_vImages.push_back(image);
	}
}

void CSlideShowCtrl::ClearAllImages()
{
	m_vImages.clear();
	Stop();
}

void CSlideShowCtrl::Start()
{
	if(m_vImages.empty())
		return;

	m_CurrentBmp = m_vImages[0];
	Invalidate();
	UpdateWindow();
	if(m_vImages.size() > 1)
	{
		SetTimer(_SLIDE_TIMER_ID, 2000, NULL);
		m_iActiveIndex++;
	}
}

void CSlideShowCtrl::Stop()
{
	KillTimer(_SLIDE_TIMER_ID);
	m_CurrentBmp = NULL;
	Invalidate();
	UpdateWindow();
	m_iActiveIndex = 0;
}

void CSlideShowCtrl::OnTimer(UINT nIDEvent)
{
	if(m_iActiveIndex >= (int)m_vImages.size())
		m_iActiveIndex = 0;

	m_CurrentBmp = m_vImages[m_iActiveIndex++];
	Invalidate();
	UpdateWindow();

	CStatic::OnTimer(nIDEvent);
}

void CSlideShowCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect Rect;
	GetClientRect(&Rect);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap Bmp;
	Bmp.CreateCompatibleBitmap(&dc,Rect.Width(),Rect.Height());
	int SavedDC = MemDC.SaveDC();
	MemDC.SelectObject(&Bmp);

	MemDC.FillSolidRect(Rect,RGB(127,127,127));
	dc.BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);

	if(m_CurrentBmp != NULL)
	{
		//Stratch to fit if needed
		BITMAP bm;
		GetObject(m_CurrentBmp, sizeof(bm),&bm);
		int oriW = bm.bmWidth;
		int oriH = bm.bmHeight;

		double Ratio = 1.0;
		if(oriW > Rect.Width())
			Ratio =  (double)Rect.Width() / (double)oriW;
		if (oriH > Rect.Height())
		{
			double Temp = Rect.Height() / (double)oriH;
			if (Temp < Ratio)
				Ratio = Temp;
		}
		int X = (int)(Rect.Width() - (oriW*Ratio)) / 2;
		int Y = (int)(Rect.Height() - (oriH*Ratio)) / 2;

		
		CBitmap* pBitmap = CBitmap::FromHandle(m_CurrentBmp);
		MemDC.SelectObject(pBitmap);
		dc.BitBlt(X, Y, (int)(oriW*Ratio), (int)(oriH*Ratio), &MemDC, 0, 0, SRCCOPY);
	}

	MemDC.RestoreDC(SavedDC);
}

HBITMAP CSlideShowCtrl::ResizeBmp(HBITMAP hBmp,int cx,int cy)
{
	HDC dc = *(GetDC());
	HDC copyDC = CreateCompatibleDC(dc);
	HDC srcDC = CreateCompatibleDC(dc);
	int oriCx,oriCy;

	//Get Original Size
	BITMAP bm;
	GetObject(hBmp, sizeof(bm),&bm);
	oriCx = bm.bmWidth;
	oriCy = bm.bmHeight;

	RECT bmpRect;
	bmpRect.top=0;
	bmpRect.left=0;
	bmpRect.right=cx;
	bmpRect.bottom=cy;

	RECT oriRect = bmpRect;
	oriRect.right=oriCx;
	oriRect.bottom=oriCy;

	HRGN rgn1 = CreateRectRgnIndirect( &bmpRect );
	HRGN rgn2 = CreateRectRgnIndirect( &oriRect );
	SelectClipRgn(copyDC,rgn1);
	SelectClipRgn(srcDC,rgn2);
	DeleteObject(rgn1);
	DeleteObject(rgn2);

	HBITMAP copyBMP = CreateCompatibleBitmap(dc,cx,cy);
	HBITMAP copyBMPold = (HBITMAP)SelectObject(copyDC,copyBMP);
	HBITMAP srcBMPold = (HBITMAP)SelectObject(srcDC,hBmp);

	if(oriCx!=cx || oriCy!=cy)
		StretchBlt(copyDC,0,0,cx,cy,srcDC,0,0,oriCx,oriCy,SRCCOPY);
	else
		BitBlt(copyDC,0,0,cx,cy,srcDC,0,0,SRCCOPY);

	copyBMP = (HBITMAP)SelectObject(copyDC, copyBMPold);

	DeleteDC(copyDC);
	DeleteDC(srcDC);

	return copyBMP;
}