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
    explicit IpRecorderWgt(QWidget *parent = nullptr);
        ~IpRecorderWgt();

private slots:
    void on_pbStartServer_released();
    void on_pbConnectToServer_released();

    void sl_newServerConnection();
    void sl_socketConnected();
    void sl_socketDisconnected();
    void sl_connectionTimerTimeout();

private:
    Ui::IpRecorderWgt   *mp_ui             {nullptr}; ///<
    QTcpServer          *mp_server         {nullptr}; ///<
    QTcpSocket          *mp_socket         {nullptr}; ///<
    QTimer              *mp_connectionTimer{nullptr}; ///<
    PlayerForm          *mp_playerForm     {nullptr}; ///<
    RecorderForm        *mp_recorderForm   {nullptr}; ///<

//    QTimer              m_temp;             ///< Timer for KDA

    void m_closeConnectionTimer();
    void m_connectToHost();
    void m_initSettings();
};

#endif // IPRECORDERWGT_H
