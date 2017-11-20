#include "player.h"
#include "ui_player.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QMediaContent>
player::player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::player)
{
    ui->setupUi(this);
    Player = new QMediaPlayer;
    //QMediaContent file(QUrl::fromLocalFile(QFileInfo("test.wav").absoluteFilePath()));
    //Player->setMedia(file);
    //Player->setMedia(QMediaContent(QUrl::fromLocalFile(QFileInfo("test.wav").absoluteFilePath())));
    Player->setMedia(QMediaContent(QUrl::fromLocalFile("C:\\Users\\Qianqian\\Desktop\\Cpp_project\\qt-player\\test.wav")));
}

player::~player()
{
    delete ui;
}

void player::on_play_clicked()
{
    Player->play();
}

void player::on_pause_clicked()
{
    Player->pause();
}

void player::on_stop_clicked()
{
    Player->stop();
}

void player::on_volume_sliderMoved(int position)
{
    Player->setVolume(position);
}
