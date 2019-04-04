
// ComputerVision_LabDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ComputerVision_Lab.h"
#include "ComputerVision_LabDlg.h"
#include "afxdialogex.h"
#include "DebugManager.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <sstream>
using std::stringstream;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComputerVisionLabDlg 对话框



CComputerVisionLabDlg::CComputerVisionLabDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMPUTERVISION_LAB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComputerVisionLabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPENFILE1, OpenFile1);
	DDX_Control(pDX, IDC_OPENFILE2, OpenFile2);
	DDX_Control(pDX, IDC_FILEPATH1, FilePath1);
	DDX_Control(pDX, IDC_FILEPATH2, FilePath2);
	DDX_Control(pDX, IDC_STARTPROCESS, StartProcess);
	DDX_Control(pDX, IDC_PICTURE1, Picture1Area);
	DDX_Control(pDX, IDC_PICTURE2, Picture2Area);
	DDX_Control(pDX, IDC_DEBUGINFO, DebugInfo);
	DDX_Control(pDX, IDC_ALGORITHMTAB, AlgorithmTab);
	DDX_Control(pDX, IDC_PICTURE1RESULT, Picture1KeyPointsArea);
	DDX_Control(pDX, IDC_PICTURE2RESULT, Picture2KeyPointsArea);
	DDX_Control(pDX, IDC_MosaicPicture, MosaicPictureArea);
	DDX_Control(pDX, IDC_MATCH, MatchResultArea);
	DDX_Control(pDX, IDC_MATCH_S, MatchResultSArea);
	DDX_Control(pDX, IDC_KEYPOINTS_S, Picture1KeyPointsSArea);
	DDX_Control(pDX, IDC_KEYPOINTS2_S, Picture2KeyPointsSArea);
}

BEGIN_MESSAGE_MAP(CComputerVisionLabDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE1, &CComputerVisionLabDlg::OnBnClickedOpenfile1)
	ON_BN_CLICKED(IDC_OPENFILE2, &CComputerVisionLabDlg::OnBnClickedOpenfile2)
	ON_BN_CLICKED(IDC_STARTPROCESS, &CComputerVisionLabDlg::OnBnClickedStartprocess)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ALGORITHMTAB, &CComputerVisionLabDlg::OnTcnSelchangeAlgorithmtab)
	ON_BN_CLICKED(IDC_MOSAICRESULTBUTTON, &CComputerVisionLabDlg::OnBnClickedMosaicresultbutton)
	ON_BN_CLICKED(IDC_KEYPOINTSBUTTON, &CComputerVisionLabDlg::OnBnClickedKeypointsbutton)
	ON_BN_CLICKED(IDC_MATCHBUTTON, &CComputerVisionLabDlg::OnBnClickedMatchbutton)
	ON_BN_CLICKED(IDC_MATCHSBUTTON, &CComputerVisionLabDlg::OnBnClickedMatchsbutton)
	ON_BN_CLICKED(IDC_KEYPOINTSSBUTTON, &CComputerVisionLabDlg::OnBnClickedKeypointssbutton)
END_MESSAGE_MAP()


// CComputerVisionLabDlg 消息处理程序

BOOL CComputerVisionLabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	DebugManager::createInstance(this);

	/**************************Tab相关**************************/
	//各个算法的Tab项
	AlgorithmTab.InsertItem(0, _T("SIFT"));
	AlgorithmTab.InsertItem(1, _T("SURF"));
	AlgorithmTab.InsertItem(2, _T("ORB(FAST+BRIEF)"));
	AlgorithmTab.InsertItem(3, _T("Random Ferns"));



	//关联主对话框和各个子Tab页对话框
	SIFTDlg.Create(IDD_SIFTDIALOG, GetDlgItem(IDD_COMPUTERVISION_LAB_DIALOG));
	SURFDlg.Create(IDD_SURFDIALOG, GetDlgItem(IDD_COMPUTERVISION_LAB_DIALOG));
	ORBDlg.Create(IDD_ORBDIALOG, GetDlgItem(IDD_COMPUTERVISION_LAB_DIALOG));
	FERNSDlg.Create(IDD_FERNSDIALOG, GetDlgItem(IDD_COMPUTERVISION_LAB_DIALOG));


	//创建显示区域
	CRect tabArea;
	AlgorithmTab.GetClientRect(&tabArea);

	//调整对话框的位置
	tabArea.top += 102;
	tabArea.bottom += 80;
	tabArea.left += 102;
	tabArea.right += 102;

	//移动子Tab页到指定的地方
	SIFTDlg.MoveWindow(&tabArea);
	SURFDlg.MoveWindow(&tabArea);
	ORBDlg.MoveWindow(&tabArea);
	FERNSDlg.MoveWindow(&tabArea);

	//分别设置隐藏和显示 
	SIFTDlg.ShowWindow(true);
	SURFDlg.ShowWindow(false);
	ORBDlg.ShowWindow(false);
	FERNSDlg.ShowWindow(false);

	//设置默认的选项卡
	AlgorithmTab.SetCurSel(0);
	/**************************Tab相关**************************/

	/**************************结果显示相关**************************/
	MosaicPictureArea.ShowWindow(true);

	Picture1KeyPointsArea.ShowWindow(false);
	Picture2KeyPointsArea.ShowWindow(false);
	MatchResultArea.ShowWindow(false);
	MatchResultSArea.ShowWindow(false);
	Picture1KeyPointsSArea.ShowWindow(false);
	Picture2KeyPointsSArea.ShowWindow(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComputerVisionLabDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		showPicture1();
		showPicture2();
		showPicture1_KeyPointsData();
		showPicture2_KeyPointsData();
		showPicture1_KeyPointsSData();
		showPicture2_KeyPointsSData();
		showMasaicPicture();
		showMatchData();
		showMatchDataS();	
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComputerVisionLabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**********************控件操作**********************/
//读取图片1
void CComputerVisionLabDlg::OnBnClickedOpenfile1()
{
	TCHAR szFilter[] = _T("JPEG(*jpg)|*.jpg|*.bmp|*.png|TIFF(*.tif)|*.tif|All Files （*.*）|*.*||");
	CString filePath("");

	CFileDialog fileOpenDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	//如果用户选择了OK按钮
	if (fileOpenDialog.DoModal() == IDOK)
	{
		VERIFY(filePath = fileOpenDialog.GetPathName());
		CString strFilePath(filePath);
		Picture1_Path = filePath;
		FilePath1.SetWindowTextW(strFilePath);

		/*if (Picture1_Data != NULL)
		{
			delete Picture1_Data;
		}*/
		Picture1_Data.Load(strFilePath);

		/*if (handledImage != NULL)
		{
			delete handledImage;
		}
		handledImage = new CImage();
		handledImage->Load(strFilePath);*/

		Picture1_KeyPointsData.Detach();
		Picture2_KeyPointsData.Detach();
		Picture1_KeyPointsSData.Detach();
		Picture2_KeyPointsSData.Detach();

		MosaicPictureData.Detach();
		MatchData.Detach();
		MatchDataS.Detach();
		//重新绘制
		this->Invalidate();
	}
}

//读取图片2
void CComputerVisionLabDlg::OnBnClickedOpenfile2()
{
	TCHAR szFilter[] = _T("JPEG(*jpg)|*.jpg|*.bmp|*.png|TIFF(*.tif)|*.tif|All Files （*.*）|*.*||");
	CString filePath("");

	CFileDialog fileOpenDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	//如果用户选择了OK按钮
	if (fileOpenDialog.DoModal() == IDOK)
	{
		VERIFY(filePath = fileOpenDialog.GetPathName());
		CString strFilePath(filePath);
		Picture2_Path = filePath;
		FilePath2.SetWindowTextW(strFilePath);

		/*if (Picture2_Data != NULL)
		{
			delete Picture2_Data;
		}*/
		Picture2_Data.Load(strFilePath);

		/*if (handledImage != NULL)
		{
			delete handledImage;
		}
		handledImage = new CImage();
		handledImage->Load(strFilePath);*/


		Picture1_KeyPointsData.Detach();
		Picture2_KeyPointsData.Detach();
		Picture1_KeyPointsSData.Detach();
		Picture2_KeyPointsSData.Detach();

		MosaicPictureData.Detach();
		MatchData.Detach();
		MatchDataS.Detach();
		//重新绘制
		this->Invalidate();
	}
}

//更新图片1区域的内容
void CComputerVisionLabDlg::showPicture1()
{
	if (Picture1_Data != NULL)
	{
		int height;
		int width;

		CRect WorkSpaceRect;
		CRect ShowImageRect;

		//记录图片本身的长和宽
		height = Picture1_Data.GetHeight();
		width = Picture1_Data.GetWidth();

		Picture1Area.GetClientRect(&WorkSpaceRect); //根据GUI中的工作区生成一个矩形对象，左上角为（0，0）
		CDC *pDC = Picture1Area.GetDC();	//设备上下文（Device Contex）->指向图片数据？
		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//设置图片拉伸的模式，设置为HalfTone，这个模式下，应用程序必须调用Win32函数 SetBrushOrgEx 设置画笔原点

		if (width <= WorkSpaceRect.Width() && height <= WorkSpaceRect.Width()) //图片完全可以在工作区中以原来的大小放下
		{
			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize(width, height)); //创建另一个矩形，左上角点和工作区一致，使用CSize传入矩形大小
			Picture1_Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		else //图片在工作区中不能以原来的大小放下
		{
			float xScale = (float)WorkSpaceRect.Width() / (float)width; //记录原工作区矩形和图片的长度比例
			float yScale = (float)WorkSpaceRect.Height() / (float)height; //记录原工作区矩形和图片的宽度比例
			float ScaleIndex = (xScale <= yScale ? xScale : yScale); //选出较小的比例

			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize((int)width*ScaleIndex, (int)height*ScaleIndex)); //创建一个由原图片按照刚刚获取的较小的比例缩放的，保证能整个放入工作区的矩形
			Picture1_Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		ReleaseDC(pDC); //将上下文释放
	}
}

//更新图片2区域的内容
void CComputerVisionLabDlg::showPicture2()
{
	if (Picture2_Data != NULL)
	{
		int height;
		int width;

		CRect WorkSpaceRect;
		CRect ShowImageRect;

		//记录图片本身的长和宽
		height = Picture2_Data.GetHeight();
		width = Picture2_Data.GetWidth();

		Picture2Area.GetClientRect(&WorkSpaceRect); //根据GUI中的工作区生成一个矩形对象，左上角为（0，0）
		CDC *pDC = Picture2Area.GetDC();	//设备上下文（Device Contex）->指向图片数据？
		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//设置图片拉伸的模式，设置为HalfTone，这个模式下，应用程序必须调用Win32函数 SetBrushOrgEx 设置画笔原点

		if (width <= WorkSpaceRect.Width() && height <= WorkSpaceRect.Width()) //图片完全可以在工作区中以原来的大小放下
		{
			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize(width, height)); //创建另一个矩形，左上角点和工作区一致，使用CSize传入矩形大小
			Picture2_Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		else //图片在工作区中不能以原来的大小放下
		{
			float xScale = (float)WorkSpaceRect.Width() / (float)width; //记录原工作区矩形和图片的长度比例
			float yScale = (float)WorkSpaceRect.Height() / (float)height; //记录原工作区矩形和图片的宽度比例
			float ScaleIndex = (xScale <= yScale ? xScale : yScale); //选出较小的比例

			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize((int)width*ScaleIndex, (int)height*ScaleIndex)); //创建一个由原图片按照刚刚获取的较小的比例缩放的，保证能整个放入工作区的矩形
			Picture2_Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		ReleaseDC(pDC); //将上下文释放
	}
}

//开始进行处理（大家把自己对应要执行的函数放在这里）
void CComputerVisionLabDlg::OnBnClickedStartprocess()
{
	//判断处理的函数是否为空
	if (Picture1_Data.GetHeight() == 0 && Picture1_Data.GetWidth() == 0)
	{
		DebugManager::getInstance()->pushLog("处理图片不能为空！\r\n");
		return;
	}
	if (Picture2_Data.GetHeight() == 0 && Picture2_Data.GetWidth() == 0)
	{
		DebugManager::getInstance()->pushLog("处理图片不能为空！\r\n");
		return;
	}

	switch (AlgorithmTab.GetCurSel())
	{
	case 0: //SIFT
	{
		//SIFT
		//SIFT();
		SIFTMosaic();
		break;
	}
	case 1: //SURF
	{
		break;
	}
	case 2: //ORB
	{
		ORBMosaic();
		break;
	}
	case 3: //FERNS
	{
		FERNS();
		break;
	}
	default:
		break;
	}

}

//tab页的选择
void CComputerVisionLabDlg::OnTcnSelchangeAlgorithmtab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int currentTab = AlgorithmTab.GetCurSel();

	SIFTDlg.ShowWindow(false);
	SURFDlg.ShowWindow(false);
	ORBDlg.ShowWindow(false);
	FERNSDlg.ShowWindow(false);

	switch (currentTab)
	{
	case 0:
	{
		SIFTDlg.ShowWindow(true);
		break;
	}
	case 1:
	{
		SURFDlg.ShowWindow(true);
		break;
	}
	case 2:
	{
		ORBDlg.ShowWindow(true);
		break;
	}
	case 3:
	{
		FERNSDlg.ShowWindow(true);
		break;
	}
	default:
		break;
	}
	*pResult = 0;
}

//显示图像拼接结果
void CComputerVisionLabDlg::OnBnClickedMosaicresultbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	Picture1KeyPointsArea.ShowWindow(false);
	Picture2KeyPointsArea.ShowWindow(false);
	MatchResultArea.ShowWindow(false);
	MatchResultSArea.ShowWindow(false);
	Picture1KeyPointsSArea.ShowWindow(false);
	Picture2KeyPointsSArea.ShowWindow(false);

	MosaicPictureArea.ShowWindow(true);
}

//显示原始关键点检测结果
void CComputerVisionLabDlg::OnBnClickedKeypointsbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	MosaicPictureArea.ShowWindow(false);
	MatchResultArea.ShowWindow(false);
	MatchResultSArea.ShowWindow(false);
	Picture1KeyPointsSArea.ShowWindow(false);
	Picture2KeyPointsSArea.ShowWindow(false);

	Picture1KeyPointsArea.ShowWindow(true);
	Picture2KeyPointsArea.ShowWindow(true);
}

//显示原始匹配结果
void CComputerVisionLabDlg::OnBnClickedMatchbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	MosaicPictureArea.ShowWindow(false);
	Picture1KeyPointsArea.ShowWindow(false);
	Picture2KeyPointsArea.ShowWindow(false);
	MatchResultSArea.ShowWindow(false);
	Picture1KeyPointsSArea.ShowWindow(false);
	Picture2KeyPointsSArea.ShowWindow(false);

	MatchResultArea.ShowWindow(true);
}

//显示经过筛选后的匹配结果
void CComputerVisionLabDlg::OnBnClickedMatchsbutton()
{
	Picture1KeyPointsArea.ShowWindow(false);
	Picture2KeyPointsArea.ShowWindow(false);
	MatchResultArea.ShowWindow(false);
	MosaicPictureArea.ShowWindow(false);
	Picture1KeyPointsSArea.ShowWindow(false);
	Picture2KeyPointsSArea.ShowWindow(false);

	MatchResultSArea.ShowWindow(true);
}

//显示经过筛选后的特征点结果
void CComputerVisionLabDlg::OnBnClickedKeypointssbutton()
{
	Picture1KeyPointsArea.ShowWindow(false);
	Picture2KeyPointsArea.ShowWindow(false);
	MatchResultArea.ShowWindow(false);
	MatchResultSArea.ShowWindow(false);
	MosaicPictureArea.ShowWindow(false);

	Picture1KeyPointsSArea.ShowWindow(true);
	Picture2KeyPointsSArea.ShowWindow(true);
}

/**********************Mat和CImage之间的转换**********************/
void CComputerVisionLabDlg::MatToCImage(Mat & mat, CImage & cimage)
{
	if (0 == mat.total())
	{
		return;
	}


	int nChannels = mat.channels();
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = mat.cols;
	int nHeight = mat.rows;


	//重建cimage
	cimage.Destroy();
	cimage.Create(nWidth, nHeight, 8 * nChannels);


	//拷贝数据


	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负


	if (1 == nChannels)								//对于单通道的图像需要初始化调色板
	{
		RGBQUAD* rgbquadColorTable;
		int nMaxColors = 256;
		rgbquadColorTable = new RGBQUAD[nMaxColors];
		cimage.GetColorTable(0, nMaxColors, rgbquadColorTable);
		for (int nColor = 0; nColor < nMaxColors; nColor++)
		{
			rgbquadColorTable[nColor].rgbBlue = (uchar)nColor;
			rgbquadColorTable[nColor].rgbGreen = (uchar)nColor;
			rgbquadColorTable[nColor].rgbRed = (uchar)nColor;
		}
		cimage.SetColorTable(0, nMaxColors, rgbquadColorTable);
		delete[]rgbquadColorTable;
	}


	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				*(pucImage + nRow * nStep + nCol) = pucRow[nCol];
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					*(pucImage + nRow * nStep + nCol * 3 + nCha) = pucRow[nCol * 3 + nCha];
				}
			}
		}
	}
}
void CComputerVisionLabDlg::CImageToMat(CImage & cimage, Mat & mat)
{
	if (true == cimage.IsNull())
	{
		return;
	}


	int nChannels = cimage.GetBPP() / 8;
	if ((1 != nChannels) && (3 != nChannels))
	{
		return;
	}
	int nWidth = cimage.GetWidth();
	int nHeight = cimage.GetHeight();


	//重建mat
	if (1 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC1);
	}
	else if (3 == nChannels)
	{
		mat.create(nHeight, nWidth, CV_8UC3);
	}


	//拷贝数据


	uchar* pucRow;									//指向数据区的行指针
	uchar* pucImage = (uchar*)cimage.GetBits();		//指向数据区的指针
	int nStep = cimage.GetPitch();					//每行的字节数,注意这个返回值有正有负


	for (int nRow = 0; nRow < nHeight; nRow++)
	{
		pucRow = (mat.ptr<uchar>(nRow));
		for (int nCol = 0; nCol < nWidth; nCol++)
		{
			if (1 == nChannels)
			{
				pucRow[nCol] = *(pucImage + nRow * nStep + nCol);
			}
			else if (3 == nChannels)
			{
				for (int nCha = 0; nCha < 3; nCha++)
				{
					pucRow[nCol * 3 + nCha] = *(pucImage + nRow * nStep + nCol * 3 + nCha);
				}
			}
		}
	}
}


/**********************SIFT算法（大家把自己的函数放到这里）**********************/
//使用SIFT进行特征点匹配(这东西没有经过特殊处理，请不要调用，在2.4.9下运行会爆炸)
void CComputerVisionLabDlg::SIFT()
{
	initModule_nonfree();
	/******************进行特征点识别******************/
	Mat sourceImage1;
	CImageToMat(Picture1_Data, sourceImage1);

	Mat sourceImage2;
	CImageToMat(Picture2_Data, sourceImage2);

	//进行高斯模糊
	Mat sourceImage1AfterBlur, sourceImage2AfterBlur;
	cv::GaussianBlur(sourceImage1, sourceImage1AfterBlur, Size(3, 3), 0.5);
	cv::GaussianBlur(sourceImage2, sourceImage2AfterBlur, Size(3, 3), 0.5);

	//检测特征点并保存到两个特征点数组中
	SurfFeatureDetector SIFT;
	vector<KeyPoint> keyPoint1, keyPoint2;
	SIFT.detect(sourceImage1AfterBlur, keyPoint1);
	SIFT.detect(sourceImage2AfterBlur, keyPoint2);

	/*画出特征点并展示*/
	//{
	//	drawKeypoints(sourceImage1AfterBlur, keyPoint1, sourceImage1AfterBlur, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//	drawKeypoints(sourceImage2AfterBlur, keyPoint2, sourceImage2AfterBlur, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//	MatToCImage(sourceImage1AfterBlur, Picture1_Result_Data);
	//	MatToCImage(sourceImage2AfterBlur, Picture2_Result_Data);

	//	showPicture1Result();
	//	showPicture2Result();
	//}

	/******************进行两幅图的特征点匹配工作******************/
	Mat descriptors_1, descriptors_2;
	SIFT.compute(sourceImage1AfterBlur, keyPoint1, descriptors_1);
	SIFT.compute(sourceImage2AfterBlur, keyPoint2, descriptors_2);

	BFMatcher matcher;
	vector<DMatch>matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//画出消去前的图像
	Mat Result;
	drawMatches(sourceImage1AfterBlur, keyPoint1, sourceImage2AfterBlur, keyPoint2, matches, Result);

	MatToCImage(Result, Picture1_KeyPointsData);
	showPicture1_KeyPointsData();

	/*******************使用RANSAC进行消除工作******************/
	vector<KeyPoint> R_keypoint1, R_keypoint2;
	for (size_t i = 0; i < matches.size(); i++)
	{
		R_keypoint1.push_back(keyPoint1[matches[i].queryIdx]);
		R_keypoint2.push_back(keyPoint2[matches[i].trainIdx]);
		//这两句话的理解：R_keypoint1是要存储img01中能与img02匹配的特征点，
		//matches中存储了这些匹配点对的img01和img02的索引值
	}

	//坐标转换
	vector<Point2f>p01, p02;
	for (size_t i = 0; i < matches.size(); i++)
	{
		p01.push_back(R_keypoint1[i].pt);
		p02.push_back(R_keypoint2[i].pt);
	}

	vector<uchar> RansacStatus;
	Mat Fundamental = findFundamentalMat(p01, p02, RansacStatus, FM_RANSAC);

	vector<KeyPoint> RR_keypoint01, RR_keypoint02;
	vector<DMatch> MatchePointsAfterRANSAC;
	int index = 0;
	for (size_t i = 0; i < matches.size(); i++)
	{
		if (RansacStatus[i] != 0)
		{
			RR_keypoint01.push_back(R_keypoint1[i]);
			RR_keypoint02.push_back(R_keypoint2[i]);
			matches[i].queryIdx = index;
			matches[i].trainIdx = index;
			MatchePointsAfterRANSAC.push_back(matches[i]);
			index++;
		}
	}

	Mat ResultAfterRANSAC;
	drawMatches(sourceImage1AfterBlur, RR_keypoint01, sourceImage2AfterBlur, RR_keypoint02, MatchePointsAfterRANSAC, ResultAfterRANSAC);

	MatToCImage(ResultAfterRANSAC, Picture2_KeyPointsData);
	showPicture2_KeyPointsData();
	imwrite("C:\\Users\\39471\\Desktop\\图像拼接\\result.jpg", ResultAfterRANSAC);
}

//使用SIFT进行特征点匹配然后进行图像拼接
void CComputerVisionLabDlg::SIFTMosaic()
{
	initModule_nonfree();
	Mat SourceImage1;
	CImageToMat(Picture1_Data, SourceImage1);

	Mat SourceImage2;
	CImageToMat(Picture2_Data, SourceImage2);

	Mat GreySourceImage1;
	Mat GreySourceImage2;

	cvtColor(SourceImage1, GreySourceImage1, CV_BGR2GRAY);
	cvtColor(SourceImage2, GreySourceImage2, CV_BGR2GRAY);

	//-- Step 1: 使用SIFT识别出特征点
	SiftFeatureDetector SIFT;
	std::vector<KeyPoint> KeyPoints1, KeyPoints2;
	KeyPoints1.reserve(1000000);
	KeyPoints2.reserve(1000000);

	SIFT.detect(GreySourceImage1, KeyPoints1);
	SIFT.detect(GreySourceImage2, KeyPoints2);

	Mat picture1KeyPointsResult;
	drawKeypoints(SourceImage1, KeyPoints1, picture1KeyPointsResult, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	MatToCImage(picture1KeyPointsResult, Picture1_KeyPointsData);
	showPicture1_KeyPointsData();

	Mat picture2KeyPointsResult;
	drawKeypoints(SourceImage2, KeyPoints2, picture2KeyPointsResult, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	MatToCImage(picture2KeyPointsResult, Picture2_KeyPointsData);
	showPicture2_KeyPointsData();

	//-- Step 2: 描述SIFT特征
	Mat Descriptors1, Descriptors2;
	SIFT.compute(GreySourceImage1, KeyPoints1, Descriptors1);
	SIFT.compute(GreySourceImage2, KeyPoints2, Descriptors2);

	//-- Step 3: 计算匹配点
	BFMatcher Matcher;//BFMatcher为强制匹配
	std::vector< DMatch > MatchPoints;
	MatchPoints.reserve(1000000);
	Matcher.match(Descriptors1, Descriptors2, MatchPoints);

	Mat MatchResult;
	drawMatches(SourceImage1, KeyPoints1, SourceImage2, KeyPoints2, MatchPoints, MatchResult);
	MatToCImage(MatchResult, MatchData);
	showMatchData();

	//-- Step 4: 筛选匹配点
	//计算所有匹配点中的最大最小距离
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < Descriptors1.rows; i++)
	{
		double dist = MatchPoints[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	std::vector< DMatch > GoodMatchPoints;

	//如果特征描述子的距离小于最小距离的3倍，则被认为是好的匹配点
	for (int i = 0; i < Descriptors1.rows; i++)
	{
		if (MatchPoints[i].distance <= 3 * min_dist)
		{
			GoodMatchPoints.push_back(MatchPoints[i]);
		}
	}

	//-- Step4.5: 使用RANSAC对原始匹配点进行筛选（展现实验结果)
	vector<KeyPoint> R_keypoint1, R_keypoint2;
	R_keypoint1.reserve(1000000);
	R_keypoint2.reserve(1000000);

	for (size_t i = 0; i < GoodMatchPoints.size(); i++)
	{
		R_keypoint1.push_back(KeyPoints1[GoodMatchPoints[i].queryIdx]);
		R_keypoint2.push_back(KeyPoints2[GoodMatchPoints[i].trainIdx]);
		//这两句话的理解：R_keypoint1是要存储img01中能与img02匹配的特征点，
		//matches中存储了这些匹配点对的img01和img02的索引值
	}

	//坐标转换
	vector<Point2f>p01(GoodMatchPoints.size()), p02(GoodMatchPoints.size());
	p01.reserve(GoodMatchPoints.size());
	p02.reserve(GoodMatchPoints.size());

	for (size_t i = 0; i < GoodMatchPoints.size(); i++)
	{
		p01[i]=(R_keypoint1[i].pt);
		p02[i]=(R_keypoint2[i].pt);
	}

	vector<uchar> RansacStatus;
	RansacStatus.reserve(1000000);

	Mat Fundamental = findFundamentalMat(p01, p02, RansacStatus, FM_RANSAC);

	vector<KeyPoint> RR_keypoint01, RR_keypoint02;
	RR_keypoint01.reserve(GoodMatchPoints.size());
	RR_keypoint02.reserve(GoodMatchPoints.size());

	vector<DMatch> MatchePointsAfterRANSAC;
	MatchePointsAfterRANSAC.reserve(GoodMatchPoints.size());

	int index = 0;
	for (size_t i = 0; i < GoodMatchPoints.size(); i++)
	{
		if (RansacStatus[i] != 0)
		{
			RR_keypoint01.push_back(R_keypoint1[i]);
			RR_keypoint02.push_back(R_keypoint2[i]);
			DMatch buf;
			buf.queryIdx = index;
			buf.trainIdx = index;
			MatchePointsAfterRANSAC.push_back(buf);
			index++;
		}
	}	

	Mat picture1KeyPointsResultAfterRANSAC;
	drawKeypoints(SourceImage1, RR_keypoint01, picture1KeyPointsResultAfterRANSAC, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	MatToCImage(picture1KeyPointsResultAfterRANSAC, Picture1_KeyPointsSData);
	showPicture1_KeyPointsSData();

	Mat picture2KeyPointsResultAfterRANSAC;
	drawKeypoints(SourceImage2, RR_keypoint02, picture2KeyPointsResultAfterRANSAC, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	MatToCImage(picture2KeyPointsResultAfterRANSAC, Picture2_KeyPointsSData);
	showPicture2_KeyPointsSData();

	Mat ResultAfterRANSAC;
	drawMatches(SourceImage1, RR_keypoint01, SourceImage2, RR_keypoint02, MatchePointsAfterRANSAC, ResultAfterRANSAC);

	MatToCImage(ResultAfterRANSAC, MatchDataS);
	showMatchDataS();

	//-- Step 5: 计算映射矩阵（利用RANSAC进一步选择相对最优的匹配点）
	//把图像二向图像一映射
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;
	for (int i = 0; i < (int)GoodMatchPoints.size(); i++)
	{
		//这里采用“帧向拼接图像中添加的方法”，因此左边的是scene,右边的是obj
		scene.push_back(KeyPoints1[GoodMatchPoints[i].queryIdx].pt);
		obj.push_back(KeyPoints2[GoodMatchPoints[i].trainIdx].pt);
	}

	//直接调用ransac,计算单应矩阵（计算映射矩阵）
	Mat Homography = findHomography(obj, scene, CV_RANSAC);

	//-- Step 6:利用得到的映射矩阵，进行图像对准及图像拼接
	Mat result;

	long long maxCols;
	int maxColsPic;

	if (GreySourceImage1.cols > GreySourceImage2.cols)
	{
		maxCols = GreySourceImage1.cols;
		maxColsPic = 1;
	}
	else
	{
		maxCols = GreySourceImage2.cols;
		maxColsPic = 2;
	}

	long long maxRows;
	int maxRowsPic;

	if (GreySourceImage1.rows > GreySourceImage2.rows)
	{
		maxRows = GreySourceImage1.rows;
		maxRowsPic = 1;
	}
	else
	{
		maxRows = GreySourceImage2.rows;
		maxRowsPic = 2;
	}

	warpPerspective(SourceImage2, result, Homography, Size(2 * maxCols, maxRows));
	Mat half(result, cv::Rect(0, 0, GreySourceImage1.cols, GreySourceImage1.rows));
	SourceImage1.copyTo(half);

	MatToCImage(result, MosaicPictureData);
	imwrite("C:\\Users\\39471\\Desktop\\图像拼接\\MosaicPicture.jpg", result);
	showMasaicPicture();
	//imshow("result", result);
	waitKey(0);
}

//自己尝试修改Ferns（羞耻的失败了，难受）
void CComputerVisionLabDlg::CJWFerns()
{
	Mat SourceImage1;
	CImageToMat(Picture1_Data, SourceImage1);

	Mat SourceImage2;
	CImageToMat(Picture2_Data, SourceImage2);

	Mat GreySourceImage1;
	Mat GreySourceImage2;

	cvtColor(SourceImage1, GreySourceImage1, CV_BGR2GRAY);
	cvtColor(SourceImage2, GreySourceImage2, CV_BGR2GRAY);

	Size patchSize(32, 32);
	LDetector ldetector(7, 20, 2, 2000, patchSize.width, 2);
	ldetector.setVerbose(true);
	PlanarObjectDetector detector;

	vector<Mat> objpyr, imgpyr;
	objpyr.reserve(1000000);
	imgpyr.reserve(1000000);
	int blurKSize = 3;
	double sigma = 0;
	GaussianBlur(GreySourceImage1, GreySourceImage1, Size(blurKSize, blurKSize), sigma, sigma);
	GaussianBlur(GreySourceImage2, GreySourceImage2, Size(blurKSize, blurKSize), sigma, sigma);
	buildPyramid(GreySourceImage1, objpyr, ldetector.nOctaves - 1);
	buildPyramid(GreySourceImage1, imgpyr, ldetector.nOctaves - 1);

	vector<KeyPoint> Picture1Keypoints, Picture2Keypoints;
	Picture1Keypoints.reserve(1000000);
	Picture2Keypoints.reserve(1000000);
	PatchGenerator gen(0, 256, 5, true, 0.8, 1.2, -CV_PI / 2, CV_PI / 2, -CV_PI / 2, CV_PI / 2); //生成噪声

	string model_filename = format("%s_model.xml.gz", Picture1_Path);
	//printf("Trying to load %s ...\n", model_filename.c_str());
	FileStorage fs(model_filename, FileStorage::READ);
	if (fs.isOpened())
	{
		detector.read(fs.getFirstTopLevelNode());
		printf("Successfully loaded %s.\n", model_filename.c_str());
	}
	else
	{
		ldetector.setVerbose(true);
		ldetector.getMostStable2D(GreySourceImage1, Picture1Keypoints, 100, gen);		
		detector.setVerbose(true);

		//detector.train(objpyr, Picture1Keypoints, patchSize.width, 100, 11, 10000, ldetector, gen);		
	/*	if (fs.open(model_filename, FileStorage::WRITE))
			detector.write(fs, "ferns_model");*/
	}



	////--Step 1:Finding the robust keypoints（找到robust的特征点）
	////ldetector.setVerbose(true);
	////ldetector.getMostStable2D(GreySourceImage1, Picture1Keypoints, 100, gen);

	////--Step 2:Training ferns-based planar object detector（训练基于蕨的平面对象探测器）
	////detector.setVerbose(true);
	////detector.train(objpyr, Picture1Keypoints, patchSize.width, 100, 11, 10000, ldetector, gen);

	////--Step 3:把训练出来的detector 保存成一个模型（这里我们就不做了）

	////-Step 4：至此，已经得到了对应的特征点了
	//vector<Point2f> dst_corners;
	//dst_corners.reserve(1000000);
	////创建一个3通道的8为的unsigned int的矩阵，矩阵长为两张图片中比较长的那一个那么长，高为两张图片加起来那么高，目前感觉应该是用来保存最后拼接完成的图片的（莫非他是要纵向拼接？？）
	//Mat correspond(GreySourceImage1.rows + GreySourceImage2.rows, std::max(GreySourceImage1.cols, GreySourceImage2.cols), CV_8UC3); 
	//correspond = Scalar(0.0); //把这副图片全部初始化为（0，0，0）的多通道图片

	///*把两张图片上下放置*/
	////图片1放在上面
	//Mat part(correspond, Rect(0, 0, GreySourceImage1.cols, GreySourceImage1.rows));
	//cvtColor(GreySourceImage1, part, CV_GRAY2BGR);
	////图片2放在下面
	//part = Mat(correspond, Rect(0, GreySourceImage1.rows, GreySourceImage2.cols, GreySourceImage2.rows));
	//cvtColor(GreySourceImage2, part, CV_GRAY2BGR);

	//vector<int> pairs;
	//pairs.reserve(1000000);
	//Mat H;

	////double t = (double)getTickCount();
	//Picture1Keypoints = detector.getModelPoints(); //拿到图片一的特征点
	//ldetector(imgpyr, Picture2Keypoints, 300); //拿到图片二的特征点？？？

	////std::cout << "Object keypoints: " << objKeypoints.size() << "\n";
	////std::cout << "Image keypoints: " << imgKeypoints.size() << "\n";
	//bool found = detector(imgpyr, Picture2Keypoints, H, dst_corners, &pairs);
	////t = (double)getTickCount() - t;
	////printf("%gms\n", t * 1000 / getTickFrequency());

	//if (found)
	//{
	//	for (int i = 0; i < 4; i++)
	//	{
	//		Point r1 = dst_corners[i % 4];
	//		Point r2 = dst_corners[(i + 1) % 4];
	//		line(correspond, Point(r1.x, r1.y + GreySourceImage1.rows),
	//			Point(r2.x, r2.y + GreySourceImage1.rows), Scalar(0, 0, 255));
	//	}
	//}

	//for (int i = 0; i < (int)pairs.size(); i += 2)
	//{
	//	line(correspond, Picture1Keypoints[pairs[i]].pt,
	//		Picture2Keypoints[pairs[i + 1]].pt + Point2f(0, (float)GreySourceImage1.rows),
	//		Scalar(0, 255, 0));
	//}

	//imshow("Object Correspondence", correspond);


	///*Mat objectColor;
	//cvtColor(GreySourceImage1, objectColor, CV_GRAY2BGR);
	//for (int i = 0; i < (int)Picture1Keypoints.size(); i++)
	//{
	//	circle(objectColor, Picture1Keypoints[i].pt, 2, Scalar(0, 0, 255), -1);
	//	circle(objectColor, Picture1Keypoints[i].pt, (1 << Picture1Keypoints[i].octave) * 15, Scalar(0, 255, 0), 1);
	//}
	//Mat imageColor;
	//cvtColor(GreySourceImage2, imageColor, CV_GRAY2BGR);
	//for (int i = 0; i < (int)Picture2Keypoints.size(); i++)
	//{
	//	circle(imageColor, Picture2Keypoints[i].pt, 2, Scalar(0, 0, 255), -1);
	//	circle(imageColor, Picture2Keypoints[i].pt, (1 << Picture2Keypoints[i].octave) * 15, Scalar(0, 255, 0), 1);
	//}*/

	//imshow("correspond.png", correspond);

	////imshow("Object", objectColor);
	////imshow("Image", imageColor);

	//waitKey(0);




}

//ORB
void CComputerVisionLabDlg::ORB() {

}

//使用ORB进行图像拼接
void CComputerVisionLabDlg::ORBMosaic() {
	Mat img1, img2;
	CImageToMat(Picture1_Data, img1);
	CImageToMat(Picture2_Data, img2);
	Mat GreySourceImage1;
	Mat GreySourceImage2;

	cvtColor(img1, GreySourceImage1, CV_BGR2GRAY);
	cvtColor(img2, GreySourceImage2, CV_BGR2GRAY);

	vector<KeyPoint> keypoints1, keypoints2;
	keypoints1.reserve(10000);
	keypoints2.reserve(10000);
	Mat des1, des2;

	OrbFeatureDetector detector;
	//<ORB> detector = ORB::create(3000);
	/*detector->detectAndCompute(scene, Mat(), keypoints_scene, des_scene);
	detector->detectAndCompute(box, Mat(), keypoints_obj, des_box);*/
	detector.detect(GreySourceImage1, keypoints1);
	detector.detect(GreySourceImage2, keypoints2);

	Mat picture1KeyPointsResult;
	drawKeypoints(img1, keypoints1, picture1KeyPointsResult, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	MatToCImage(picture1KeyPointsResult, Picture1_KeyPointsData);
	showPicture1_KeyPointsData();

	Mat picture2KeyPointsResult;
	drawKeypoints(img2, keypoints2, picture2KeyPointsResult, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	MatToCImage(picture2KeyPointsResult, Picture2_KeyPointsData);
	showPicture2_KeyPointsData();

	detector.compute(GreySourceImage1, keypoints1, des1);
	detector.compute(GreySourceImage2, keypoints2, des2);

	//cout << keypoints1.size() << endl;
	//cout << keypoints2.size() << endl;

	Mat out1;
	drawKeypoints(img1, keypoints1, out1);
	//imshow("ORB特征点", out1);


	vector<DMatch> matches;
	matches.reserve(1000);
	//Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
	BFMatcher matcher;

	//Ptr<DescriptorMatcher> matcher = makePtr<FlannBasedMatcher>(makePtr<flann::LshIndexParams>(12, 2, 2));
	matcher.match(des1, des2, matches);


	Mat MatchResult;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, MatchResult);
	MatToCImage(MatchResult, MatchData);
	showMatchData();
	//vector<DMatch> goodMatches;
	cout << "total match points : " << " " << matches.size() << endl;
	double min_dist = 500, max_dist = 0;
	for (int i = 0; i < matches.size(); ++i) {
		double dist = matches[i].distance;
		//cout << dist << endl;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	/*cout << "maxdist " << max_dist << endl;
	cout << "mindist " << min_dist << endl;*/

	Mat matchesImg;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, matchesImg);
	//imshow("配对", matchesImg);

	sort(matches.begin(), matches.end());
	vector<DMatch> goodMatches;
	int ptsPairs = std::min(150, (int)(matches.size() * 0.15));
	//cout << "pts" << ptsPairs << endl;

	for (int i = 0; i < ptsPairs; ++i) {
		if (matches[i].distance <= (0.6*max_dist)) {
			goodMatches.push_back(matches[i]);
		}
		//goodMatches.push_back(matches[i]);
	}
	cout << "good matches" << goodMatches.size() << endl;
	Mat img_good;
	drawMatches(img1, keypoints1, img2, keypoints2, goodMatches, img_good, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//imshow("good", img_good);

	vector<KeyPoint> R_keypoint1, R_keypoint2;
	R_keypoint1.reserve(10000);
	R_keypoint2.reserve(10000);
	for (size_t i = 0; i < goodMatches.size(); i++)
	{
		R_keypoint1.push_back(keypoints1[goodMatches[i].queryIdx]);
		R_keypoint2.push_back(keypoints2[goodMatches[i].trainIdx]);
		//这两句话的理解：R_keypoint1是要存储img01中能与img02匹配的特征点，
		//matches中存储了这些匹配点对的img01和img02的索引值
	}
	vector<Point2f>p01(goodMatches.size()), p02(goodMatches.size());
	p01.reserve(goodMatches.size());
	p02.reserve(goodMatches.size());

	for (size_t i = 0; i < goodMatches.size(); i++)
	{
		p01[i] = (R_keypoint1[i].pt);
		p02[i] = (R_keypoint2[i].pt);
	}

	vector<uchar> RansacStatus;
	RansacStatus.reserve(1000000);

	Mat Fundamental = findFundamentalMat(p01, p02, RansacStatus, FM_RANSAC);

	vector<KeyPoint> RR_keypoint01, RR_keypoint02;
	RR_keypoint01.reserve(goodMatches.size());
	RR_keypoint02.reserve(goodMatches.size());

	vector<DMatch> MatchePointsAfterRANSAC;
	MatchePointsAfterRANSAC.reserve(goodMatches.size());

	int index = 0;
	for (size_t i = 0; i < goodMatches.size(); i++)
	{
		if (RansacStatus[i] != 0)
		{
			RR_keypoint01.push_back(R_keypoint1[i]);
			RR_keypoint02.push_back(R_keypoint2[i]);
			DMatch buf;
			buf.queryIdx = index;
			buf.trainIdx = index;
			MatchePointsAfterRANSAC.push_back(buf);
			index++;
		}
	}

	Mat picture1KeyPointsResultAfterRANSAC;
	drawKeypoints(img1, RR_keypoint01, picture1KeyPointsResultAfterRANSAC, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	MatToCImage(picture1KeyPointsResultAfterRANSAC, Picture1_KeyPointsSData);
	showPicture1_KeyPointsSData();

	Mat picture2KeyPointsResultAfterRANSAC;
	drawKeypoints(img2, RR_keypoint02, picture2KeyPointsResultAfterRANSAC, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	MatToCImage(picture2KeyPointsResultAfterRANSAC, Picture2_KeyPointsSData);
	showPicture2_KeyPointsSData();

	Mat ResultAfterRANSAC;
	drawMatches(img1, RR_keypoint01, img2, RR_keypoint02, MatchePointsAfterRANSAC, ResultAfterRANSAC);

	MatToCImage(ResultAfterRANSAC, MatchDataS);
	showMatchDataS();

	vector<Point2f> obj, scene;
	for (unsigned int i = 0; i < (int)goodMatches.size(); i++) {
		scene.push_back(keypoints1[goodMatches[i].queryIdx].pt);
		obj.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}

	Mat Homography = findHomography(obj, scene, CV_RANSAC);
	vector<DMatch> match_ransac;

	Mat result;
	warpPerspective(img2, result, Homography, Size(2 * max(GreySourceImage1.cols, GreySourceImage2.cols), GreySourceImage1.rows));
	Mat half(result, cv::Rect(0, 0, GreySourceImage1.cols, GreySourceImage1.rows));
	img1.copyTo(half);
	MatToCImage(result, MosaicPictureData);
	showMasaicPicture();
	waitKey(0);
	//imshow("result", result);

}

//FERNS
void CComputerVisionLabDlg::FERNS()
{
	int i;

	/*输入处理*/
	initModule_nonfree();
	Mat objects, grayOject;
	CImageToMat(Picture1_Data, objects);
	initModule_nonfree();
	Mat scenes, grayScene;
	CImageToMat(Picture2_Data, scenes);

	cvtColor(objects, grayOject, CV_BGR2GRAY);
	cvtColor(scenes, grayScene, CV_BGR2GRAY);

	const char* object_filename = "box.png";
	const char* scene_filename = "box_in_scene.png";



	//Mat object = imread(object_filename, CV_LOAD_IMAGE_GRAYSCALE);
	//Mat scene = imread(scene_filename, CV_LOAD_IMAGE_GRAYSCALE);

	if (!grayOject.data || !grayScene.data)
	{
		fprintf(stderr, "Can not load %s and/or %s\n",
			object_filename, scene_filename);
		system("pause");
		exit(-1);
	}

	double imgscale = 1;
	Mat image;

	resize(grayScene, image, Size(), 1. / imgscale, 1. / imgscale, INTER_CUBIC);

	//cvNamedWindow("Object", 1);
	//cvNamedWindow("Image", 1);
	//cvNamedWindow("Object Correspondence", 1);

	Size patchSize(32, 32);
	LDetector ldetector(7, 20, 2, 2000, patchSize.width, 2);
	ldetector.setVerbose(true);
	PlanarObjectDetector detector;

	vector<Mat> objpyr, imgpyr;
	objpyr.reserve(1000000);
	imgpyr.reserve(1000000);

	int blurKSize = 3;
	double sigma = 0;
	GaussianBlur(grayOject, grayOject, Size(blurKSize, blurKSize), sigma, sigma);
	GaussianBlur(image, image, Size(blurKSize, blurKSize), sigma, sigma);
	buildPyramid(grayOject, objpyr, ldetector.nOctaves - 1);
	buildPyramid(image, imgpyr, ldetector.nOctaves - 1);

	vector<KeyPoint> objKeypoints, SceKeypoints;
	objKeypoints.reserve(1000000);
	SceKeypoints.reserve(1000000);
	PatchGenerator gen(0, 256, 5, true, 0.8, 1.2, -CV_PI / 2, CV_PI / 2, -CV_PI / 2, CV_PI / 2);

	string model_filename = format("%s_model.xml.gz", object_filename);
	printf("Trying to load %s ...\n", model_filename.c_str());
	FileStorage fs(model_filename, FileStorage::READ);
	if (fs.isOpened())
	{
		detector.read(fs.getFirstTopLevelNode());
		printf("Successfully loaded %s.\n", model_filename.c_str());
	}
	else
	{
		printf("The file not found and can not be read. Let's train the model.\n");
		printf("Step 1. Finding the robust keypoints ...\n");
		ldetector.setVerbose(true);
		ldetector.getMostStable2D(grayOject, objKeypoints, 100, gen);
		printf("Done.\nStep 2. Training ferns-based planar object detector ...\n");
		detector.setVerbose(true);

		detector.train(objpyr, objKeypoints, patchSize.width, 100, 11, 10000, ldetector, gen);
		printf("Done.\nStep 3. Saving the model to %s ...\n", model_filename.c_str());
		if (fs.open(model_filename, FileStorage::WRITE))
			detector.write(fs, "ferns_model");
	}
	printf("Now find the keypoints in the image, try recognize them and compute the homography matrix\n");
	fs.release();




	vector<Point2f> dst_corners;
	dst_corners.reserve(1000000);
	Mat correspond(grayOject.rows + image.rows, std::max(grayOject.cols, image.cols), CV_8UC3);
	correspond = Scalar(0.);
	Mat part(correspond, Rect(0, 0, grayOject.cols, grayOject.rows));
	cvtColor(grayOject, part, CV_GRAY2BGR);
	part = Mat(correspond, Rect(0, grayOject.rows, image.cols, image.rows));
	cvtColor(image, part, CV_GRAY2BGR);

	Mat temp(grayOject.rows + image.rows, std::max(grayOject.cols, image.cols), CV_8UC3);
	temp = Scalar(0.);
	Mat part2(temp, Rect(0, 0, grayOject.cols, grayOject.rows));
	cvtColor(grayOject, part2, CV_GRAY2BGR);
	part2 = Mat(temp, Rect(0, grayOject.rows, image.cols, image.rows));
	cvtColor(image, part2, CV_GRAY2BGR);

	vector<int> pairs;
	pairs.reserve(1000000);
	Mat H;

	double t = (double)getTickCount();
	objKeypoints = detector.getModelPoints();
	ldetector(imgpyr, SceKeypoints, 300);

	std::cout << "Object keypoints: " << objKeypoints.size() << "\n";
	std::cout << "Image keypoints: " << SceKeypoints.size() << "\n";

	/*图像拼接
	Mat Descriptors1, Descriptors2;
	FernClassifier fern;
	BFMatcher Matcher;
	vector<DMatch> MatchPoints;
	MatchPoints.reserve(1000000);
	fern.trainFromSingleView(grayOject, objKeypoints);
	Matcher.match(Descriptors1, Descriptors2, MatchPoints);

	Mat MatchResult;
	drawMatches(objects,objKeypoints, scenes,SceKeypoints, MatchPoints, MatchResult);
	MatToCImage(MatchResult, MatchData);
	showMatchData();*/

	bool found = detector(imgpyr, SceKeypoints, H, dst_corners, &pairs);
	t = (double)getTickCount() - t;
	printf("%gms\n", t * 1000 / getTickFrequency());

	if (found)
	{
		for (i = 0; i < 4; i++)
		{
			Point r1 = dst_corners[i % 4];
			Point r2 = dst_corners[(i + 1) % 4];
			line(correspond, Point(r1.x, r1.y + grayOject.rows),
				Point(r2.x, r2.y + grayOject.rows), Scalar(0, 0, 255));
		}

	}

	/*筛选后的匹配连线*/
	for (i = 0; i < (int)pairs.size(); i += 2)
	{
		line(correspond, objKeypoints[pairs[i]].pt,
			SceKeypoints[pairs[i + 1]].pt + Point2f(0, (float)grayOject.rows),
			Scalar(0, 255, 0));
	}

	/*未筛选的匹配连线*/
	int Size = min((int)objKeypoints.size(), (int)SceKeypoints.size());
	for (i = 0; i < Size; ++i)
		line(temp, objKeypoints[i].pt,
			SceKeypoints[i].pt + Point2f(0, (float)grayOject.rows),
			Scalar(0, 255, 0));
	MatToCImage(temp, MatchData);
	showMatchData();

	//imshow("Object Correspondence", correspond);

	/*图像1的筛选后的特征点画圈*/
	Mat object2;
	cvtColor(grayOject, object2, CV_GRAY2BGR);
	for (i = 0; i < (int)pairs.size(); i += 2)
	{
		circle(object2, objKeypoints[pairs[i]].pt, 2, Scalar(0, 0, 255), -1);
		circle(object2, objKeypoints[pairs[i]].pt, (1 << objKeypoints[pairs[i]].octave) * 15, Scalar(0, 255, 0), 1);
	}
	MatToCImage(object2, Picture1_KeyPointsSData);
	showPicture1_KeyPointsSData();

	/*图像2的筛选后的特征点画圈*/
	Mat image2;
	cvtColor(image, image2, CV_GRAY2BGR);
	for (i = 0; i < (int)pairs.size(); i += 2)
	{
		circle(image2, SceKeypoints[pairs[i + 1]].pt, 2, Scalar(0, 0, 255), -1);
		circle(image2, SceKeypoints[pairs[i + 1]].pt, (1 << SceKeypoints[pairs[i + 1]].octave) * 15, Scalar(0, 255, 0), 1);
	}
	MatToCImage(image2, Picture2_KeyPointsSData);
	showPicture2_KeyPointsSData();

	/*图像1的未筛选的特征点画圈*/
	Mat objectColor;
	cvtColor(grayOject, objectColor, CV_GRAY2BGR);
	for (i = 0; i < (int)objKeypoints.size(); i++)
	{
		circle(objectColor, objKeypoints[i].pt, 2, Scalar(0, 0, 255), -1);
		circle(objectColor, objKeypoints[i].pt, (1 << objKeypoints[i].octave) * 15, Scalar(0, 255, 0), 1);
	}

	/*图像2的未筛选的特征点画圈*/
	Mat imageColor;
	cvtColor(image, imageColor, CV_GRAY2BGR);
	for (i = 0; i < (int)SceKeypoints.size(); i++)
	{
		circle(imageColor, SceKeypoints[i].pt, 2, Scalar(0, 0, 255), -1);
		circle(imageColor, SceKeypoints[i].pt, (1 << SceKeypoints[i].octave) * 15, Scalar(0, 255, 0), 1);
	}
	MatToCImage(objectColor, Picture1_KeyPointsData);
	showPicture1_KeyPointsData();//
	MatToCImage(imageColor, Picture2_KeyPointsData);
	showPicture2_KeyPointsData();//
	MatToCImage(correspond, MatchDataS);
	showMatchDataS();///筛选后的匹配结果
	//imwrite("correspond.png", correspond);
	//imshow("Object", objectColor);
	//imshow("Image", imageColor);
}

//使用FERNS进行图像拼接
void CComputerVisionLabDlg::FERNSMosaic() {}

/**********************图像显示接口**********************/
void CComputerVisionLabDlg::showImageToUI(CStatic &Area, CImage &Data)
{
	if (Data != NULL)
	{
		int height;
		int width;

		CRect WorkSpaceRect;
		CRect ShowImageRect;

		//记录图片本身的长和宽
		height = Data.GetHeight();
		width = Data.GetWidth();

		Area.GetClientRect(&WorkSpaceRect); //根据GUI中的工作区生成一个矩形对象，左上角为（0，0）
		CDC *pDC = Area.GetDC();	//设备上下文（Device Contex）->指向图片数据？
		SetStretchBltMode(pDC->m_hDC, STRETCH_HALFTONE);//设置图片拉伸的模式，设置为HalfTone，这个模式下，应用程序必须调用Win32函数 SetBrushOrgEx 设置画笔原点

		if (width <= WorkSpaceRect.Width() && height <= WorkSpaceRect.Width()) //图片完全可以在工作区中以原来的大小放下
		{
			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize(width, height)); //创建另一个矩形，左上角点和工作区一致，使用CSize传入矩形大小
			Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		else //图片在工作区中不能以原来的大小放下
		{
			float xScale = (float)WorkSpaceRect.Width() / (float)width; //记录原工作区矩形和图片的长度比例
			float yScale = (float)WorkSpaceRect.Height() / (float)height; //记录原工作区矩形和图片的宽度比例
			float ScaleIndex = (xScale <= yScale ? xScale : yScale); //选出较小的比例

			ShowImageRect = CRect(WorkSpaceRect.TopLeft(), CSize((int)width*ScaleIndex, (int)height*ScaleIndex)); //创建一个由原图片按照刚刚获取的较小的比例缩放的，保证能整个放入工作区的矩形
			Data.StretchBlt(pDC->m_hDC, ShowImageRect, SRCCOPY);//使用SRCCOPY直接将原图片数据传递至展示图片的矩形（ShowImageRect）
		}
		ReleaseDC(pDC); //将上下文释放
	}
}

//更新图片1结果区域的内容
void CComputerVisionLabDlg::showPicture1_KeyPointsData()
{
	showImageToUI(Picture1KeyPointsArea, Picture1_KeyPointsData);
}

//更新图片2特征点区域的内容
void CComputerVisionLabDlg::showPicture2_KeyPointsData()
{
	showImageToUI(Picture2KeyPointsArea, Picture2_KeyPointsData);
}

//更新图片1筛选后的特征点区域的内容
void CComputerVisionLabDlg::showPicture1_KeyPointsSData()
{
	showImageToUI(Picture1KeyPointsSArea, Picture1_KeyPointsSData);
}

//更新图片2筛选后的特征点区域的内容
void CComputerVisionLabDlg::showPicture2_KeyPointsSData()
{
	showImageToUI(Picture2KeyPointsSArea, Picture2_KeyPointsSData);
}

//更新图片拼接结果区域内容
void CComputerVisionLabDlg::showMasaicPicture()
{
	showImageToUI(MosaicPictureArea, MosaicPictureData);
}

//更新原始特征点匹配结果区域内容
void CComputerVisionLabDlg::showMatchData()
{
	showImageToUI(MatchResultArea, MatchData);
}

//更新经过筛选的特征点匹配的结果
void CComputerVisionLabDlg::showMatchDataS()
{
	showImageToUI(MatchResultSArea, MatchDataS);
}
