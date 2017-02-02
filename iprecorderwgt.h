#ifndef IPRECORDERWGT_H
#define IPRECORDERWGT_H

#include <QWidget>

namespace Ui {
class IpRecorderWgt;
}

class IpRecorderWgt : public QWidget
{
    Q_OBJECT

public:
    explicit IpRecorderWgt(QWidget *parent = 0);
    ~IpRecorderWgt();

private slots:
    void on_lePortName_editingFinished      ();
    void on_rbServerChoice_toggled          (bool checked);
    void on_pbStartServer_released          ();
    void on_rbClientChoice_toggled          (bool checked);
    void on_leServerName_editingFinished    ();
    void on_pbConnectToServer_released      ();
    void on_rbTimeMarkerIsOn_toggled        (bool checked);
    void on_rbSetPlaySpeed_toggled          (bool checked);
    void on_hsPlaySpeed_sliderMoved         (int position);
    void on_tbFileNameForRecording_released ();
    void on_pbStartStopRecord_released      ();
    void on_pbPauseRecord_released          ();
    void on_tbFileNameForPlayer_released    ();
    void on_pbStartStopPlayer_released      ();
    void on_pbPauseRecord_2_released        ();

private:
    Ui::IpRecorderWgt *ui;
};

#endif // IPRECORDERWGT_H
