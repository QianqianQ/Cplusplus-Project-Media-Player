#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
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

private:
    Ui::Player *ui;
    QMediaPlayer *player;
};

#endif // PLAYER_H
