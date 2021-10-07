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
}
