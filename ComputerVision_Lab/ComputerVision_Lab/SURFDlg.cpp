// SURFDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComputerVision_Lab.h"
#include "SURFDlg.h"
#include "afxdialogex.h"


// SURFDlg 对话框

IMPLEMENT_DYNAMIC(SURFDlg, CDialogEx)

SURFDlg::SURFDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SURFDIALOG, pParent)
{

}

SURFDlg::~SURFDlg()
{
}

void SURFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SURFDlg, CDialogEx)
END_MESSAGE_MAP()


// SURFDlg 消息处理程序
