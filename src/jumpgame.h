#ifndef JUMPGAME_H
#define JUMPGAME_H

#include <QtWidgets/QMainWindow>
#include "ui_jumpgame.h"
#include "CJumpManger.h"
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include <memory>


using namespace std;
class jumpgame : public QMainWindow
{
	Q_OBJECT

public:
	jumpgame(QWidget *parent = 0);
	~jumpgame();
	void setWindow();
	//修改时间因素
	void modTimeFactor();
	//修改起始点识别阈值
	void modSrcRecGate();
	//获取时间
	void getTime();
	//初始化参数
	void initInfo();
	//保存参数
	void saveInfo();
	//修改调试模式
	void changeMod();
	//修改休息时间
	void setRestTime();
	//分割
	void split(const char* srclist, const char spl, vector<string> &vecDes);
	//运行
	void workStart();
	//停止
	void workStop();
	//主线程
	void workThread();

private:
	Ui::jumpgameClass ui;
	int m_iDeline;
	int m_iStep;
	int m_ignoreLine;
	int m_iSrcGate;
	int xTop;
	int yTop;
	int xBottom;
	int yBottom;
	int m_iSleepTime;
	bool m_workFlag;
	CJumpManger* jumpManger;
	std::thread* m_tid;

	//设置窗体大小
	QHBoxLayout* m_layoutWinPos;
	QLabel* m_labelWinPos[4];
	QLineEdit* m_editWinPos[4];
	QPushButton* m_buttonWinPos;
	//设置步长
	QLineEdit* m_editStep;
	QLabel* m_labelStep;
	//设置阈值变化
	QHBoxLayout* m_layoutGate;
	QLineEdit* m_editGate;
	QPushButton* m_buttonGate;
	QPushButton* m_buttonGateAdd;
	QPushButton* m_buttonGateReduce;
	//设置时间因子
	QLayout* m_layoutFactor;
	QLineEdit* m_editFactor;
	QPushButton* m_buttonFactor;
	QPushButton* m_buttonFactorAdd;
	QPushButton* m_buttonFactorReduce;

	//游戏速度
	QLayout* m_layoutSpeed;
	QLineEdit* m_editSpeed;
	QPushButton* m_buttonSpeed;
	QPushButton* m_buttonSpeedAdd;
	QPushButton* m_buttonSpeedReduce;
	//调试按钮
	QLayout* m_layoutControl;
	QPushButton* m_buttonDebug;
	QPushButton* m_buttonStart;
	QPushButton* m_buttonStop;

	//主窗口布局
	QVBoxLayout* mainLayout;
	//按键布局
	QVBoxLayout* m_layoutOption;
	//参数布局
	QVBoxLayout* m_layoutParam;
	//内容布局
	QHBoxLayout* m_layoutContent;
};

#endif // JUMPGAME_H
