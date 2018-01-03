#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <windows.h>

using cv::Mat;
using cv::VideoCapture;


class CJumpManger
{
public:
	CJumpManger();
	~CJumpManger();
	Mat imgGray;
	Mat imgTemp;
	Mat imgCircle;
	VideoCapture videoCapture;
	void Reline(int iDeline);
	void GetPic();
	int RecMe();
	int RecDest();
	void ChangeDebugMode();
	bool GetDegubMode(){ return debugFlag; };
	int SetTime();
	void setPicWindow(int xTop, int yTop, int xBottom, int yBottom);
	void setFactor(int iFactor);
	void setIgnoreLine(int iLine);
	void setSrcGate(int iGate);
	void screen(char* fileName);
	//判断获取的点是否有效
	//int isCatch(std::vector<Point> vecP);

	//调试标识
	bool debugFlag;
	int iDesHPoint;
	int iHCenter;
	int m_iSrcGate;
	int m_iIgnoreLine;
	int m_iFactor;

	int m_xTop;
	int m_yTop;
	int m_xBot;
	int m_yBot;

};

