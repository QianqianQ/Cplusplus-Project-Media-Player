#include "player.h"
#include "ui_player.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QMediaContent>
#include "QFileDialog"


Player::Player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    updateList();
    player->setVolume(100);
    ui->listWidget->setCurrentRow(0);
    if(ui->listWidget->count() != 0){
        loadTrack();
        player->pause();
        updater->start();
    }
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

void Player::on_add_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"));
    if(!files.empty())
    {
        playlist.add(files);
        updateList();
        ui->save->setChecked(false);
        updater->start();
    }
}

void Player::on_remove_clicked()
{
    int index = getIndex();
    if(index != -1)
    {
       playlist.remove(index);
       updateList();
       ui->listWidget->setCurrentRow(index);
       ui->save->setChecked(false);
    }
}

void Player::on_save_clicked()
{
    playlist.save();
    ui->save->setChecked(true);
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
void Player::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist.getFileList());
}


int Player::getIndex()
{
    return ui->listWidget->currentIndex().row();
}

void Player::loadTrack()
{
     QString str = QString::fromStdString(playlist.tracks[getIndex()].getLocation());
     player->setMedia(QUrl::fromLocalFile(str));
     str = QString::fromStdString(playlist.tracks[getIndex()].getName());
     ui->currentSong->setText(str);
}
