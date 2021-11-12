
// Picture_ControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Picture_Control.h"
#include "Picture_ControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPictureControlDlg 对话框



CPictureControlDlg::CPictureControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICTURE_CONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPictureControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPictureControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_IMGTEST, &CPictureControlDlg::OnStnClickedImgtest)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPictureControlDlg 消息处理程序
/**********************************************************************
*
*   OnInitDialog - 对Dlg进行初始化
*   input:  nopt
*   output: nopt
*   ps: 设置了图标，设置了Pictrue clt的默认大小（因为这张位图超级大）
*
*********************************************************************/
BOOL CPictureControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect rect;
	GetDlgItem(IDC_IMGTEST)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	GetDlgItem(IDC_IMGTEST)->MoveWindow(rect.left, rect.top, 50, 50, true);


	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPictureControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPictureControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPictureControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPictureControlDlg::OnStnClickedImgtest()
{
	// TODO: 在此添加控件通知处理程序代码

}



/*******************************
*	OnLButtonDown   ---  左键鼠标按下
*	input: UINT，CPoint  --  标记，鼠标点击位置坐标
*	output: nope
*	ps: 
********************************/
void CPictureControlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   rectPic;
	POINT   ptPut = point;

	//获取控件指针，并获取控件的Rect
	GetDlgItem(IDC_IMGTEST)->GetWindowRect(rectPic);
	//转换坐标!
	ClientToScreen(&ptPut);

	//如果你点击的点在Rect内
	if (rectPic.PtInRect(ptPut))
	{
		//初始化DC
		CBitmap     bitmapTemp;
		CBitmap*	pOldBitmap;
		CDC* pDC = GetDlgItem(IDC_IMGTEST)->GetDC();
		CDC* pMemDC = new CDC;

		//创建位图内存
		bitmapTemp.CreateCompatibleBitmap(pDC, rectPic.Width(), rectPic.Height());
		pMemDC->CreateCompatibleDC(pDC);

		pOldBitmap = pMemDC->SelectObject(&bitmapTemp);
		pMemDC->BitBlt(0, 0, rectPic.Width(), rectPic.Height(), pDC, 0, 0, SRCCOPY);
		pMemDC->SelectObject(pOldBitmap);

		delete  pMemDC;
		ReleaseDC(pDC);

		m_bIsLButtonDown = true;

		m_ptOffset.x = ptPut.x - rectPic.left;
		m_ptOffset.y = ptPut.y - rectPic.top;

		//CImageList
		m_imgDrag.DeleteImageList();
		m_imgDrag.Create(rectPic.Width(), rectPic.Height(), ILC_COLOR32 | ILC_MASK, 0, 1);
		//黑色透明
		m_imgDrag.Add(&bitmapTemp, RGB(0, 0, 0));
		m_imgDrag.BeginDrag(0, m_ptOffset);
		m_imgDrag.DragEnter(NULL, ptPut);
		//设置鼠标获取
		SetCapture();
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}

/*******************************
*	OnLButtonUp   ---  左键鼠标松开
*	input: UINT，CPoint  --  标记，鼠标点击位置坐标
*	output: nope
*	ps: 结束鼠标捕获，结束图片移动，
********************************/
void CPictureControlDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bIsLButtonDown)
	{
		CRect   rectPic;
		CWnd* pPic = GetDlgItem(IDC_IMGTEST);

		ScreenToClient(&m_ptMove);

		pPic->GetWindowRect(rectPic);

		pPic->MoveWindow(m_ptMove.x - m_ptOffset.x, m_ptMove.y - m_ptOffset.y, rectPic.Width(), rectPic.Height());

		m_bIsLButtonDown = false;

		CImageList::DragLeave(this);
		CImageList::EndDrag();
		//结束鼠标捕获
		ReleaseCapture();
		pPic->Invalidate();

	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


/*******************************
*	OnMouseMove   ---  鼠标移动
*	input: UINT，CPoint  --  标记，鼠标点击位置坐标
*	output: nope
*	ps: 计算鼠标的移动
********************************/
void CPictureControlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//计算鼠标位移
	if (m_bIsLButtonDown)
	{
		CRect       rtClient, rtPicture;
		CPoint tempPoint;
		GetClientRect(rtClient);

		m_ptMove = point;

		GetDlgItem(IDC_IMGTEST)->GetWindowRect(rtPicture);

		ClientToScreen(&rtClient);
		ClientToScreen(&m_ptMove);

		if (rtClient.left > m_ptMove.x - m_ptOffset.x)
			m_ptMove.x = rtClient.left + m_ptOffset.x;

		if (rtClient.top > m_ptMove.y - m_ptOffset.y)
			m_ptMove.y = rtClient.top + m_ptOffset.y;

		if ((rtClient.right - rtPicture.Width()) < (m_ptMove.x - m_ptOffset.x))
			m_ptMove.x = rtClient.right - rtPicture.Width() + m_ptOffset.x;

		if (rtClient.bottom - rtPicture.Height() < (m_ptMove.y - m_ptOffset.y))
			m_ptMove.y = rtClient.bottom - rtPicture.Height() + m_ptOffset.y;

		CImageList::DragMove(m_ptMove);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

/*****************************************************************************************
*	OnMouseMove   ---  鼠标右键
*	input: UINT，CPoint  --  标记，鼠标点击位置坐标
*	output: nope
*	ps: 点击鼠标右键。打开打开文件对话框选择图片，并在鼠标点击位置创建一个图片（未完工）
*   bug: 如果打开文件对话框出现的够快，那么在文件对话框中也点击右键（不排除是鼠标的问题）
********************************************************************************************/
void CPictureControlDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect   rectPic;
	_createpoint = point;

	//获取控件指针，并获取控件的Rect
	GetDlgItem(IDC_IMGTEST)->GetWindowRect(rectPic);
	//转换坐标!
	ClientToScreen(&_createpoint);

	//如果你点击的点在Rect内
	if (!rectPic.PtInRect(_createpoint))
	{
		 
		 CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
		 if (dlgFile.DoModal())
		 {
			     strFile = (LPCTSTR)dlgFile.GetPathName();
				 if (strFile)
				 {
					 CString temp;
					 temp.Format(L"在: %d,%d处创建 %s", _createpoint.x, _createpoint.y, strFile);
					 AfxMessageBox(temp);
				 }

		 }

	}


	CDialogEx::OnRButtonDown(nFlags, point);
}

/*********************************************************************
*	OnSize   ---  reSize 
*	input: 
*	output: 
*	ps: 
*   bug： 对话框没有自动排版，当大小发生改变时，图片大小会变成原来的尺寸
*********************************************************************/
void CPictureControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);



	// TODO: 在此处添加消息处理程序代码
	
}






