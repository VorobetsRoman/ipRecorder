#include "socketpeer.h"
#include <QDebug>

SocketPeer::
SocketPeer(QObject *parent)
    : Peer(parent)
{
    qDebug() << "socket started";
}

SocketPeer::~SocketPeer()
{
    qDebug() << "socket stopped";
}

void SocketPeer::
initConnection(const int &port
               , const QString &host)
{
    m_initSocket(port, host);
}

void SocketPeer::
m_initSocket(const int &port
             , const QString &host)
{
    m_socket = QSharedPointer<QTcpSocket>(
                new QTcpSocket, &QObject::deleteLater);
    p_initSocket();
    m_connectToHost(port, host);
}

void SocketPeer::
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
