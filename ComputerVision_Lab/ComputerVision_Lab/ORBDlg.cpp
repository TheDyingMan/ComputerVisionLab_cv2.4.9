// ORBDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComputerVision_Lab.h"
#include "ORBDlg.h"
#include "afxdialogex.h"


// ORBDlg 对话框

IMPLEMENT_DYNAMIC(ORBDlg, CDialogEx)

ORBDlg::ORBDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ORBDIALOG, pParent)
{

}

ORBDlg::~ORBDlg()
{
}

void ORBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ORBDlg, CDialogEx)
END_MESSAGE_MAP()


// ORBDlg 消息处理程序
