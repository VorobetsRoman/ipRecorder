#ifndef IPRECORDERWGT_H
#define IPRECORDERWGT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QFile>
#include "playerform.h"
#include "recorderform.h"


namespace Ui {
class IpRecorderWgt;
}

class IpRecorderWgt : public QWidget
{
    Q_OBJECT

public:
    explicit IpRecorderWgt                  (QWidget *parent = 0);
        ~IpRecorderWgt                      ();

private slots:
    void on_pbStartServer_released          ();
    void on_rbClientChoice_toggled          (bool checked);
    void on_pbConnectToServer_released      ();

    void newServerConnectionSlot            ();
    void socketConnected                    ();
    void socketDisconnected                 ();

    void connectionTimerTimeoutSlot         ();

    void closeConnectionTimer               ();

    void on_rbServerChoice_toggled(bool checked);

private:
    Ui::IpRecorderWgt   *ui             {NULL};
    QTcpServer          *server         {NULL};
    QTcpSocket          *socket         {NULL};
    QTimer              *connectionTimer{NULL};
    PlayerForm          *playerForm     {NULL};
    RecorderForm        *recorderForm   {NULL};

    void connectToHost                      ();
};

#endif // IPRECORDERWGT_H
