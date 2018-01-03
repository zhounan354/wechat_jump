#include "jumpgame.h"

jumpgame::jumpgame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(QSize(300, 200));
	QSize szMin(20, 20);
	QSize szMid(60, 25);
	ui.mainToolBar->setVisible(false);
	setWindowIcon(QIcon(":/jumpgame/jump"));
	setWindowTitle("jump");

	m_layoutOption = new QVBoxLayout();
	m_layoutParam = new QVBoxLayout();
	//窗体设置
	m_layoutWinPos = new QHBoxLayout();
	m_buttonWinPos = new QPushButton(QStringLiteral("设置窗体"));
	m_buttonWinPos->setFixedSize(szMid);
	for (int i = 0; i < 4; i++)
	{
		m_labelWinPos[i] = new QLabel();
		m_editWinPos[i] = new QLineEdit();
		m_layoutWinPos->addWidget(m_labelWinPos[i]);
		m_layoutWinPos->addWidget(m_editWinPos[i]);
	}
	m_labelWinPos[0]->setText("L-x:");
	m_labelWinPos[1]->setText("L-y:");
	m_labelWinPos[2]->setText("R-x:");
	m_labelWinPos[3]->setText("R-y:");

	m_layoutOption->addWidget(m_buttonWinPos);
	m_layoutParam->addItem(m_layoutWinPos);
	//步长设置
	m_editStep = new QLineEdit();
	m_editStep->setMaximumWidth(100);
	m_labelStep = new QLabel(QStringLiteral("设置步长"));
	
	//阈值变化设置
	m_layoutGate = new QHBoxLayout();
	m_editGate = new QLineEdit();
	m_buttonGate = new QPushButton(QStringLiteral("设置阈值"));
	m_buttonGate->setFixedSize(szMid);
	m_buttonGateAdd = new QPushButton("+");
	m_buttonGateReduce = new QPushButton("-");
	m_buttonGateReduce->setFixedSize(szMin);
	m_buttonGateAdd->setFixedSize(szMin);

	m_layoutOption->addWidget(m_buttonGate);
	m_layoutGate->addWidget(m_buttonGateAdd);
	m_layoutGate->addWidget(m_buttonGateReduce);
	m_layoutGate->addWidget(m_editGate);

	m_layoutGate->addWidget(m_labelStep);
	m_layoutGate->addWidget(m_editStep);

	m_layoutParam->addItem(m_layoutGate);
	//设置时间因子
	m_layoutFactor = new QHBoxLayout();
	m_editFactor = new QLineEdit();
	m_buttonFactor = new QPushButton(QStringLiteral("设置距离"));
	m_buttonFactor->setFixedSize(szMid);
	m_buttonFactorAdd = new QPushButton("+");
	m_buttonFactorReduce = new QPushButton("-");
	m_buttonFactorReduce->setFixedSize(szMin);
	m_buttonFactorAdd->setFixedSize(szMin);

	m_layoutOption->addWidget(m_buttonFactor);
	m_layoutFactor->addWidget(m_buttonFactorAdd);
	m_layoutFactor->addWidget(m_buttonFactorReduce);
	m_layoutFactor->addWidget(m_editFactor);
	m_layoutParam->addItem(m_layoutFactor);
	//设置游戏速度
	m_layoutSpeed = new QHBoxLayout();
	m_editSpeed = new QLineEdit();
	m_buttonSpeed = new QPushButton(QStringLiteral("设置速度"));
	m_buttonSpeed->setFixedSize(szMid);
	m_buttonSpeedAdd = new QPushButton("+");
	m_buttonSpeedReduce = new QPushButton("-");
	m_buttonSpeedReduce->setFixedSize(szMin);
	m_buttonSpeedAdd->setFixedSize(szMin);

	m_layoutOption->addWidget(m_buttonSpeed);
	m_layoutSpeed->addWidget(m_buttonSpeedAdd);
	m_layoutSpeed->addWidget(m_buttonSpeedReduce);
	m_layoutSpeed->addWidget(m_editSpeed);
	m_layoutParam->addItem(m_layoutSpeed);
	//控制按钮
	m_layoutControl = new QHBoxLayout();
	m_buttonStart = new QPushButton(QStringLiteral("开始"));
	m_buttonStop = new QPushButton(QStringLiteral("停止"));
	m_buttonDebug = new QPushButton(QStringLiteral("调试"));
	m_buttonStart->setFixedSize(QSize(60, 30));
	m_buttonStop->setFixedSize(QSize(60, 30));
	m_buttonDebug->setFixedSize(QSize(60, 30));

	m_layoutControl->addWidget(m_buttonStart);
	m_layoutControl->addWidget(m_buttonStop);
	m_layoutControl->addWidget(m_buttonDebug);

	//主布局
	m_layoutContent = new QHBoxLayout();
	m_layoutContent->addItem(m_layoutOption);
	m_layoutContent->addItem(m_layoutParam);

	mainLayout = new QVBoxLayout();
	mainLayout->addItem(m_layoutContent);
	mainLayout->addItem(m_layoutControl);
	ui.centralWidget->setLayout(mainLayout);

	m_layoutOption->setMargin(10);
	m_layoutOption->setSpacing(10);

	m_layoutParam->setMargin(10);
	m_layoutContent->setMargin(10);
	m_layoutParam->setSpacing(10);

	jumpManger = new CJumpManger();

	initInfo();

	connect(m_buttonWinPos, &QPushButton::clicked, this, &jumpgame::setWindow);
	connect(m_buttonDebug, &QPushButton::clicked, this, &jumpgame::changeMod);
	connect(m_buttonFactor, &QPushButton::clicked, this, &jumpgame::modTimeFactor);
	connect(m_buttonFactorAdd, &QPushButton::clicked, this, [this]{
		int iFactor = m_editFactor->text().toInt();
		iFactor++;
		m_editFactor->setText(QString("%1").arg(iFactor));
		modTimeFactor();
	});
	connect(m_buttonFactorReduce, &QPushButton::clicked, this, [this]{
		int iFactor = m_editFactor->text().toInt();
		iFactor--;
		m_editFactor->setText(QString("%1").arg(iFactor));
		modTimeFactor();
	});
	connect(m_buttonGate, &QPushButton::clicked, this, &jumpgame::modSrcRecGate);
	connect(m_buttonGateAdd, &QPushButton::clicked, this, [this]{
		m_iStep = m_editStep->text().toInt();
		int iGate = m_editGate->text().toInt();
		iGate += m_iStep;
		m_editGate->setText(QString("%1").arg(iGate));
		modSrcRecGate();
	});
	connect(m_buttonGateReduce, &QPushButton::clicked, this, [this]{
		m_iStep = m_editStep->text().toInt();
		int iGate = m_editGate->text().toInt();
		iGate -= m_iStep;
		m_editGate->setText(QString("%1").arg(iGate));
		modSrcRecGate();
	});
	connect(m_buttonSpeed, &QPushButton::clicked, this, &jumpgame::setRestTime);
	connect(m_buttonSpeedAdd, &QPushButton::clicked, this, [this]{
		int iSleepTime = m_editSpeed->text().toInt();
		iSleepTime++;
		m_editSpeed->setText(QString("%1").arg(iSleepTime));
		setRestTime();
	});
	connect(m_buttonSpeedReduce, &QPushButton::clicked, this, [this]{
		int iSleepTime = m_editSpeed->text().toInt();
		iSleepTime--;
		m_editSpeed->setText(QString("%1").arg(iSleepTime));
		setRestTime();
	});
	connect(m_buttonStart, &QPushButton::clicked, this, &jumpgame::workStart);
	connect(m_buttonStop, &QPushButton::clicked, this, &jumpgame::workStop);
}

jumpgame::~jumpgame()
{

}

void jumpgame::getTime()
{
	jumpManger->SetTime();
}

void jumpgame::setWindow()
{
	xTop = m_editWinPos[0]->text().toInt();
	yTop = m_editWinPos[1]->text().toInt();
	xBottom = m_editWinPos[2]->text().toInt();
	yBottom = m_editWinPos[3]->text().toInt();

	jumpManger->setPicWindow(xTop, yTop, xBottom, yBottom);
	saveInfo();

}

void jumpgame::initInfo()
{
	//初始状态不运行
	m_workFlag = true;

	fstream file;
	string strTemp;
	file.open("para.ini");
	while (!file.is_open())
	{
		file.open("para.ini", ios::out);
		file << "20 150 300 400 52 5 157 34" << endl;
		file.close();
		file.open("para.ini");
	}
	vector<string> vecParam;
	getline(file, strTemp);
	split(strTemp.c_str(), ' ', vecParam);

	m_editWinPos[0]->setText(vecParam[0].c_str());
	m_editWinPos[1]->setText(vecParam[1].c_str());
	m_editWinPos[2]->setText(vecParam[2].c_str());
	m_editWinPos[3]->setText(vecParam[3].c_str());
	m_editGate->setText(vecParam[4].c_str());
	m_editStep->setText(vecParam[5].c_str());
	m_editFactor->setText(vecParam[6].c_str());
	m_editSpeed->setText(vecParam[7].c_str());
	file.close();

	m_iSleepTime = m_editSpeed->text().toInt();
	m_iStep = m_editStep->text().toInt();
	
	setWindow();
	setRestTime();
	modSrcRecGate();
	modTimeFactor();
}

void jumpgame::saveInfo()
{
	vector<string> vecParam;
	vecParam.push_back(m_editWinPos[0]->text().toStdString());
	vecParam.push_back(m_editWinPos[1]->text().toStdString());
	vecParam.push_back(m_editWinPos[2]->text().toStdString());
	vecParam.push_back(m_editWinPos[3]->text().toStdString());
	vecParam.push_back(m_editGate->text().toStdString());
	vecParam.push_back(m_editStep->text().toStdString());
	vecParam.push_back(m_editFactor->text().toStdString());
	vecParam.push_back(m_editSpeed->text().toStdString());

	fstream file;
	file.open("para.ini", ios::out);
	for (int i = 0; i < vecParam.size(); i++)
	{
		file << vecParam[i] << " ";
	}
	file << endl;
	file.close();
}

void  jumpgame::split(const char* srclist, const char spl, vector<string> &vecDes)
{
	int p = 0;
	int q = 0;
	char id[300] = { 0 };
	string strTemp;
	if (strlen(srclist) == 0)
	{
		//	printf("functionlist is empty!\n");
		vecDes.push_back("");
		return;
	}
	while (srclist[p] != '\0')
	{
		if (srclist[p] != spl)
		{
			id[q] = srclist[p];
			q++;
		}
		else
		{
			id[q] = '\0';
			q = 0;
			strTemp = id;
			vecDes.push_back(strTemp);
		}
		p++;
	}
	if (q != 0)
	{
		id[q] = '\0';
		strTemp = id;
		vecDes.push_back(strTemp);
	}
}

void jumpgame::changeMod()
{
	jumpManger->ChangeDebugMode();
	if (jumpManger->GetDegubMode())
		m_buttonDebug->setText(QStringLiteral("调试"));
	else
		m_buttonDebug->setText("go");
}

void jumpgame::modTimeFactor()
{
	int iFactor = m_editFactor->text().toInt();
	jumpManger->setFactor(iFactor);
	saveInfo();
}

void jumpgame::modSrcRecGate()
{
	int iGate = m_editGate->text().toInt();
	jumpManger->setSrcGate(iGate);
	saveInfo();
}

void jumpgame::setRestTime()
{
	m_iSleepTime = m_editSpeed->text().toInt();
	saveInfo();
}

void jumpgame::workThread()
{
	int iClickTime;
	POINT pt1;
	POINT pt2;

	

	while (true)
	{
		pt1.x = xTop / 2 + xBottom / 2;
		pt1.y = yTop / 2 + yBottom / 2;
		iClickTime = jumpManger->SetTime();

		if (iClickTime ==0)
			continue;
		//cout << "test" << endl;
		GetCursorPos(&pt2);
		ShowCursor(false);
		SetCursorPos(pt1.x, pt1.y);
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, 200, 500, 0, 0);
		SetCursorPos(pt2.x, pt2.y);
		ShowCursor(true);

		Sleep(iClickTime);

		GetCursorPos(&pt2);
		ShowCursor(false);
		SetCursorPos(pt1.x, pt1.y);
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, 200, 500, 0, 0);
		SetCursorPos(pt2.x, pt2.y);
		ShowCursor(true);

		Sleep(m_iSleepTime*100);
		if (!m_workFlag)
			return;
	}
}

void jumpgame::workStart()
{
	m_workFlag = true;
	m_tid = new std::thread(&jumpgame::workThread, this);
	//m_tid->join();
}

void jumpgame::workStop()
{
	m_workFlag = false;
}




