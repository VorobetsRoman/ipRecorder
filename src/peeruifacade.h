#ifndef PEERUIFACADE_H
#define PEERUIFACADE_H

#include "Common/peer.h"
#include <QPushButton>
#include <QLabel>

class PeerUiFacade : public Peer
{
public:
    PeerUiFacade(QPushButton *own
                 , QPushButton *alt
                 , QLabel *indicator);
};

#endif // PEERUIFACADE_H
