#pragma once
#include <string>
using std::string;
#include "SIFTDlg.h"
#include "SURFDlg.h"
#include "ORBDlg.h"
#include "FERNSDlg.h"



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

	CStatic Picture1KeyPointsArea;//图片1原始关键点显示区域
	CStatic Picture2KeyPointsArea;//图片2原始关键点显示区域
	CStatic Picture1KeyPointsSArea;//图片1筛选后关键点显示区域
	CStatic Picture2KeyPointsSArea; //图片2筛选后关键点显示区域

	CStatic MosaicPictureArea;	//图像拼接结果显示区域
	CStatic MatchResultArea; //特征点匹配显示区域
	CStatic MatchResultSArea;	//经过筛选后的特征点匹配的显示区域

	

	CTabCtrl AlgorithmTab; //tab页
	SIFTDlg SIFTDlg;	//Sift Tab页
	SURFDlg SURFDlg;	//Surf Tab页 
	ORBDlg ORBDlg;		//ORB Tab页 
	FERNSDlg FERNSDlg;	//FERNS Tab页 

	CEdit DebugInfo; //debug信息显示
	

	/*界面触发函数*/
	afx_msg void OnBnClickedOpenfile1();
	afx_msg void OnBnClickedOpenfile2();

	/*内部变量*/
	CImage Picture1_Data;
	CImage Picture2_Data;
	CString Picture1_Path;
	CString Picture2_Path;

	CImage Picture1_KeyPointsData;
	CImage Picture2_KeyPointsData;	
	CImage Picture1_KeyPointsSData;
	CImage Picture2_KeyPointsSData;

	CImage MosaicPictureData;
	CImage MatchData;
	CImage MatchDataS;

	//内部函数(调试时使用）
	void showPicture1();
	void showPicture2();

	bool isEmpty(CImage &);

	//Mat与CImage之间的转换，来源https://blog.csdn.net/liangjialang/article/details/33320093
	bool MatToCImage(Mat& mat, CImage& cimage);
	bool CImageToMat(CImage& cimage, Mat& mat);
	
	afx_msg void OnBnClickedStartprocess(); //开始执行	
	afx_msg void OnTcnSelchangeAlgorithmtab(NMHDR *pNMHDR, LRESULT *pResult); //选择tab页

	afx_msg void OnBnClickedMosaicresultbutton(); //选择显示拼接后图片
	afx_msg void OnBnClickedKeypointsbutton(); //选择显示未筛选关键点
	afx_msg void OnBnClickedKeypointssbutton(); //选择显示筛选后关键点
	afx_msg void OnBnClickedMatchbutton(); //选择显示为筛选的匹配信息
	afx_msg void OnBnClickedMatchsbutton(); //选择显示筛选后匹配信息
	
	//各种实现（大家把自己的函数定义放在这里）
	void SIFT(); //特征点检测
	void SIFTMosaic(); //图像拼接
	void FernsFromChunHua();
	
	void SURF();
	void SURFMosaic();

	void ORB();
	void ORBMosaic();

	void FERNS();
	void FERNSMosaic();

	//图片显示接口
	void showImageToUI(CStatic&, CImage&);

	void showPicture1_KeyPointsData();
	void showPicture2_KeyPointsData();
	void showPicture1_KeyPointsSData();
	void showPicture2_KeyPointsSData();

	void showMasaicPicture();
	void showMatchData();
	void showMatchDataS();	
	
	//测试用函数
	float getRepeatability(vector<KeyPoint> KeyPoints1, vector<KeyPoint> KeyPoints2, Mat Picture1, Mat Picture2, Mat Homography);
	
};
#pragma comment( linker, "/subsystem:console /entry:WinMainCRTStartup" )