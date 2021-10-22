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
        m_peer = QSharedPointer<Peer>(
                    new ServerPeer(this)
                    , &QObject::deleteLater);
    } else {
        mp_ui->lbConnectionStatus->setText(QStringLiteral("Empty"));
        m_peer.clear();
    }
}

void IpRecorderWgt::on_pbConnectToServer_released()
{
    if (m_peer.isNull()) {
        m_peer = QSharedPointer<Peer>(
                    new SocketPeer(this)
                    , &QObject::deleteLater);
    } else {
        mp_ui->lbConnectionStatus->setText(QStringLiteral("Empty"));
        m_peer.clear();
    }
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

void IpRecorderWgt::m_storeSettings()
{
    UserSettings::store(QStringLiteral("port")
                        , mp_ui->lePortName->text());
    UserSettings::store(QStringLiteral("host")
                        , mp_ui->leServerName->text());
}

void IpRecorderWgt::m_updateUi()
{

}
