#ifndef SOCKETPEER_H
#define SOCKETPEER_H

#include "peer.h"
#include <QObject>
#include <QTcpSocket>

class SocketPeer : public Peer
{
    Q_OBJECT
public:
    SocketPeer(QObject *parent = nullptr);
    ~SocketPeer();
    // Peer interface
public:
    void initConnection(const int &port, const QString &host);

private:
    QSharedPointer<QTcpSocket> m_socket;    ///< Указатель на сокет
    void m_initSocket(const int &port
                      , const QString &host);
    void m_connectToHost(   ///< Функция соединения с сервером
            const int &port         ///< portId
            , const QString &host   //!< hostName
            );
};

#endif // SOCKETPEER_H
