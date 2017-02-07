#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QTcpSocket>

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerForm                 (QWidget *parent = 0);
        ~PlayerForm                     ();
    void setSocket                      (QTcpSocket* newSocket);

private slots:
    void on_tbFileNameForPlayer_released();
    void on_rbSetPlaySpeed_toggled      (bool checked);
    void on_rbTimeMarkerIsOn_toggled    (bool checked);
    void on_hsPlaySpeed_sliderMoved     (int position);
    void on_pbStartStopPlayer_released  ();
    void on_pbPausePlay_released        ();

    void playTimerTimeoutSlot           ();

private:
    Ui::PlayerForm *ui      {NULL};

    bool        playingIsOn {false};
    bool        pauseIsOn   {false};
    QTimer      *playTimer  {NULL};
    qint64      playDelay   {2000};
    QFile       *workFile   {NULL};
    QTcpSocket  *socket     {NULL};
    bool        timeMarkerExist {false};

    void workFileAtEnd  ();
};

#endif // PLAYERFORM_H
