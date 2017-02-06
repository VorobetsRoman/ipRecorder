#ifndef PLAYERFORM_H
#define PLAYERFORM_H

#include <QWidget>
#include <QTimer>
#include <QFile>

namespace Ui {
class PlayerForm;
}

class PlayerForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerForm(QWidget *parent = 0);
    ~PlayerForm();

private slots:
    void on_tbFileNameForPlayer_released();
    void on_rbSetPlaySpeed_toggled      (bool checked);
    void on_rbTimeMarkerIsOn_toggled    (bool checked);
    void on_hsPlaySpeed_sliderMoved     (int position);
    void on_pbStartStopPlayer_released  ();
    void on_pbPauseRecord_2_released    ();

    void playTimerTimeoutSlot           ();
private:
    Ui::PlayerForm *ui;

    bool playingIsOn    {false};
    bool pauseIsOn      {false};
    QTimer  *playTimer  {NULL};
    qint64 playDelay    {200};
    QFile *workFile  {NULL};
};

#endif // PLAYERFORM_H
