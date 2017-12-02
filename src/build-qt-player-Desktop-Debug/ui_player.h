/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_player
{
public:
    QWidget *centralWidget;
    QPushButton *play;
    QPushButton *pause;
    QPushButton *stop;
    QSlider *volume;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *player)
    {
        if (player->objectName().isEmpty())
            player->setObjectName(QString::fromUtf8("player"));
        player->resize(400, 300);
        centralWidget = new QWidget(player);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        play = new QPushButton(centralWidget);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(30, 40, 75, 23));
        pause = new QPushButton(centralWidget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setGeometry(QRect(140, 40, 75, 23));
        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(260, 40, 75, 23));
        volume = new QSlider(centralWidget);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setGeometry(QRect(110, 100, 160, 22));
        volume->setMinimum(20);
        volume->setValue(60);
        volume->setSliderPosition(60);
        volume->setOrientation(Qt::Horizontal);
        player->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(player);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        player->setMenuBar(menuBar);
        mainToolBar = new QToolBar(player);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        player->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(player);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        player->setStatusBar(statusBar);

        retranslateUi(player);

        QMetaObject::connectSlotsByName(player);
    } // setupUi

    void retranslateUi(QMainWindow *player)
    {
        player->setWindowTitle(QApplication::translate("player", "Media Player", 0, QApplication::UnicodeUTF8));
        play->setText(QApplication::translate("player", "Play", 0, QApplication::UnicodeUTF8));
        pause->setText(QApplication::translate("player", "Pause", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("player", "Stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class player: public Ui_player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
