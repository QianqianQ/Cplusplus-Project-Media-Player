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
#include <QMediaMetaData>
#include <QtGlobal>
#include <QMediaService>
#include <QStringList>
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
    QIcon play_icon, pause_icon, stop_icon,next_icon,previous_icon;
    play_icon.addPixmap(play_image);
    pause_icon.addPixmap(pause_image);
    stop_icon.addPixmap(stop_image);
    next_icon.addPixmap(next_image);
    previous_icon.addPixmap(previous_image);

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
    ui->metadata_list->clear();
    ui->mode->setCurrentIndex(0);
    mode = ui->mode->currentIndex();
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
    //qDebug()<<probe->isActive();

    // Signals and slots
    connect(player,&QMediaPlayer::positionChanged,this,&Player::on_positionChanged);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::on_durationChanged);
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(calculator, SIGNAL(calculatedSpectrum(QVector<double>)), this,
            SLOT(processSpectrum(QVector<double>)));
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &Player::statusChanged);
    connect(player,&QMediaPlayer::stateChanged,this,&Player::stateChanged);
    connect(player, static_cast<void (QMediaPlayer::*)()>(&QMediaPlayer::metaDataChanged), this, &Player::display_metadata);

}

Player::~Player()
{
    delete ui;
}

// Add file to playlist
void Player::on_add_clicked()
{
    int empty_flag=0;
        int current_row = 0;

        if(ui->listWidget->count()==0)
            empty_flag=1;

        if (empty_flag==0)
            current_row = ui->listWidget->currentRow();

        QStringList files = QFileDialog::getOpenFileNames(this, tr("Select Music Files"));
        if(!files.empty())
        {
            playlist->add(current_row,files);
            updateList();
            save_list();
        }
        ui->listWidget->setCurrentRow(current_row);
}

// Remove file from playlist
int Player::on_remove_clicked()
{
    //on_Stop_clicked();
    int index = ui->listWidget->currentRow();
    if(index != -1)
    {
        if(player->state()==QMediaPlayer::PlayingState || player->state()==QMediaPlayer::PausedState)
        {
            QString current_url = player->currentMedia().canonicalUrl().toString();
            QString str = "file://"+QString::fromStdString(playlist->tracks[index].getLocation());
            //qDebug()<<current_url;
            //qDebug()<<str;
            if (current_url == str)
            {
                QMessageBox::information( NULL,
                "Error message",
                "The music is playing, could not be removed!");
                return 0;
            }
        }
       playlist->remove(index);
       updateList();
       save_list();
       if (ui->listWidget->count()!=0 && index!=0)
            ui->listWidget->setCurrentRow(index-1);
       else if (ui->listWidget->count()!=0 && index==0)
           ui->listWidget->setCurrentRow(0);
    }
    return 0;

}
// update playlist
void Player::updateList()
{
    ui->listWidget->clear();
    ui->listWidget->addItems(playlist->getFileList());
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
       ui->metadata_list->clear();
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
        this->setWindowTitle("Media Player - "+str);
    }
    if(player->state()==QMediaPlayer::PlayingState)
    {
        QString current_url = player->currentMedia().canonicalUrl().toString();
        int current_row =ui->listWidget->currentRow();
        QString str = QString::fromStdString(playlist->tracks[current_row].getLocation());
        if (current_url != ("file://"+str))
        {
            player->setMedia(QUrl::fromLocalFile(str));
            str = QString::fromStdString(playlist->tracks[current_row].getName());
            this->setWindowTitle("Media Player - "+str);
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
    player->stop();
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
     this->setWindowTitle("Media Player - "+str);
}

// Next song
void Player::on_Next_clicked()
{
    player->stop();
    int current_row =getIndex();
    int next_row;
    if(current_row != ui->listWidget->count()-1){
        next_row = current_row+1;
    }
    else{
        next_row = 0;
    }
    ui->listWidget->setCurrentRow(next_row);
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

void Player::on_mode_currentIndexChanged(int index)
{
    mode = index;
}

void Player::statusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
        case QMediaPlayer::EndOfMedia:
            {
                // Playlist Loop
                if (mode==0)
                    on_Next_clicked();
                // Single Loop
                if (mode==1)
                    on_Play_clicked();
                // Playlist in order
                if (mode==2)
                {
                    int current_row =getIndex();
                    if(current_row==ui->listWidget->count()-1)
                    {
                        ui->listWidget->setCurrentRow(0);
                        on_Stop_clicked();
                        QString str = QString::fromStdString(playlist->tracks[0].getLocation());
                        player->setMedia(QUrl::fromLocalFile(str));
                        str = QString::fromStdString(playlist->tracks[0].getName());
                        this->setWindowTitle("Media Player - "+str);
                    }
                    else
                    {
                        on_Next_clicked();
                    }
                }
                // Single Once
                if(mode==3)
                {
                    on_Stop_clicked();
                    int current_row =ui->listWidget->currentRow();
                    QString str = QString::fromStdString(playlist->tracks[current_row].getLocation());
                    player->setMedia(QUrl::fromLocalFile(str));
                    str = QString::fromStdString(playlist->tracks[current_row].getName());
                    this->setWindowTitle("Media Player - "+str);
                }

                // Play randomly
                if (mode==4)
                {
                    int current_row = getIndex();
                    int amount = ui->listWidget->count();
                    int random_row = rand()%amount;
                    while(random_row == current_row)
                    {
                        random_row = rand()%amount;
                    }
                    ui->listWidget->setCurrentRow(random_row);
                    on_Play_clicked();
                }
                break;
            }
        case QMediaPlayer::NoMedia:
        case QMediaPlayer::InvalidMedia:
            {
                QMessageBox::information( NULL,
                "Error message",
                "The file unavailable");
                ui->metadata_list->clear();
                break;
            }
    //case QMediaPlayer::LoadedMedia:
            //display_metadata();
        default:
            break;
    }
}

void Player::stateChanged(QMediaPlayer::State s)
{
    if (s==QMediaPlayer::StoppedState )
    {
        ui->Pause->setEnabled(false);
        ui->Stop->setEnabled(false);
    }
    else if (s==QMediaPlayer::PausedState)
    {
        ui->Pause->setEnabled(false);
        ui->Stop->setEnabled(true);

    }
    else if (s==QMediaPlayer::PlayingState)
    {
        ui->Pause->setEnabled(true);
        ui->Stop->setEnabled(true);
    }
}

// display metadata
void Player::display_metadata()
{
    QString title, album, author,genre;
    ui->metadata_list->clear();
    title = "Title: "+player->metaData(QMediaMetaData::Title).toString();
    album = "Album: "+player->metaData(QMediaMetaData::AlbumTitle).toString();
    author = "Author: "+player->metaData(QMediaMetaData::ContributingArtist).toString();
    genre = "Genre: "+player->metaData(QMediaMetaData::Genre).toString();
    QStringList meta_list=(QStringList()<<title<<album<<author<<genre);
    ui->metadata_list->addItems(meta_list);

}

