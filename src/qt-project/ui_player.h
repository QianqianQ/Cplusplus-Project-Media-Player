/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            Player->setObjectName(QStringLiteral("Player"));
        Player->resize(364, 362);
        actionOpen = new QAction(Player);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionPlay = new QAction(Player);
        actionPlay->setObjectName(QStringLiteral("actionPlay"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPlay->setIcon(icon1);
        actionStop = new QAction(Player);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon2);
        actionPause = new QAction(Player);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon3);
        centralWidget = new QWidget(Player);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 210, 331, 72));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Progress = new QSlider(widget);
        Progress->setObjectName(QStringLiteral("Progress"));
        Progress->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(Progress, 0, 0, 1, 4);

        Pause = new QPushButton(widget);
        Pause->setObjectName(QStringLiteral("Pause"));
        Pause->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(Pause, 1, 0, 1, 1);

        Play = new QPushButton(widget);
        Play->setObjectName(QStringLiteral("Play"));
        Play->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(Play, 1, 1, 1, 1);

        Stop = new QPushButton(widget);
        Stop->setObjectName(QStringLiteral("Stop"));
        Stop->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(Stop, 1, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Volume = new QSlider(widget);
        Volume->setObjectName(QStringLiteral("Volume"));
        Volume->setValue(50);
        Volume->setSliderPosition(50);
        Volume->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(Volume);

        volumeLabel = new QLabel(widget);
        volumeLabel->setObjectName(QStringLiteral("volumeLabel"));
        volumeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(volumeLabel);


        gridLayout->addLayout(verticalLayout, 1, 3, 1, 1);

        Player->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Player);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 364, 23));
        Player->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Player);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Player->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Player);
        statusBar->setObjectName(QStringLiteral("statusBar"));
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
        Player->setWindowTitle(QApplication::translate("Player", "Media Player", 0));
        actionOpen->setText(QApplication::translate("Player", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("Player", "Open an audio file", 0));
#endif // QT_NO_TOOLTIP
        actionPlay->setText(QApplication::translate("Player", "Play", 0));
#ifndef QT_NO_TOOLTIP
        actionPlay->setToolTip(QApplication::translate("Player", "Play music", 0));
#endif // QT_NO_TOOLTIP
        actionStop->setText(QApplication::translate("Player", "Stop", 0));
#ifndef QT_NO_TOOLTIP
        actionStop->setToolTip(QApplication::translate("Player", "Stop music", 0));
#endif // QT_NO_TOOLTIP
        actionPause->setText(QApplication::translate("Player", "Pause", 0));
        Pause->setText(QApplication::translate("Player", "Pause", 0));
        Play->setText(QApplication::translate("Player", "Play", 0));
        Stop->setText(QApplication::translate("Player", "Stop", 0));
        volumeLabel->setText(QApplication::translate("Player", "Volume", 0));
    } // retranslateUi

};

namespace Ui {
    class Player: public Ui_Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
