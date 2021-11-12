#pragma once


// AboutBoxDlg 对话框

class AboutBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AboutBoxDlg)

public:
	AboutBoxDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AboutBoxDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
