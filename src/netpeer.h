#ifndef NETPEER_H
#define NETPEER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class NetPeer : public QObject
{
public:
    NetPeer(QObject *parent = nullptr);

private:
    QSharedPointer<QTcpServer> m_server;
    QSharedPointer<QTcpSocket> m_socket;
    void m_initSocket(const int &port
                      , const QString &host);
    void m_initServer(const int &port);
    void m_connectToHost(const int &port
                         , const QString &host);

private slots:
    void sl_socketDisconnected();
};

#endif // NETPEER_H
