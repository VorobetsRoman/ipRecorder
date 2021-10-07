#ifndef PEER_H
#define PEER_H

#include <QtCore>
#include <QObject>
#include <QTcpSocket>

class Peer : public QObject
{
    Q_OBJECT
public:
    Peer(QObject *parent = nullptr);
    virtual void initConnection(const int &port
                                , const QString &host = 0) = 0;
signals:
    void sg_connectionState(QAbstractSocket::SocketState);

protected slots:
    void sl_readyRead();

protected:
    QSharedPointer<QTcpSocket> m_socket;    ///< Указатель на сокет

    void p_initSocket();
};

#endif // PEER_H
