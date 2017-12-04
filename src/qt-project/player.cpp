#include "player.h"
#include "ui_player.h"
#include <QMediaPlayer>
#include <QUrl>
#include <QDir>
#include <QFile>
#include <QMediaContent>
#include "QFileDialog"
#include "playlist.h"
#include <stdio.h>
#include <string.h>
Player::Player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Player)
{

    ui->setupUi(this);
    player = new QMediaPlayer;
    playlist = new Playlist();
    //updater = new QTimer(this);
    this->updateList();
    player->setVolume(50);
    ui->listWidget->setCurrentRow(0);
    if(ui->listWidget->count() != 0){
        loadTrack();
        //player->stop();
        //updater->start();
    }
    probe = new QAudioProbe(this);
    calculator = new FFTCalc(this);
    qRegisterMetaType< QVector<double> >("QVector<double>");

    connect(player,&QMediaPlayer::positionChanged,this,&Player::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::on_durationChanged);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(calculator, SIGNAL(calculatedSpectrum(QVector<double>)), this,
            SLOT(processSpectrum(QVector<double>)));
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
        playlist->add(files);
        updateList();
        //ui->save->setChecked(false);
        //updater->start();
        save_list();
    }
}

void Player::on_remove_clicked()
{
    //on_Stop_clicked();
    int index = getIndex();
    if(index != -1)
    {
       playlist->remove(index);
       updateList();
       /*
       if (index !=0)
            ui->listWidget->setCurrentRow(index-1);
       else
           ui->listWidget->setCurrentRow(0); */
       //ui->save->setChecked(false);
       save_list();
    }
}

void Player::save_list()
{
    playlist->save();
    //ui->save->setChecked(true);
}

void Player::on_Play_clicked()
{
    if(player->state()==QMediaPlayer::StoppedState)
    {
        int current_row =ui->listWidget->currentRow();
        QString str = QString::fromStdString(playlist->tracks[current_row].getLocation());
        player->setMedia(QUrl::fromLocalFile(str));
        str = QString::fromStdString(playlist->tracks[current_row].getName());
        ui->currentSong->setText(str);
    }
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

void Player::processBuffer(QAudioBuffer buffer)
{
    qreal audioPeak;
    int duration;
    //qDebug() << buffer.format().sampleRate();
    //qDebug() << SHRT_MAX;
    if(buffer.frameCount() < SPECSIZE)
        return;
    sample.resize(buffer.frameCount());

    if(buffer.format().sampleType() == QAudioFormat::SignedInt){
      QAudioBuffer::S16S *data = buffer.data<QAudioBuffer::S16S>();

      if (buffer.format().sampleSize() == 32)
        audioPeak = INT_MAX;
      else if (buffer.format().sampleSize() == 16)
        audioPeak = SHRT_MAX;
      else
        audioPeak = CHAR_MAX;
      for(int i=0; i<buffer.frameCount(); i++){
        sample[i] = data[i].left/audioPeak;
        leftLevel+= abs(data[i].left)/audioPeak;
        rightLevel+= abs(data[i].right)/audioPeak;
      }
    }

    else if(buffer.format().sampleType() == QAudioFormat::UnSignedInt){
        QAudioBuffer::S16U *data = buffer.data<QAudioBuffer::S16U>();
        if (buffer.format().sampleSize() == 32)
          audioPeak = UINT_MAX;
        else if (buffer.format().sampleSize() == 16)
          audioPeak = USHRT_MAX;
        else
          audioPeak = UCHAR_MAX;

        for(int i=0; i<buffer.frameCount(); i++){
          sample[i] = data[i].left/audioPeak;
          leftLevel+= abs(data[i].left)/audioPeak;
          rightLevel+= abs(data[i].right)/audioPeak;
        }
    }

    else if(buffer.format().sampleType() == QAudioFormat::Float){
      QAudioBuffer::S32F *data = buffer.data<QAudioBuffer::S32F>();
      audioPeak = 1.00003;
      for(int i=0; i<buffer.frameCount(); i++){
        sample[i] = data[i].left/audioPeak;
        if(sample[i] != sample[i]){
          sample[i] = 0;
        }
        else{
          leftLevel+= abs(data[i].left)/audioPeak;
          rightLevel+= abs(data[i].right)/audioPeak;
        }
      }
    }

    if(probe->isActive()){
        duration = buffer.format().durationForBytes(buffer.frameCount())/1000;
        //qDebug() << sample[2];
        calculator->calc(sample, duration);
    }

    emit levels(leftLevel/buffer.frameCount(), rightLevel/buffer.frameCount());

}
void Player::processSpectrum(QVector<double> spectrum)
{
    //qDebug() << "Spectrum";
   // qDebug() << spectrum[2];
    int norm = 1500;
    ui->spec63->setValue(spectrum[2]*norm);
    ui->spec125->setValue(spectrum[3]*norm);
    ui->spec250->setValue(spectrum[6]*norm);
    ui->spec500->setValue(spectrum[12]*norm);
    ui->spec1000->setValue(spectrum[24]*norm);
    ui->spec2000->setValue(spectrum[47]*norm);
    ui->spec4000->setValue(spectrum[93]*norm);
    ui->spec8000->setValue(spectrum[186]*norm);
    ui->spec16000->setValue(spectrum[371]*norm);
    ui->spec20000->setValue(spectrum[464]*norm);


}
void Player::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist->getFileList());
}


int Player::getIndex()
{
    return ui->listWidget->currentIndex().row();
}

void Player::loadTrack()
{
     QString str = QString::fromStdString(playlist->tracks[getIndex()].getLocation());
     player->setMedia(QUrl::fromLocalFile(str));
     str = QString::fromStdString(playlist->tracks[getIndex()].getName());
     ui->currentSong->setText(str);
}

void Player::on_Next_clicked()
{
    player->stop();
    int previous_row =getIndex();
    int current_row;
    if(previous_row != ui->listWidget->count()-1){
        current_row = previous_row+1;
    }
    else{
        current_row = 0;
    }
    ui->listWidget->setCurrentRow(current_row);
    on_Play_clicked();
}

void Player::on_previous_clicked()
{
    player->stop();
    int previous_row =getIndex();
    int current_row;
    if (previous_row!=0){
        current_row = previous_row-1;
    }
    else{
        current_row = ui->listWidget->count()-1;
    }
    ui->listWidget->setCurrentRow(current_row);
    on_Play_clicked();
}

void Player::on_comboBox_currentIndexChanged(int index)
{
    mode = index;
}
