#pragma once


// KeyPointsDlg 对话框

class KeyPointsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(KeyPointsDlg)

public:
	KeyPointsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~KeyPointsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KETPOINTSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
