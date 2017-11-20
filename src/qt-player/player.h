#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
namespace Ui {
class player;
}

class player : public QMainWindow
{
    Q_OBJECT

public:
    explicit player(QWidget *parent = 0);
    ~player();

private slots:
    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

    void on_volume_sliderMoved(int position);

private:
    Ui::player *ui;
    QMediaPlayer *Player;
};

#endif // PLAYER_H
