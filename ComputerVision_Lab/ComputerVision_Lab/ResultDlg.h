#pragma once


// PictureMosaic 对话框

class ResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ResultDlg)

public:
	ResultDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ResultDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESULTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CImage* ResultDataPointer=nullptr;
public:
	CStatic ResultPictureArea; //图像拼接结果显示区域
	void showResult(CImage* result);
	void showResult();
};
