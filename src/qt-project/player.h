#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QAudioProbe>
#include <QAudioBuffer>
#include <QVector>
#include "playlist.h"
#include "QTimer"
#include "fftcalc.h"

namespace Ui {
class Player;
}

class Player : public QMainWindow
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

private slots:
    void on_add_clicked();

    void on_remove_clicked();

    void save_list();

    void on_Play_clicked();

    void on_Pause_clicked();

    void on_Stop_clicked();

    void on_Volume_sliderMoved(int position);

    void on_Progress_sliderMoved(int position);

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void processBuffer(QAudioBuffer buffer);

    void processSpectrum(QVector<double> spectrum);

    void on_Next_clicked();

    void on_previous_clicked();


    void statusChanged(QMediaPlayer::MediaStatus status);

    void on_mode_currentIndexChanged(int index);

    void stateChanged(QMediaPlayer::State s);


private:
    void loadTrack();
    int getIndex();
    void updateList();

    Ui::Player *ui;
    QMediaPlayer *player;
    Playlist *playlist;
    //QTimer *updater;
    QAudioProbe  *probe;
    int mode;

    // Audio Buffer Data
    QByteArray buffer;// buffer for copying audio
    QVector<double> sample;// input for fft
    QVector<double> spectrum;// output vector containing spectrum
    FFTCalc *calculator;
    double leftLevel, rightLevel;
    //
signals:
    int levels(double left, double right);
};

#endif // PLAYER_H
