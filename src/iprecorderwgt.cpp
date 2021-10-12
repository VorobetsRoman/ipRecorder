#include "iprecorderwgt.h"
#include "ui_iprecorderwgt.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QSettings>
#include "Common/usersettings.h"




//=================================== Конструктор
IpRecorderWgt::IpRecorderWgt(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::IpRecorderWgt)
{
    mp_ui->setupUi(this);
    mp_recorderForm = mp_ui->recorderWgt;
    mp_playerForm = mp_ui->playerWgt;

    m_initSettings();
}

IpRecorderWgt::~IpRecorderWgt()
{
    m_storeSettings();
    delete mp_ui;
}

void IpRecorderWgt::on_pbStartServer_released()
{
    if (m_peer.isNull()) {
        m_peer = QSharedPointer<Peer>(new ServerPeer
                                      , &QObject::deleteLater);
    } else {
        m_peer.clear();
    }
}

void IpRecorderWgt::on_pbConnectToServer_released()
{
    m_peer.clear();
    m_peer = QSharedPointer<Peer>(new SocketPeer
                                  , &QObject::deleteLater);
    m_updateUi(false, true);
}

void IpRecorderWgt::m_initSettings()
{
    mp_ui->lePortName->setText(
                UserSettings::valueFor(
                    QStringLiteral("port")
                    , QStringLiteral("5000")).toString());
    mp_ui->leServerName->setText(
                UserSettings::valueFor(
                    QStringLiteral("host")
                    , QStringLiteral("127.0.0.1")).toString());
}

void IpRecorderWgt::m_updateUi(bool isServer, bool started)
{
    mp_ui->pbStartServer->setEnabled(isServer || !started);
    mp_ui->pbConnectToServer->setEnabled(!isServer || !started);
    mp_ui->lePortName->setEnabled(!started);
    mp_ui->leServerName->setEnabled(!started);

    auto stopIcon = QIcon(QStringLiteral(":/Buttons/media-stop-32.png"));
    auto startIcon = QIcon(QStringLiteral(":/Buttons/media-play-16.png"));

    mp_ui->pbStartServer->setIcon(isServer && started ? stopIcon : startIcon);
    mp_ui->pbStartServer->setChecked(isServer && started);
    mp_ui->pbConnectToServer->setIcon(!isServer && started ? stopIcon : startIcon);
    mp_ui->pbConnectToServer->setChecked(!isServer && started);
}

void IpRecorderWgt::m_storeSettings()
{
    UserSettings::store(QStringLiteral("port")
                        , mp_ui->lePortName->text());
    UserSettings::store(QStringLiteral("host")
                        , mp_ui->leServerName->text());
}
