#include "iprecorderwgt.h"
#include "ui_iprecorderwgt.h"
//#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QSettings>




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




//=================================== Деструктор
IpRecorderWgt::~IpRecorderWgt()
{
    QSettings settings(QSettings::IniFormat
                       , QSettings::UserScope
                       , QStringLiteral("ipRecorder"));
    settings.setValue("port", mp_ui->lePortName->text());
    settings.setValue("host", mp_ui->leServerName->text());
    delete mp_ui;
}




//=================================== Кнопка старт сервера
void IpRecorderWgt::on_pbStartServer_released()
{

}




//=================================== Кнопка подключиться к серверу
void IpRecorderWgt::on_pbConnectToServer_released()
{

}




//===================================
void IpRecorderWgt::m_initSettings()
{
    QSettings settings(QSettings::IniFormat
                       , QSettings::UserScope
                       , QStringLiteral("ipRecorder"));

    if (!settings.contains(QStringLiteral("port"))) {
        settings.setValue(QStringLiteral("port"), QStringLiteral("5000"));
    } else {
        mp_ui->lePortName->setText(settings.value("port").toString());
    }
    if (!settings.contains(QStringLiteral("host"))) {
        settings.setValue(QStringLiteral("host"), QStringLiteral("127.0.0.1"));
    } else {
        mp_ui->leServerName->setText(settings.value("host").toString());
    }
}




// Реакция интерфейса на нажатие кнопок сервер/сокет
//===================================
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




//===================================
