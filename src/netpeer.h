#ifndef NETPEER_H
#define NETPEER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Common/peer.h"

class NetPeer : public Peer
{
public:
    NetPeer(QObject *parent = nullptr);

private:
    QSharedPointer<QTcpServer> m_server;    ///< Указатель на сервер
    QSharedPointer<QTcpSocket> m_socket;    ///< Указатель на сокет
    /*!
     * \brief Инициализация сокета
     * \param port
     * \param host
     */
    void p_initSocket(const int &port
                      , const QString &host);
    void m_initServer(const int &port);
    /*!
     * \brief Connection to host
     * \param Идентификатор порта
     * \param host идентификатор хоста
     */
    void m_connectToHost(   ///< Функция соединения с сервером
            const int &port         ///< portId
            , const QString &host   //!< hostName
            );

private slots:
    void sl_socketDisconnected();

    // Peer interface
public:
    void initConnection(const int &port, const QString &host);
};

#endif // NETPEER_H
