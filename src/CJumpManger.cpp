#include "CJumpManger.h"

using namespace cv;

CJumpManger::CJumpManger()
{
	/*Mat imgIn = imread("test1.jpg");
	Mat imgResize;
	debugFlag = true;
	m_iIgnoreLine = 0;

	resize(imgIn, imgResize, Size(imgIn.cols / 2, imgIn.rows / 2));
	cvtColor(imgResize, imgGray, CV_BGR2GRAY);*/
	//line(imgGray, Point(0, imgGray.rows / 2), Point(imgGray.cols, imgGray.rows / 2), Scalar(0, 0, 0));
	//line(imgGray, Point(imgGray.cols / 2, 0), Point(imgGray.cols / 2, imgGray.rows), Scalar(0, 0, 0));
	//imgGray.copyTo(imgTemp);
	namedWindow("图像");
	namedWindow("我在这");
	namedWindow("要去这");
}

CJumpManger::~CJumpManger()
{
}

void CJumpManger::Reline(int iDeline)
{
	imgGray.copyTo(imgTemp);
	if (iDeline > imgTemp.cols / 2 || iDeline < 0)
	{
		return;
	}
	line(imgTemp, Point(imgTemp.cols / 2 + iDeline, 0), Point(imgTemp.cols / 2 + iDeline, imgTemp.rows), Scalar(0, 0, 0));
	line(imgTemp, Point(imgTemp.cols / 2 - iDeline, 0), Point(imgTemp.cols / 2 - iDeline, imgTemp.rows), Scalar(0, 0, 0));
	imshow("图像", imgTemp);
}

void CJumpManger::GetPic()
{
	screen("1.bmp");
	Mat imgScreen;
	Mat imgIn;
	imgScreen = imread("1.bmp");
	imgIn = imgScreen(Range(m_yTop, m_yBot), Range(m_xTop, m_xBot));
	if (!imgIn.data)
		return;
	//imgIn = imread("sec2.png");
	//resize(imgIn, imgIn, Size(imgIn.cols / 2,imgIn.rows / 2));


	cvtColor(imgIn, imgGray, CV_BGR2GRAY);

	imgGray.copyTo(imgTemp);
	if (debugFlag)
	{
		imshow("图像", imgTemp);
		waitKey(10);
	}
		
}

int CJumpManger::RecMe()
{
	imgGray.copyTo(imgTemp);
	iHCenter = 0;
	//imshow("test", imgTemp);
	threshold(imgTemp, imgTemp, m_iSrcGate, 255, THRESH_BINARY);
	//腐蚀
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
	erode(imgTemp, imgTemp, element);
	dilate(imgTemp, imgTemp, element);
	dilate(imgTemp, imgTemp, element);
	//imshow("Src", imgTemp);
	//waitKey(10);

	int iNum=0;
	int iSum=0;
	for (int i = 0; i < imgTemp.rows; i++)
		for (int j = 0; j < imgTemp.cols; j++)
		{
			if (imgTemp.data[i*imgTemp.cols + j] == 0)
			{
				iNum++;
				iSum += j;
			}
		}
	if (iNum < 1)
		return 0;
	iHCenter = iSum / iNum;
	//std::cout << imgTemp.cols<<" "<<iHCenter<<std::endl;
	if (debugFlag)
	{
		line(imgTemp, Point(iHCenter, 0), Point(iHCenter, imgTemp.rows),0);
		imshow("我在这", imgTemp);
		waitKey(10);
		//getchar();
	}
	return iHCenter;
}

int CJumpManger::RecDest()
{
	imgGray.copyTo(imgTemp);
	//imshow("test", imgTemp);

	threshold(imgTemp, imgTemp, m_iSrcGate, 255, THRESH_BINARY_INV);
	//腐蚀
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));

	dilate(imgTemp, imgTemp, element);
	dilate(imgTemp, imgTemp, element);

	imgTemp = imgGray - imgTemp;
	if (debugFlag)
	{
		imshow("要去这", imgTemp);
		waitKey(10);
		//std::cout << iDesHPoint << std::endl;
		//getchar();
	}


	int iBackground;
	iDesHPoint = 0;
	int iDesVPoint = 0;
	std::vector<int> vecPoint;
	for (int i = 3; i < imgTemp.rows; i++)
	{
		iBackground = imgTemp.data[i*imgTemp.cols+30];
		vecPoint.clear();
		for (int j = 30; j < imgTemp.cols; j++)
		{
			
			int iTemp = imgTemp.data[i*imgTemp.cols + j];
			if (0 == iTemp)
				continue;
			if (iTemp - iBackground >= 3 || iTemp - iBackground <= -3)
			{
				vecPoint.push_back(j);
				iDesVPoint = i;
			}
		}
		if (vecPoint.size() >= 40)
			break;
		
	}
	if (vecPoint.size() == 0)
	{
		std::cout << "error\n";
		getchar();
		return 0;
	}	
	int sum = 0;
	for (int i = 0; i < vecPoint.size(); i++)
		sum += vecPoint[i];

	iDesHPoint = sum / vecPoint.size();

	if (debugFlag)
	{
		line(imgTemp, Point(0, iDesVPoint), Point(imgTemp.cols, iDesVPoint), 0);
		line(imgTemp, Point(iDesHPoint, 0), Point(iDesHPoint, imgTemp.rows), 0);
		imshow("要去这", imgTemp);
		waitKey(10);
		//std::cout << iDesHPoint << std::endl;
		//getchar();
	}
	return iDesHPoint;
}

int CJumpManger::SetTime()
{
	GetPic();
	RecMe();
	RecDest();
	if (iDesHPoint == 0)
		return 0;
	double iRange;
	iRange = iDesHPoint >= iHCenter ? iDesHPoint - iHCenter : iHCenter - iDesHPoint;
	int iTime = iRange / imgTemp.cols * m_iFactor*10;
	//单位 0.001 秒
	std::cout << iTime << std::endl;
	return iTime;
}

void CJumpManger::setFactor(int iFactor)
{
	m_iFactor = iFactor;
}

void CJumpManger::setIgnoreLine(int iLine)
{
	m_iIgnoreLine = iLine;
}

void CJumpManger::setSrcGate(int iGate)
{
	m_iSrcGate = iGate;
}

void CJumpManger::setPicWindow(int xTop, int yTop, int xBottom, int yBottom)
{
	m_xTop = xTop;
	m_yTop = yTop;
	m_xBot = xBottom;
	m_yBot = yBottom;
}

void CJumpManger::ChangeDebugMode()
{
	debugFlag = !debugFlag;
	if (debugFlag)
	{
		namedWindow("图像");
		namedWindow("我在这");
		namedWindow("要去这");
	}
	else
		destroyAllWindows();
}

void CJumpManger::screen(char* fileName)
{
	HWND window = GetDesktopWindow();
	HDC _dc = GetWindowDC(window);
	HDC dc = CreateCompatibleDC(0);

	RECT re;
	GetWindowRect(window, &re);
	int w = re.right,
		h = re.bottom;
	void* buf = new char[w*h * 4];

	HBITMAP bm = CreateCompatibleBitmap(_dc, w, h);
	SelectObject(dc, bm);

	StretchBlt(dc, 0, 0, w, h, _dc, 0, 0, w, h, SRCCOPY);

	void* f = CreateFileA(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	GetObject(bm, 84, buf);

	tagBITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = w;
	bi.bmiHeader.biHeight = h;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = 0;
	bi.bmiHeader.biSizeImage = 0;

	CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &buf, 0, 0);
	GetDIBits(dc, bm, 0, h, buf, &bi, DIB_RGB_COLORS);

	BITMAPFILEHEADER bif;
	bif.bfType = MAKEWORD('B', 'M');
	bif.bfSize = w*h * 4 + 54;
	bif.bfOffBits = 54;

	BITMAPINFOHEADER bii;
	bii.biSize = 40;
	bii.biWidth = w;
	bii.biHeight = h;
	bii.biPlanes = 1;
	bii.biBitCount = 32;
	bii.biCompression = 0;
	bii.biSizeImage = w*h * 4;

	DWORD r;
	WriteFile(f, &bif, sizeof(bif), &r, NULL);
	WriteFile(f, &bii, sizeof(bii), &r, NULL);
	WriteFile(f, buf, w*h * 4, &r, NULL);

	CloseHandle(f);
	DeleteDC(_dc);
	DeleteDC(dc);
}


