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
    void on_actionOpen_triggered();

    void on_Play_clicked();

    void on_Pause_clicked();

    void on_Stop_clicked();

    void on_Volume_sliderMoved(int position);

    void on_Progress_sliderMoved(int position);

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void processBuffer(QAudioBuffer buffer_);

private:
    Ui::Player *ui;
    QMediaPlayer *player;
    QAudioProbe  *probe;

    // Audio Buffer Data
    QByteArray buffer;// buffer for copying audio
    QVector<double> sample;// input for fft
    QVector<double> spectrum;// output vector containing spectrum
    //
};

#endif // PLAYER_H
