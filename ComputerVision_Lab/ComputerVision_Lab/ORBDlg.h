#pragma once


// ORBDlg 对话框

class ORBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ORBDlg)

public:
	ORBDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ORBDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORBDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
