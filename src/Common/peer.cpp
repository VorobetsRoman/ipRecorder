#include "peer.h"
#include <QDebug>

Peer::
Peer(QObject *parent)
    : QObject(parent)
{

}

void Peer::
sl_readyRead()
{
    qDebug() << "ready read";
    auto incomingData = m_socket.data()->readAll();
    emit sg_incomingData(incomingData);
}

void Peer::
p_initSocket()
{
    connect(m_socket.data(), &QTcpSocket::stateChanged,
            this, &Peer::sg_connectionState);
    connect(m_socket.data(), &QTcpSocket::disconnected,
            this,   [=]{m_socket.clear();});
    connect(m_socket.data(), &QTcpSocket::readyRead,
            this, &Peer::sl_readyRead);
}
