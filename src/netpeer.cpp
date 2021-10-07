#include "netpeer.h"
#include <QTimer>




NetPeer::
NetPeer(QObject *parent)
    : Peer(parent)
{

}




void NetPeer::
p_initSocket(const int &port
             , const QString &host)
{
    m_socket = QSharedPointer<QTcpSocket>(
                new QTcpSocket, &QObject::deleteLater);
    m_connectToHost(port, host);
}




void NetPeer::
m_initServer(const int &port)
{
    m_server = QSharedPointer<QTcpServer>(
                new QTcpServer, &QObject::deleteLater);
    if (!m_server.data()->listen(QHostAddress::Any, port)) {
        throw m_server.data()->errorString();
    }
}




void NetPeer::
m_connectToHost(const int &_port
                , const QString &_host)
{
    m_socket.data()->connectToHost(_host
                                   , _port
                                   , QIODevice::ReadWrite);
    QTimer::singleShot(100, this, [=] {
        if (m_socket.data()->state()
                != QAbstractSocket::ConnectedState) {
            m_connectToHost(_port, _host);
        }
    });
}

void NetPeer::sl_socketDisconnected()
{

}

void NetPeer::initConnection(const int &port, const QString &host)
{

}
