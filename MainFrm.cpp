
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "SHU_Traveller_SD.h"

#include "MainFrm.h"
#include "CtrlPadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_CTWindow, &CMainFrame::OnCtwindow)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
	//dlg_ctrlPad = new CtrlPadDlg();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 设置标题栏图标
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_Logo);
	SetIcon(m_hIcon, TRUE); // Set big icon
	//SetIcon(m_hIcon, FALSE); // Set small icon

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


// 菜单栏按钮 打开控制悬浮窗
void CMainFrame::OnCtwindow()
{
	if (dlg_ctrlPad->dlgCtrlPad_flg == 0) {
		dlg_ctrlPad = new CtrlPadDlg();
		dlg_ctrlPad->Create(IDD_DIALOG_CtrlPad, this);
		dlg_ctrlPad->ShowWindow(SW_SHOW);
		dlg_ctrlPad->dlgCtrlPad_flg = 1;
	}
}
