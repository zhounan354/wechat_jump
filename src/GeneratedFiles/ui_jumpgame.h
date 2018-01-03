/********************************************************************************
** Form generated from reading UI file 'jumpgame.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JUMPGAME_H
#define UI_JUMPGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jumpgameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *jumpgameClass)
    {
        if (jumpgameClass->objectName().isEmpty())
            jumpgameClass->setObjectName(QStringLiteral("jumpgameClass"));
        jumpgameClass->resize(600, 400);
        menuBar = new QMenuBar(jumpgameClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        jumpgameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(jumpgameClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        jumpgameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(jumpgameClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        jumpgameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(jumpgameClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        jumpgameClass->setStatusBar(statusBar);

        retranslateUi(jumpgameClass);

        QMetaObject::connectSlotsByName(jumpgameClass);
    } // setupUi

    void retranslateUi(QMainWindow *jumpgameClass)
    {
        jumpgameClass->setWindowTitle(QApplication::translate("jumpgameClass", "jumpgame", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class jumpgameClass: public Ui_jumpgameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JUMPGAME_H
