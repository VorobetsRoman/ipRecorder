#ifndef PEERUIFACADE_H
#define PEERUIFACADE_H

#include "Common/peer.h"
#include <QPushButton>
#include <QLabel>

class PeerUiFacade : public Peer
{
    Q_OBJECT
public:
    PeerUiFacade(QPushButton *own
                 , QPushButton *alt
                 , QLabel *indicator);
    ~PeerUiFacade();

private:
    QPushButton *mp_own {nullptr};
    QPushButton *mp_alt {nullptr};
    QLabel *mp_indicator {nullptr};
    void m_switchOn();
    void m_setUi(bool isOn);
};

#endif // PEERUIFACADE_H
