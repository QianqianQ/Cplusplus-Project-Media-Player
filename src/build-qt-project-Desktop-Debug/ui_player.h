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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Player
{
public:
    QAction *actionOpen;
    QAction *actionPlay;
    QAction *actionStop;
    QAction *actionPause;
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSlider *Progress;
    QPushButton *Pause;
    QPushButton *Play;
    QPushButton *Stop;
    QVBoxLayout *verticalLayout;
    QSlider *Volume;
    QLabel *volumeLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Player)
    {
        if (Player->objectName().isEmpty())
            Player->setObjectName(QString::fromUtf8("Player"));
        Player->resize(364, 362);
        actionOpen = new QAction(Player);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionPlay = new QAction(Player);
        actionPlay->setObjectName(QString::fromUtf8("actionPlay"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay->setIcon(icon1);
        actionStop = new QAction(Player);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon2);
        actionPause = new QAction(Player);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon3);
        centralWidget = new QWidget(Player);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 210, 331, 72));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Progress = new QSlider(widget);
        Progress->setObjectName(QString::fromUtf8("Progress"));
        Progress->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Progress, 0, 0, 1, 4);

        Pause = new QPushButton(widget);
        Pause->setObjectName(QString::fromUtf8("Pause"));
        Pause->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(Pause, 1, 0, 1, 1);

        Play = new QPushButton(widget);
        Play->setObjectName(QString::fromUtf8("Play"));
        Play->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(Play, 1, 1, 1, 1);

        Stop = new QPushButton(widget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(Stop, 1, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Volume = new QSlider(widget);
        Volume->setObjectName(QString::fromUtf8("Volume"));
        Volume->setValue(50);
        Volume->setSliderPosition(50);
        Volume->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(Volume);

        volumeLabel = new QLabel(widget);
        volumeLabel->setObjectName(QString::fromUtf8("volumeLabel"));
        volumeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(volumeLabel);


        gridLayout->addLayout(verticalLayout, 1, 3, 1, 1);

        Player->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Player);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 364, 23));
        Player->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Player);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Player->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Player);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy);
        Player->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpen);

        retranslateUi(Player);

        QMetaObject::connectSlotsByName(Player);
    } // setupUi

    void retranslateUi(QMainWindow *Player)
    {
        Player->setWindowTitle(QApplication::translate("Player", "Media Player", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("Player", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("Player", "Open an audio file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPlay->setText(QApplication::translate("Player", "Play", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate("Player", "Play music", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionStop->setText(QApplication::translate("Player", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStop->setToolTip(QApplication::translate("Player", "Stop music", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPause->setText(QApplication::translate("Player", "Pause", 0, QApplication::UnicodeUTF8));
        Pause->setText(QApplication::translate("Player", "Pause", 0, QApplication::UnicodeUTF8));
        Play->setText(QApplication::translate("Player", "Play", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("Player", "Stop", 0, QApplication::UnicodeUTF8));
        volumeLabel->setText(QApplication::translate("Player", "Volume", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Player: public Ui_Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
