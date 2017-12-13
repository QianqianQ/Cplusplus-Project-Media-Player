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
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include <exception>
Player::Player(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Player)
{

    ui->setupUi(this);

    // Setting icons
    QPixmap play_image(":/images/icons/play.png");
    QPixmap pause_image(":/images/icons/pause.png");
    QPixmap stop_image(":/images/icons/stop.png");
    QPixmap next_image(":/images/icons/next.png");
    QPixmap previous_image(":/images/icons/previous.png");
    //QPixmap add_image(":/images/icons/add.png");
    //QPixmap remove_image(":/images/icons/delete.jpg");
    QIcon play_icon, pause_icon, stop_icon,next_icon,previous_icon;
    //QIcon add_icon,remove_icon;
    play_icon.addPixmap(play_image);
    pause_icon.addPixmap(pause_image);
    stop_icon.addPixmap(stop_image);
    next_icon.addPixmap(next_image);
    previous_icon.addPixmap(previous_image);
    //add_icon.addPixmap(add_image);
    //remove_icon.addPixmap(remove_image);
    ui->Play->setIcon(play_icon);
    ui->Play->setIconSize(QSize(50,50));
    ui->Stop->setIcon(stop_icon);
    ui->Stop->setIconSize(QSize(50,50));
    ui->Pause->setIcon(pause_icon);
    ui->Pause->setIconSize(QSize(50,50));
    ui->Next->setIcon(next_icon);
    ui->Next->setIconSize(QSize(50,50));
    ui->previous->setIcon(previous_icon);
    ui->previous->setIconSize(QSize(50,50));
    ui->listWidget->clear();
    //ui->add->setIcon(add_icon);
    //ui->add->setIconSize(QSize(30,30));
    //ui->remove->setIcon(remove_icon);
    //ui->remove->setIconSize(QSize(50,30));

    // player and playlist initialization
    player = new QMediaPlayer;
    playlist = new Playlist();
    this->updateList();
    player->setVolume(50);
    ui->listWidget->setCurrentRow(0);
    if(ui->listWidget->count() != 0){
        loadTrack();
    }

    // Audio visualization initalization
    probe = new QAudioProbe(this);
    calculator = new FFTCalc(this);
    qRegisterMetaType< QVector<double> >("QVector<double>");
    probe->setSource(player);
    qDebug()<<probe->isActive();

    // Signals and slots
    connect(player,&QMediaPlayer::positionChanged,this,&Player::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::on_durationChanged);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(calculator, SIGNAL(calculatedSpectrum(QVector<double>)), this,
            SLOT(processSpectrum(QVector<double>)));
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Player::statusChanged);

}

Player::~Player()
{
    delete ui;
}

// Add file to playlist
void Player::on_add_clicked()
{
    int current_row = ui->listWidget->currentRow();
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"));
    if(!files.empty())
    {
        playlist->add(files);
        updateList();
        save_list();
    }
    ui->listWidget->setCurrentRow(current_row);
}

// Remove file from playlist
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

// Save new playlist after adding or deleting file
void Player::save_list()
{
    playlist->save();
    //ui->save->setChecked(true);
}

// Play
void Player::on_Play_clicked()
{
   if(ui->listWidget->count()==0)
   {
       QMessageBox::information( NULL,
       "Error message",
       "No media in the playlist!");
   }
   else
   {
    try{
    if(player->state()==QMediaPlayer::StoppedState)
    {
        if (ui->listWidget->count()==1)
        {
            ui->listWidget->setCurrentRow(0);
        }
        int current_row =ui->listWidget->currentRow();
        QString str = QString::fromStdString(playlist->tracks[current_row].getLocation());
        player->setMedia(QUrl::fromLocalFile(str));
        str = QString::fromStdString(playlist->tracks[current_row].getName());
        ui->currentSong->setText(str);
    }
    if(player->state()==QMediaPlayer::PlayingState)
    {
        QString current_url = player->currentMedia().canonicalUrl().toString();
        int current_row =ui->listWidget->currentRow();
        QString str = QString::fromStdString(playlist->tracks[current_row].getLocation());
        if (current_url != str)
        {
            player->setMedia(QUrl::fromLocalFile(str));
            str = QString::fromStdString(playlist->tracks[current_row].getName());
            ui->currentSong->setText(str);
        }

    }
    player->play();
    ui->statusBar->showMessage("Playing");
    }
    catch(std::exception& e)
        {
       QMessageBox::information( NULL,
       "Error message",
       "An error occured!");
        }
    }
}
// Pause
void Player::on_Pause_clicked()
{
    player->pause();
    ui->statusBar->showMessage("Paused");
}

// Stop
void Player::on_Stop_clicked()
{
    ui->spec63->setValue(0);
    ui->spec125->setValue(0);
    ui->spec250->setValue(0);
    ui->spec500->setValue(0);
    ui->spec1000->setValue(0);
    ui->spec2000->setValue(0);
    ui->spec4000->setValue(0);
    ui->spec8000->setValue(0);
    ui->spec16000->setValue(0);
    ui->spec20000->setValue(0);
    player->stop();
    ui->statusBar->showMessage("Stopped");
}

// Volume adjustment
void Player::on_Volume_sliderMoved(int position)
{
    player->setVolume(position);
}

// Seeking audio position when progress bar moves
void Player::on_Progress_sliderMoved(int position)
{
    player->setPosition(position);
}

// Change progess bar position while audio position changes
void Player::on_positionChanged(qint64 position)
{
    ui->Progress->setValue(position);
}

// Set the maximum value of the progress bar as a new song loaded
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

// audio visualization in ui
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

// update playlist
void Player::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist->getFileList());
}

// Get current index of the playlist
int Player::getIndex()
{
    return ui->listWidget->currentIndex().row();
}

// load current track
void Player::loadTrack()
{
     QString str = QString::fromStdString(playlist->tracks[getIndex()].getLocation());
     player->setMedia(QUrl::fromLocalFile(str));
     str = QString::fromStdString(playlist->tracks[getIndex()].getName());
     ui->currentSong->setText(str);
}

// Next song
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

// Previous song
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

void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
        case QMediaPlayer::EndOfMedia:
            {
                if(mode==0)
                    player->stop();
                else if (mode==1)
                    on_Play_clicked();
                else if (mode==2)
                    on_Next_clicked();
                break;
            }
        case QMediaPlayer::NoMedia:
            {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","There is no current media");
            messageBox.setFixedSize(200,200);
            break;
            }
        case QMediaPlayer::InvalidMedia:
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","The current media cannot be played.");
                messageBox.setFixedSize(200,200);
                break;
            }
        default:
            break;
    }
}
