// SIFTDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComputerVision_Lab.h"
#include "SIFTDlg.h"
#include "afxdialogex.h"


// SIFTDlg 对话框

IMPLEMENT_DYNAMIC(SIFTDlg, CDialogEx)

SIFTDlg::SIFTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIFTDIALOG, pParent)
{

}

SIFTDlg::~SIFTDlg()
{
}

void SIFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SIFTDlg, CDialogEx)
END_MESSAGE_MAP()


// SIFTDlg 消息处理程序
