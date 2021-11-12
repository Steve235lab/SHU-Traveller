#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

class CSlideShowCtrl :public CStatic
{
private:
	int m_iActiveIndex;
	vector<HBITMAP> m_vImages;
	HBITMAP m_CurrentBmp;

	HBITMAP ReadJpegFile(LPWSTR& pFile);
	HBITMAP ResizeBmp(HBITMAP hBmp, int cx, int cy);
	void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
protected:
	DECLARE_MESSAGE_MAP()
public:
	CSlideShowCtrl(void);
	virtual ~CSlideShowCtrl(void);

	void AddImage(LPWSTR imagePath);
	void AddImage(HBITMAP image);
	void ClearAllImages();
	void Start();
	void Stop();
};