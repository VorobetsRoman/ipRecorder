#ifndef PEER_H
#define PEER_H

#include <QtCore>

class Peer
{
public:
    Peer();
    virtual void initConnection(const int &port
                                , const QString &host = 0);

};

#endif // PEER_H
