#pragma once


// CtrlPadDlg 对话框

class CtrlPadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CtrlPadDlg)

public:
	CtrlPadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CtrlPadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CtrlPad };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedHide();
	int dlgCtrlPad_flg;	// 控制浮窗存在标志
	afx_msg void OnCbnSelchangeComboStartpoint();
	CComboBox comboBoxStartPoint;
	afx_msg void OnCbnDropdownComboStartpoint();
	CComboBox comboBoxEndPoint;
	afx_msg void OnCbnDropdownComboEndpoint();
	afx_msg void OnCbnSelchangeComboEndpoint();
	CComboBox comboBoxHow;
	afx_msg void OnCbnSelchangeComboHow();
};
