#include "player.h"
#include "ui_player.h"
#include <QFileDialog>
#include <QUrl>
Player::Player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    probe = new QAudioProbe(this);
    connect(player,&QMediaPlayer::positionChanged,this,&Player::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::on_durationChanged);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(player);
    qDebug()<<probe->isActive();
}

Player::~Player()
{
    delete ui;
}

void Player::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,"Open an audio file");
    on_Stop_clicked();
    player->setMedia(QUrl::fromLocalFile(file));
}

void Player::on_Play_clicked()
{
    player->play();
    ui->statusBar->showMessage("Playing");
}

void Player::on_Pause_clicked()
{
    player->pause();
    ui->statusBar->showMessage("Paused");
}

void Player::on_Stop_clicked()
{
    player->stop();
    ui->statusBar->showMessage("Stopped");
}

void Player::on_Volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void Player::on_Progress_sliderMoved(int position)
{
    player->setPosition(position);
}

void Player::on_positionChanged(qint64 position)
{
    ui->Progress->setValue(position);
}

void Player::on_durationChanged(qint64 position)
{
    ui->Progress->setMaximum(position);
}

void Player::processBuffer(QAudioBuffer buffer_)
{
    qDebug() << "Hey";
}
