#pragma once
#include <string>
using std::string;
#include "SIFTDlg.h"
#include "SURFDlg.h"
#include "ORBDlg.h"
#include "FERNSDlg.h"

#include "ResultDlg.h"
#include "KeyPointsDlg.h"


#ifndef CV2
#define CV2
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/features2d/hal/interface.h>
using namespace cv;
#endif // !CV2

// CComputerVisionLabDlg 对话框
class CComputerVisionLabDlg : public CDialogEx
{
// 构造
public:
	CComputerVisionLabDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPUTERVISION_LAB_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	

	/*各个界面部件*/
	CButton StartProcess; //开始处理
	CButton OpenFile1; //打开图片1的按钮
	CButton OpenFile2; //打开图片2的按钮
	CEdit FilePath1; //图片1文件路径
	CEdit FilePath2; //图片2文件路径
	
	CStatic Picture1Area; //图片1资源显示区域
	CStatic Picture2Area; //图片2资源显示区域
	CStatic Picture1Result;//图片1结果显示区域
	CStatic Picture2Result;//图片1结果显示区域

	CTabCtrl AlgorithmTab; //tab页
	SIFTDlg SIFTDlg;	//Sift Tab页
	SURFDlg SURFDlg;	//Surf Tab页 
	ORBDlg ORBDlg;		//ORB Tab页 
	FERNSDlg FERNSDlg;	//FERNS Tab页 

	CTabCtrl ResultTab; //结果tab页
	ResultDlg ResultDlg; //图像拼接 Tab页
	KeyPointsDlg KeyPointsDlg; //未筛选特征点 Tab页

	CEdit DebugInfo; //debug信息显示
	

	/*界面触发函数*/
	afx_msg void OnBnClickedOpenfile1();
	afx_msg void OnBnClickedOpenfile2();

	/*内部变量*/
	CImage Picture1_Data;
	CImage Picture2_Data;
	CImage Picture1_Result_Data;
	CImage Picture2_Result_Data;
	CString Picture1_Path;
	CString Picture2_Path;

	//内部函数(调试时使用）
	void showPicture1();
	void showPicture2();
	void showPicture1Result();
	void showPicture2Result();

	//Mat与CImage之间的转换，来源https://blog.csdn.net/liangjialang/article/details/33320093
	void MatToCImage(Mat& mat, CImage& cimage);
	void CImageToMat(CImage& cimage, Mat& mat);
	
	afx_msg void OnBnClickedStartprocess(); //开始执行	
	afx_msg void OnTcnSelchangeAlgorithmtab(NMHDR *pNMHDR, LRESULT *pResult); //选择tab页
	afx_msg void OnTcnSelchangeResulttab(NMHDR *pNMHDR, LRESULT *pResult); //选择结果tab页

	//各种实现
	void SIFT(); //特征点检测
	void SIFTMosaic(); //图像拼接
	
	//图片显示接口
	void showResult(CImage* result);
	
};
