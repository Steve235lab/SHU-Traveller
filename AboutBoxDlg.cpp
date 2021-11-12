// AboutBoxDlg.cpp: 实现文件
//

#include "pch.h"
#include "SHU_Traveller_SD.h"
#include "AboutBoxDlg.h"
#include "afxdialogex.h"


// AboutBoxDlg 对话框

IMPLEMENT_DYNAMIC(AboutBoxDlg, CDialogEx)

AboutBoxDlg::AboutBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

AboutBoxDlg::~AboutBoxDlg()
{
}

void AboutBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutBoxDlg, CDialogEx)
END_MESSAGE_MAP()


// AboutBoxDlg 消息处理程序
