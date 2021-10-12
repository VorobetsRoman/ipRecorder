#include "peeruifacade.h"

PeerUiFacade::PeerUiFacade(QPushButton *own
                           , QPushButton *alt
                           , QLabel *indicator)
    : mp_own(own), mp_alt(alt), mp_indicator(indicator)
{
    m_switchOn();
}

PeerUiFacade::~PeerUiFacade()
{
    m_setUi(false);
    mp_indicator->setText(QStringLiteral("Empty"));
}

void PeerUiFacade::m_switchOn()
{
    m_setUi(true);
    connect(this, &Peer::sg_connectionState,
            this, [=] (QAbstractSocket::SocketState socketState) {
       if (socketState == QAbstractSocket::ConnectedState) {
           mp_indicator->setText(QStringLiteral("Connected"));
       }
    });
}

void PeerUiFacade::m_setUi(bool isOn)
{
    mp_own->setIcon(QIcon(isOn
                          ? QStringLiteral(":/Buttons/media-stop-32.png")
                          : QStringLiteral(":/Buttons/media-play-16.png")));
    mp_own->setChecked(isOn);
    mp_alt->setEnabled(!isOn);
}
