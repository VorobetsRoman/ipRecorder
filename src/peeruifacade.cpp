#include "peeruifacade.h"

PeerUiFacade::PeerUiFacade(QPushButton *own
                           , QPushButton *alt
                           , QLabel *indicator)
{
    own->setIcon(QIcon(QStringLiteral(":/Buttons/media-stop-32.png")));
    own->setChecked(true);
    alt->setEnabled(false);
    connect(this, &Peer::sg_connectionState,
            this, [=] (QAbstractSocket::SocketState socketState) {
       if (socketState == QAbstractSocket::ConnectedState) {
           indicator->setText(QStringLiteral("Connected"));
       }
    });
}
