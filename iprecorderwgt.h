#ifndef IPRECORDERWGT_H
#define IPRECORDERWGT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>



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
    void on_pbStartServer_released          ();
    void on_rbClientChoice_toggled          (bool checked);
    void on_pbConnectToServer_released      ();
    void on_hsPlaySpeed_sliderMoved         (int position);
    void on_tbFileNameForRecording_released ();
    void on_pbStartStopRecord_released      ();
    void on_pbPauseRecord_released          ();
    void on_tbFileNameForPlayer_released    ();
    void on_pbStartStopPlayer_released      ();

    void newServerConnectionSlot            ();
    void socketConnected                    ();
    void socketDisconnected                 ();
    void socketReadyRead                    ();

    void connectionTimerTimeoutSlot         ();

    void closeConnectionTimer               ();

    void playTimerTimeoutSlot               ();

    void on_rbTimeMarkerIsOn_toggled(bool checked);

    void on_rbSetPlaySpeed_toggled(bool checked);

private:
    Ui::IpRecorderWgt   *ui     {NULL};
    QTcpServer          *server {NULL};
    QTcpSocket          *socket {NULL};
    QTimer              *connectionTimer    {NULL};
    QTimer              *playTimer          {NULL};
    QString             fileName {""};
    QFile               workFile;

    bool                recordingOn     {false};
    bool                recordingPaused {false};
    bool                playingOn       {false};
    bool                playingPaused   {false};

    int                 timeInterval    {200};
    int                 defaultPlayInterval {200};

    void connectToHost                      ();
    void playinGotoBegin                    ();
};

#endif // IPRECORDERWGT_H
