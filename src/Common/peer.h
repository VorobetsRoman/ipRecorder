#ifndef PEER_H
#define PEER_H

#include <QtCore>
#include <QObject>
#include <QAbstractSocket>

class Peer : public QObject
{
    Q_OBJECT
public:
    Peer(QObject *parent = nullptr);
    virtual void initConnection(const int &port
                                , const QString &host = 0) = 0;
signals:
    void sg_connectionState(QAbstractSocket::SocketState);
};

#endif // PEER_H
