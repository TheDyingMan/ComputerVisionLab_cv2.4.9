// KeyPointsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComputerVision_Lab.h"
#include "KeyPointsDlg.h"
#include "afxdialogex.h"


// KeyPointsDlg 对话框

IMPLEMENT_DYNAMIC(KeyPointsDlg, CDialogEx)

KeyPointsDlg::KeyPointsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KETPOINTSDIALOG, pParent)
{

}

KeyPointsDlg::~KeyPointsDlg()
{
}

void KeyPointsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(KeyPointsDlg, CDialogEx)
END_MESSAGE_MAP()


// KeyPointsDlg 消息处理程序
