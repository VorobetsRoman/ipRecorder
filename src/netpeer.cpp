#include "netpeer.h"
#include <QTimer>




NetPeer::
NetPeer(QObject *parent)
    : QObject(parent)
{

}




void NetPeer::
m_initSocket(const int &port
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
        //TODO: обработать ошибку
    }
}




void NetPeer::
m_connectToHost(const int &port
                , const QString &host)
{
    m_socket.data()->connectToHost(host
                                   , port
                                   , QIODevice::ReadWrite);
    QTimer::singleShot(100, this, [=] {
        if (m_socket.data()->state()
                != QAbstractSocket::ConnectedState) {
            m_connectToHost(port, host);
        }
    });
}
