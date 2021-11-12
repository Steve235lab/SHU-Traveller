// MapDlg.cpp: 实现文件
//

#include "pch.h"
#include "SHU_Traveller_SD.h"
#include "MapDlg.h"
#include "afxdialogex.h"
#include "AboutBoxDlg.h"

#include <fstream>
#include <string>


extern Landmark landmarks[256];
extern Edge edges[256][256];
extern ShortestPath web[256][256];
extern int dataIniFlag;
int startPointIndex = -1;
int endPointIndex = -1;
int drawPathFlag = 0;	// 启动绘制路线标志位：0 - 不绘制，1 - 绘制；
						// 由CtrlPadDlg::OnBnClickedOk()函数控制置1，Ondraw()内部控制置0
int existFlag_ext[128][128];


CtrlPadDlg* dlg_ctrlPad = new CtrlPadDlg();

// MapDlg 对话框

IMPLEMENT_DYNAMIC(MapDlg, CDialogEx)

MapDlg::MapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAP, pParent)
{

}

MapDlg::~MapDlg()
{
}

void MapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MapDlg, CDialogEx)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_OpenCtrlPad, &MapDlg::OnBnClickedButtonOpenctrlpad)
	ON_BN_CLICKED(IDC_BUTTON_OpenAboutDlg, &MapDlg::OnBnClickedButtonOpenaboutdlg)
END_MESSAGE_MAP()


// MapDlg 消息处理程序

BOOL MapDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ShowWindow(SW_MAXIMIZE);//对话框默认最大化弹出
	
	this->iniLandmarks();
	this->iniEdges();
	this->runFloyd();
	dataIniFlag = 1;

	SCROLLINFO vinfo, hinfo;
	vinfo.cbSize = sizeof(vinfo);
	vinfo.fMask = SIF_ALL;
	vinfo.nPage = 50;//滚动块自身的长短，通常有如下关系：其长度/滚动条长度（含两个箭头）=nPage/(nMax+2)，
					//另外nPage取值-1时，滚动条会不见了。
	vinfo.nMax = 300;//滚动条所能滚动的最大值
	vinfo.nMin = 0;//滚动条所能滚动的最小值
	vinfo.nTrackPos = 0;
	SetScrollInfo(SB_VERT, &vinfo);//即使上述步骤一不做，使用此条语句也可以显示滚动条

	hinfo.cbSize = sizeof(hinfo);
	hinfo.fMask = SIF_ALL;
	hinfo.nPage = 50;//滚动块自身的长短，通常有如下关系：其长度/滚动条长度（含两个箭头）=nPage/(nMax+2)，
					//另外nPage取值-1时，滚动条会不见了。
	hinfo.nMax = 300;//滚动条所能滚动的最大值
	hinfo.nMin = 0;//滚动条所能滚动的最小值
	hinfo.nTrackPos = 0;
	SetScrollInfo(SB_HORZ, &hinfo);//即使上述步骤一不做，使用此条语句也可以显示滚动条

	SHUmap.Load(_T("SHU_map_dark.bmp"));

    return TRUE;
}

void MapDlg::iniLandmarks()
{
	using namespace std;
	ifstream dataFile;
	dataFile.open("./LMdata.txt");
	char buffer[128];
	string tName;
	int tx = 0, ty = 0;
	int ct = 0;
	int flag = 0;

	while (ct < 129) {							// 129个地点
		dataFile.getline(buffer, 128, '\n');	// 读取一行
		string buffer_s;
		buffer_s.append(buffer);				// 转为string类型
		int i, j;
		string tempstr;
		j = 0;
		for (i = 0; i < buffer_s.length(); i++) {
			if (buffer_s[i] == ',') {			// 以 "," 为界线切分字符串
				if (i == 0) {					// 道路点：无名称信息，统一命名
					tempstr = "Road Point";
				}
				else {							// 地标点
					tempstr = buffer_s.substr(j, i);
				}
				j = i + 1;
				if (flag == 0) {
					tName = tempstr;
					flag++;
				}
				else if (flag == 1) {
					tx = atoi(tempstr.c_str());
					flag++;
				}
				else if (flag == 2) {
					ty = atoi(tempstr.c_str());
					flag = 0;
				}
			}
		}
		landmarks[ct] = Landmark(tName, tx, ty, ct);
		ct++;
	}

	// 测试通过
	/*
	CString str;
	str = landmarks[127].getName().c_str();
	MessageBox(str);
	str.Format(_T("%d"), landmarks[127].x);
	MessageBox(str);
	str.Format(_T("%d"), landmarks[127].y);
	MessageBox(str);
	str.Format(_T("%d"), landmarks[127].getIndex());
	MessageBox(str);
	*/
}

void MapDlg::iniEdges()
{
	using namespace std;
	ifstream dataFile;
	dataFile.open("./PathDataN.txt");
	char buffer[512];
	int ct = 0;
	int existFlags[128][128] = { -1 };
	// 读取数据文件
	while (ct < 128) {
		string tLine;
		dataFile.getline(buffer, 512, '\n');	// 读取一行
		tLine.append(buffer);					// 转为string类型
		int i;
		int j = 0;
		string s;
		for (i = 0; i < 128; i++) {
			s = tLine[i];
			if (s == "0") {
				existFlags[ct][j] = 0;
				j++;
			}
			else if (s == "1") {
				existFlags[ct][j] = 1;
				j++;
			}
		}
		ct++;
	}

	int i, j;

	for (i = 0; i < 128; i++) {
		for (j = 0; j < 128; j++) {
			existFlag_ext[i][j] = existFlags[i][j];
		}
	}

	for (i = 0; i < 256; i++) {
		if (landmarks[i].getIndex() == -1) {
			break;
		}
		for (j = 0; j < 256; j++) {
			if (landmarks[j].getIndex() == -1) {
				break;
			}
			edges[i][j] = Edge(landmarks[i], landmarks[j], existFlags[i][j]);
		}
	}

	// 测试代码
	//CString str;
	//for (i = 0; i < 256; i++) {
	//	for (j = 0; j < 256; j++) {
	//		if (edges[i][j].getPD() != 1000000.0 && edges[i][j].getPD() != -1) {
	//			str.Format(_T("%lf"), edges[i][j].getPD());
	//			str.Append(_T("%d"), i);
	//			str.Append(_T("%d"), j);
	//			MessageBox(str);
	//		}
	//	}
	//}
	
	//CString str;
	//str.Format(_T("%lf"), edges[0][1].getPD());
	//MessageBox(str);
	
}

void MapDlg::runFloyd()
{
	ShortestPath::Floyd(landmarks, edges, web);
}




void MapDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollinfo;

	GetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);



	switch (nSBCode)

	{
	case SB_BOTTOM: //滑块滚动到最底部

		ScrollWindow(0, (scrollinfo.nPos - scrollinfo.nMax) * 10); //滚动屏幕

		scrollinfo.nPos = scrollinfo.nMax; //设定滑块新位置

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL); //更新滑块位置

		break;

	case SB_TOP: //滑块滚动到最顶部

		ScrollWindow(0, (scrollinfo.nPos - scrollinfo.nMin) * 10);

		scrollinfo.nPos = scrollinfo.nMin;

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		break;

	case SB_LINEUP: //单击上箭头

		scrollinfo.nPos -= 1;

		if (scrollinfo.nPos < scrollinfo.nMin)

		{
			scrollinfo.nPos = scrollinfo.nMin;

			break;

		}

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		ScrollWindow(0, 10);

		break;

	case SB_LINEDOWN: //单击下箭头

		scrollinfo.nPos += 1;

		if (scrollinfo.nPos > scrollinfo.nMax)

		{
			scrollinfo.nPos = scrollinfo.nMax;

			break;

		}

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		ScrollWindow(0, -10);

		break;

	case SB_PAGEUP: //单击滑块上方空白区域

		scrollinfo.nPos -= 5;

		if (scrollinfo.nPos < scrollinfo.nMin)

		{
			scrollinfo.nPos = scrollinfo.nMin;

			break;

		}

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		ScrollWindow(0, 10 * 5);

		break;

	case SB_PAGEDOWN: //单击滑块下方空白区域

		scrollinfo.nPos += 5;

		if (scrollinfo.nPos > scrollinfo.nMax)

		{
			scrollinfo.nPos = scrollinfo.nMax;

			break;

		}

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		ScrollWindow(0, -10 * 5);

		break;

	case SB_ENDSCROLL: //鼠标离开滑块，结束滑块拖动

	// MessageBox("SB_ENDSCROLL");

		break;

	case SB_THUMBPOSITION:

		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10);

		// scrollinfo.nPos = nPos;

		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);

		break;

	case SB_THUMBTRACK: //拖动滑块

		ScrollWindow(0, (scrollinfo.nPos - nPos) * 10);

		scrollinfo.nPos = nPos;

		SetScrollInfo(SB_VERT, &scrollinfo, SIF_ALL);

		break;
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void MapDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
	switch (nSBCode)
	{
	case SB_LEFT:
		ScrollWindow((scrollinfo.nPos - scrollinfo.nMin) * 10, 0);
		scrollinfo.nPos = scrollinfo.nMin;
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		break;
	case SB_RIGHT:
		ScrollWindow((scrollinfo.nPos - scrollinfo.nMax) * 10, 0);
		scrollinfo.nPos = scrollinfo.nMax;
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		break;
	case SB_LINELEFT:
		scrollinfo.nPos -= 1;
		if (scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		ScrollWindow(10, 0);
		break;
	case SB_LINERIGHT:
		scrollinfo.nPos += 1;
		if (scrollinfo.nPos > scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		ScrollWindow(-10, 0);
		break;
	case SB_PAGELEFT:
		scrollinfo.nPos -= 5;
		if (scrollinfo.nPos < scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		ScrollWindow(10 * 5, 0);
		break;
	case SB_PAGERIGHT:
		scrollinfo.nPos += 5;
		if (scrollinfo.nPos > scrollinfo.nMax)
		{
			scrollinfo.nPos = scrollinfo.nMax;
			break;
		}
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		ScrollWindow(-10 * 5, 0);
		break;
	case SB_THUMBPOSITION:
		break;
	case SB_THUMBTRACK:
		ScrollWindow((scrollinfo.nPos - nPos) * 10, 0);
		scrollinfo.nPos = nPos;
		SetScrollInfo(SB_HORZ, &scrollinfo, SIF_ALL);
		break;
	case SB_ENDSCROLL:
		break;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void MapDlg::OnPaint()
{
	/*
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	// 绘制路线
	CPen pen(PS_SOLID, 25, RGB(255, 0, 0));

	CRect rect;

	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);

	//IDC_STATIC_PREVIEW为要绘图的静态框的ID

	ScreenToClient(&rect); //将它们转化为相对于应用程序对话框的矩形

	// 绘制路线
	// TODO: 检查Floyd 以及edges
	if (drawPathFlag == 1) {
		if (startPointIndex != -1 && endPointIndex != -1) {
			CPen pen(PS_SOLID, 25, RGB(255, 0, 0));		// 设置画笔
			dc.SelectObject(&pen);
			int i, x, y;
			for (i = 0; i < sizeof(web[startPointIndex][endPointIndex].LMonPath) - 1; i++) {
				if (web[startPointIndex][endPointIndex].LMonPath[i + 1] != 0) {
					x = landmarks[web[startPointIndex][endPointIndex].LMonPath[i]].x;
					y = landmarks[web[startPointIndex][endPointIndex].LMonPath[i]].y;
					dc.MoveTo(x, y);
					x = landmarks[web[startPointIndex][endPointIndex].LMonPath[i + 1]].x;
					y = landmarks[web[startPointIndex][endPointIndex].LMonPath[i + 1]].y;
					dc.LineTo(x, y);
				}
				else {
					break;
				}
			}
			//for (i = 0; i < sizeof(web[startPointIndex][endPointIndex].LMonPath) - 1; i++) {
			//	CString str;
			//	int temp = web[startPointIndex][endPointIndex].LMonPath[i];
			//	if (temp == 0) {
			//		break;
			//	}
			//	else {
			//		int x = landmarks[web[startPointIndex][endPointIndex].LMonPath[i]].X();
			//		str.Format(_T("%d"), x);
			//		MessageBox(str);
			//	}
			//}
		}
		else {
			MessageBox(TEXT("请选择起点与终点！"));
		}

		drawPathFlag = 0;
	}
	*/
	
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();
	//SHUmap.Draw(pDC->GetSafeHdc(), 0, 0);

	
	// 创建并选择红色粗画笔
	CPen pen(PS_SOLID, 15, RGB(255, 0, 0));		
	pDC->SelectObject(pen);

	CPaintDC dc(this); // device context for painting
				   // TODO: 在此处添加消息处理程序代码
				   // 不为绘图消息调用 CDialogEx::OnPaint()

	dc.SelectObject(pen);

	//SHUmap.Draw(dc.GetSafeHdc(), 0, 0);

	if (drawPathFlag == 1) {
		pDC->Ellipse(landmarks[startPointIndex].x - 10, landmarks[startPointIndex].y - 10, landmarks[startPointIndex].x + 10, landmarks[startPointIndex].y + 10);
		pDC->Ellipse(landmarks[endPointIndex].x - 10, landmarks[endPointIndex].y - 10, landmarks[endPointIndex].x + 10, landmarks[endPointIndex].y + 10);
		if (startPointIndex != -1 && endPointIndex != -1) {
			int i, x, y;
			for (i = 0; i < sizeof(web[startPointIndex][endPointIndex].LMonPath) - 1; i++) {
				if (web[startPointIndex][endPointIndex].LMonPath[i + 1] != -1) {
					x = landmarks[web[startPointIndex][endPointIndex].LMonPath[i]].x;
					y = landmarks[web[startPointIndex][endPointIndex].LMonPath[i]].y;
					pDC->MoveTo(x, y);
					x = landmarks[web[startPointIndex][endPointIndex].LMonPath[i + 1]].x;
					y = landmarks[web[startPointIndex][endPointIndex].LMonPath[i + 1]].y;
					pDC->LineTo(x, y);
				}
				else {
					break;
				}
			}
			/*
			for (i = 0; i < sizeof(web[startPointIndex][endPointIndex].LMonPath) - 1; i++) {
				CString str;
				int temp = web[startPointIndex][endPointIndex].LMonPath[i];
				if (temp == 0) {
					break;
				}
				else {
					int x = web[startPointIndex][endPointIndex].LMonPath[i];
					str.Format(_T("%d"), x);

					MessageBox(str);
				}
			}
			*/
		}
		else {
			MessageBox(TEXT("请选择起点与终点！"));
		}

		//drawPathFlag = 0;
	}

	
	// 测试代码
	/*
	pDC->MoveTo(0, 0);
	pDC->LineTo(1920, 1080);
	*/
	
	// 取消以下注释来显示完整无向图
	/*
	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	pDC->SelectObject(pen2);
	int i, j;
	for (i = 0; i < 128; i++) {
		for (j = 0; j < 128; j++) {
			if (existFlag_ext[i][j] == 1) {
				pDC->MoveTo(landmarks[i].x, landmarks[i].y);
				pDC->LineTo(landmarks[j].x, landmarks[j].y);
			}
		}
	}
	*/
}


void MapDlg::OnBnClickedButtonOpenctrlpad()
{
	// TODO: 在此添加控件通知处理程序代码
	if (dlg_ctrlPad->dlgCtrlPad_flg == 0) {
		dlg_ctrlPad = new CtrlPadDlg();
		dlg_ctrlPad->Create(IDD_DIALOG_CtrlPad, this);
		dlg_ctrlPad->ShowWindow(SW_SHOW);
		dlg_ctrlPad->dlgCtrlPad_flg = 1;
	}
}


void MapDlg::OnBnClickedButtonOpenaboutdlg()
{
	AboutBoxDlg dlg_aboutBox;
	dlg_aboutBox.DoModal();
}
