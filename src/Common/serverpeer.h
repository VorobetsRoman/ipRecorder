#ifndef SERVERPEER_H
#define SERVERPEER_H

#include "peer.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerPeer : public Peer
{
    Q_OBJECT
public:
    ServerPeer(QObject *parent = nullptr);

    // Peer interface
public:
    void initConnection(const int &port, const QString &host);
    QSharedPointer<QTcpServer> m_server;    ///< Указатель на сервер
    QSharedPointer<QTcpSocket> m_socket;    ///< Указатель на сокет

private:
    void m_initServer(const int &port);
    void m_initSocket();
};

#endif // SERVERPEER_H
