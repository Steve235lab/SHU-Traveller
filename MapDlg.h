#pragma once

#include "Landmark.h"
#include "Edge.h"
#include "ShortestPath.h"
#include "CtrlPadDlg.h"

// MapDlg 对话框

class MapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MapDlg)
	CImage SHUmap;

public:
	MapDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MapDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog();
	//CImage SHUmap;
	void iniLandmarks();	// 初始化landmarks对象数组
	void iniEdges();		// 初始化edges对象数组
	void runFloyd();		// 启动Floyd()函数计算每对顶点间的最短路径并写入web中

	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonOpenctrlpad();
	afx_msg void OnBnClickedButtonOpenaboutdlg();
};
