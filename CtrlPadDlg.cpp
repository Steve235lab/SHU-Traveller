// CtrlPadDlg.cpp: 实现文件
//

#include "pch.h"
#include "SHU_Traveller_SD.h"
#include "CtrlPadDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Landmark.h"
#include "ShortestPath.h"
#include "SHU_Traveller_SDView.h"
#include "MapDlg.h"

extern Landmark landmarks[256];
extern ShortestPath web[256][256];
extern int dataIniFlag;
extern int startPointIndex;
extern int endPointIndex;
extern int drawPathFlag;
int travelMode = 0;		// 出行方式：0 - 步行（默认），1 - 骑行
double walkSpeed = 90;	// m/min
double rideSpeed = 250;	// m/min
double scale = 0.5;		// m/pix 待定

// CtrlPadDlg 对话框

IMPLEMENT_DYNAMIC(CtrlPadDlg, CDialogEx)

CtrlPadDlg::CtrlPadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CtrlPad, pParent)
{
	dlgCtrlPad_flg = 0;

}

CtrlPadDlg::~CtrlPadDlg()
{
}

void CtrlPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_StartPoint, comboBoxStartPoint);
	DDX_Control(pDX, IDC_COMBO_EndPoint, comboBoxEndPoint);
	DDX_Control(pDX, IDC_COMBO_How, comboBoxHow);
}


BEGIN_MESSAGE_MAP(CtrlPadDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CtrlPadDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CtrlPadDlg::OnBnClickedHide)
	ON_CBN_SELCHANGE(IDC_COMBO_StartPoint, &CtrlPadDlg::OnCbnSelchangeComboStartpoint)
	ON_CBN_DROPDOWN(IDC_COMBO_StartPoint, &CtrlPadDlg::OnCbnDropdownComboStartpoint)
	ON_CBN_DROPDOWN(IDC_COMBO_EndPoint, &CtrlPadDlg::OnCbnDropdownComboEndpoint)
	ON_CBN_SELCHANGE(IDC_COMBO_EndPoint, &CtrlPadDlg::OnCbnSelchangeComboEndpoint)
	ON_CBN_SELCHANGE(IDC_COMBO_How, &CtrlPadDlg::OnCbnSelchangeComboHow)
END_MESSAGE_MAP()


// CtrlPadDlg 消息处理程序

// 防下拉框重复添加项标志位
int combosFlag = 0;	
int comboeFlag = 0;				

// “确定”按钮
void CtrlPadDlg::OnBnClickedOk()
{
	// 计算真实距离与时间
	double pixLength = web[startPointIndex][endPointIndex].pathLen;
	double realLength = pixLength * scale;
	double travelTime = 0;
	if (travelMode == 0) {
		travelTime = realLength / walkSpeed;
	}
	else if (travelMode == 1) {
		travelTime = realLength / rideSpeed;
	}

	// 显示总距离和时间
	CString length, time;
	length.Format(_T("%lf"), realLength);
	length.Append(_T(" m"));
	time.Format(_T("%lf"), travelTime);
	time.Append(_T(" min"));
	SetDlgItemText(IDC_STATIC_Length, length);
	SetDlgItemText(IDC_STATIC_Time, time);

	// 启动路径绘制
	drawPathFlag = 1;

	//CMainFrame* pAppFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//CSHUTravellerSDView* pView = (CSHUTravellerSDView*)pAppFrame->GetActiveView();
	//pAppFrame->Invalidate();
	//pAppFrame->UpdateWindow();

	MapDlg* pMapDlg = (MapDlg*)this->GetParent();
	//pMapDlg->GetClientRect();
	pMapDlg->Invalidate();
	pMapDlg->UpdateWindow();

	//CDialogEx::OnOK();
}


//  “隐藏”按钮
void CtrlPadDlg::OnBnClickedHide()
{
	dlgCtrlPad_flg = 0;
	combosFlag = 0;
	comboeFlag = 0;
	CDialogEx::OnCancel();
}


// 起点下拉框下拉响应函数
void CtrlPadDlg::OnCbnDropdownComboStartpoint()
{
	// 数据初始化检验: Pass
	//CString msg;
	//msg.Format(_T("%d"), dataIniFlag);
	//MessageBox(msg);
	
	// 初始化起点下拉框
	if (combosFlag == 0) {
		int i;
		string tName;
		CString newItem;
		for (i = 0; i < 128; i++) {
			tName = landmarks[i].getName();
			if (tName != "Road Point") {
				newItem = tName.c_str();
				this->comboBoxStartPoint.AddString(newItem);
			}
		}
		combosFlag = 1;
	}
}


// 起点下拉框选择响应函数
void CtrlPadDlg::OnCbnSelchangeComboStartpoint()
{
	startPointIndex = comboBoxStartPoint.GetCurSel();
}


// 终点下拉框下拉响应函数
void CtrlPadDlg::OnCbnDropdownComboEndpoint()
{
	// 初始化终点下拉框
	if (comboeFlag == 0) {
		int i;
		string tName;
		CString newItem;
		for (i = 0; i < 128; i++) {
			tName = landmarks[i].getName();
			if (tName != "Road Point") {
				newItem = tName.c_str();
				this->comboBoxEndPoint.AddString(newItem);
			}
		}
		comboeFlag = 1;
	}
}


// 终点下拉框选择响应函数
void CtrlPadDlg::OnCbnSelchangeComboEndpoint()
{
	endPointIndex = comboBoxEndPoint.GetCurSel();
}


// 出行方式下拉框选择响应函数
void CtrlPadDlg::OnCbnSelchangeComboHow()
{
	travelMode = comboBoxHow.GetCurSel();
}
