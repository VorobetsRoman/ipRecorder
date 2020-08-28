/*!
  * @file Форма основного окна, содержит вкладки
  * с интерфейсами управления записью, воспроизведением, склеиванием файлов
  */
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

private:
    Ui::IpRecorderWgt   *mp_ui             {nullptr}; ///< Форма окна
    QTcpServer          *mp_server         {nullptr}; ///< Сервер
    QTcpSocket          *mp_socket         {nullptr}; ///< Сокет
    PlayerForm          *mp_playerForm     {nullptr}; ///< Форма управления воспроизведением
    RecorderForm        *mp_recorderForm   {nullptr}; ///< Форма управления записью

    void m_initSettings();
    void m_connectToHost();
    /*!
     * \brief m_updateUi
     * \param isServer
     * \param started
     */
    void m_updateUi(bool isServer, bool started);
};

#endif // IPRECORDERWGT_H
