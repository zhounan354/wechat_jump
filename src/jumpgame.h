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
	//�޸�ʱ������
	void modTimeFactor();
	//�޸���ʼ��ʶ����ֵ
	void modSrcRecGate();
	//��ȡʱ��
	void getTime();
	//��ʼ������
	void initInfo();
	//�������
	void saveInfo();
	//�޸ĵ���ģʽ
	void changeMod();
	//�޸���Ϣʱ��
	void setRestTime();
	//�ָ�
	void split(const char* srclist, const char spl, vector<string> &vecDes);
	//����
	void workStart();
	//ֹͣ
	void workStop();
	//���߳�
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

	//���ô����С
	QHBoxLayout* m_layoutWinPos;
	QLabel* m_labelWinPos[4];
	QLineEdit* m_editWinPos[4];
	QPushButton* m_buttonWinPos;
	//���ò���
	QLineEdit* m_editStep;
	QLabel* m_labelStep;
	//������ֵ�仯
	QHBoxLayout* m_layoutGate;
	QLineEdit* m_editGate;
	QPushButton* m_buttonGate;
	QPushButton* m_buttonGateAdd;
	QPushButton* m_buttonGateReduce;
	//����ʱ������
	QLayout* m_layoutFactor;
	QLineEdit* m_editFactor;
	QPushButton* m_buttonFactor;
	QPushButton* m_buttonFactorAdd;
	QPushButton* m_buttonFactorReduce;

	//��Ϸ�ٶ�
	QLayout* m_layoutSpeed;
	QLineEdit* m_editSpeed;
	QPushButton* m_buttonSpeed;
	QPushButton* m_buttonSpeedAdd;
	QPushButton* m_buttonSpeedReduce;
	//���԰�ť
	QLayout* m_layoutControl;
	QPushButton* m_buttonDebug;
	QPushButton* m_buttonStart;
	QPushButton* m_buttonStop;

	//�����ڲ���
	QVBoxLayout* mainLayout;
	//��������
	QVBoxLayout* m_layoutOption;
	//��������
	QVBoxLayout* m_layoutParam;
	//���ݲ���
	QHBoxLayout* m_layoutContent;
};

#endif // JUMPGAME_H
