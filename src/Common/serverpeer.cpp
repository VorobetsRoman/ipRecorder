#include "serverpeer.h"

ServerPeer::
ServerPeer(QObject *parent)
    : Peer(parent)
{

}

void ServerPeer::
initConnection(const int &port
               , const QString &host)
{
    m_initServer(port);
}

void ServerPeer::
m_initServer(const int &port)
{
    m_server = QSharedPointer<QTcpServer>(
                new QTcpServer, &QObject::deleteLater);
    if (!m_server.data()->listen(QHostAddress::Any, port)) {
        throw m_server.data()->errorString();
    }
    m_server.data()->setMaxPendingConnections(1);
    connect(m_server.data(), &QTcpServer::newConnection,
            this, [=] {
        m_socket = QSharedPointer<QTcpSocket>(
                    m_server->nextPendingConnection()
                    , &QObject::deleteLater);
        m_initSocket();
    });
}

void ServerPeer::
m_initSocket()
{
    connect(m_socket.data(), &QTcpSocket::stateChanged,
            this, &ServerPeer::sg_connectionState);
    connect(m_socket.data(), &QTcpSocket::disconnected,
            this,   [=]{m_socket.clear();});
    connect(m_socket.data(), &QTcpSocket::readyRead,
            this, &ServerPeer::sl_readyRead);
}
