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
    if (mp_server) {
        mp_server->deleteLater();
    }
    if (mp_socket) {
        if (mp_socket->isOpen()) {
            mp_socket->close();
        }
        mp_socket->deleteLater();
    }
    m_closeConnectionTimer();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "ipRecorder");
    settings.setValue("port", mp_ui->lePortName->text());
    settings.setValue("host", mp_ui->leServerName->text());
    delete mp_ui;
}




//=================================== Кнопка старт сервера
void IpRecorderWgt::on_pbStartServer_released()
{
    // Включение или выключение сервера.
    // Сервер включается только если нажата
    // соответствующая radioButton

    if (mp_server) {    //Если сервер был запущен - выключить
        mp_server->close();
        mp_server->deleteLater();
        mp_server = nullptr;
        if (mp_socket) {
            mp_socket->disconnect();
            mp_socket->deleteLater();
            mp_socket = nullptr;
        }

        m_updateUi(true, false);
    } else {
        mp_server = new QTcpServer();
        mp_server->setMaxPendingConnections(1);

        connect(mp_server,  &QTcpServer     ::newConnection,
                this,       &IpRecorderWgt  ::sl_newServerConnection);

        bool success {true};
        mp_server->listen(QHostAddress::Any, mp_ui->lePortName->text().toInt(&success, 10));
        if (!success) {
            QMessageBox::warning(0, "Ошибка запуска сервера", mp_server->errorString());
            mp_server->deleteLater();
            mp_server = nullptr;
            return;
        }

        m_updateUi(true, true);
    }
}




//=================================== Кнопка подключиться к серверу
void IpRecorderWgt::on_pbConnectToServer_released()
{
    // Запуск или остановка сокетного соединения с сервером
    // Запуск производится только если отмечена соответствующая radioButton
    if (mp_socket) {    //Если сокет был подключен - отключить
        mp_socket->disconnect();
        mp_socket->deleteLater();
        mp_socket = nullptr;

        m_updateUi(false, false);

        if (mp_connectionTimer) {
            mp_connectionTimer->stop();
            mp_connectionTimer->deleteLater();
            mp_connectionTimer = nullptr;
        }
    } else {
        mp_socket = new QTcpSocket();
        connect(mp_socket,          &QTcpSocket     ::connected,
                this,               &IpRecorderWgt  ::sl_socketConnected   );
        connect(mp_socket,          &QTcpSocket     ::disconnected,
                this,               &IpRecorderWgt  ::sl_socketDisconnected);
        connect(mp_socket,          &QTcpSocket     ::readyRead,
                mp_recorderForm,    &RecorderForm   ::sl_writeToFile       );
        m_connectToHost();

        if (!mp_connectionTimer) {
            mp_connectionTimer = new QTimer();
            connect(mp_connectionTimer, &QTimer         ::timeout,
                    this,               &IpRecorderWgt  ::sl_connectionTimerTimeout);
            mp_connectionTimer->start(200);
        }

        m_updateUi(false, true);
    }
}




//=================================== Слот нового подключения к серверу
void  IpRecorderWgt::sl_newServerConnection()
{
    if (!mp_socket) {
        mp_socket = mp_server->nextPendingConnection();

        connect(mp_socket,          &QTcpSocket     ::disconnected,
                this,               &IpRecorderWgt  ::sl_socketDisconnected);
        connect(mp_socket,          &QTcpSocket     ::readyRead,
                mp_recorderForm,    &RecorderForm   ::sl_writeToFile       );

        sl_socketConnected();
    }
}




//=================================== Слот установки соединения сокета
void IpRecorderWgt::sl_socketConnected()
{
    mp_socket->open(QIODevice::ReadWrite);

    if (mp_playerForm) {
        mp_playerForm->setSocket(mp_socket);
    }

    if (mp_ui->pbConnectToServer->isChecked()) {
        mp_ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
    }

    mp_ui->lbConnectionStatus->setText("Установлено соединение");
    mp_ui->lbConnectionStatus->setStyleSheet("background-color: rgb(64, 152, 50);");
}




//=================================== Слот разрыва соединения сокета
void IpRecorderWgt::sl_socketDisconnected()
{
    mp_ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-play-16.png"));
    mp_socket->deleteLater();
    mp_socket = nullptr;
    if (mp_playerForm) {
        mp_playerForm->setSocket(nullptr);
    }
    mp_ui->lbConnectionStatus->setText("Соединение потеряно");
    mp_ui->lbConnectionStatus->setStyleSheet("background-color: rgb(211, 36, 54);");
}




//=================================== Слот таймера соединения
void IpRecorderWgt::sl_connectionTimerTimeout()
{
    if (mp_socket->state() == QAbstractSocket::UnconnectedState) {
        m_connectToHost();
    } else if (mp_socket->state() == QAbstractSocket::ConnectedState) {
        m_closeConnectionTimer();
    }
}




//===================================
void IpRecorderWgt::m_initSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "ipRecorder");

    if (!settings.contains("port")) {
        settings.setValue("port", "5000");
    } else {
        mp_ui->lePortName->setText(settings.value("port").toString());
    }
    if (!settings.contains("host")) {
        settings.setValue("host", "127.0.0.1");
    } else {
        mp_ui->leServerName->setText(settings.value("host").toString());
    }
}




//=================================== Функция соединения с сервером
void IpRecorderWgt::m_connectToHost()
{
    bool success {true};
    mp_socket->connectToHost(mp_ui->leServerName->text(),
                             mp_ui->lePortName->text().toInt(&success, 10),
                             QIODevice::ReadWrite);
    if (!success) {
        QMessageBox::warning(nullptr, "Ошибка", "Ошибочно указан порт");
    }
}




//=================================== Функция закрытия сетевного соединения
void IpRecorderWgt::m_closeConnectionTimer()
{
    // Функция закрытия таймера соединения
    if (mp_connectionTimer) {
        mp_connectionTimer->stop();
        mp_connectionTimer->deleteLater();
        mp_connectionTimer = nullptr;
    }
}




//===================================
void IpRecorderWgt::m_updateUi(bool isServer, bool started)
{
    mp_ui->pbStartServer->setEnabled(isServer || !started);
    mp_ui->pbConnectToServer->setEnabled(!isServer || !started);
    mp_ui->lePortName->setEnabled(!started);
    mp_ui->leServerName->setEnabled(!started);

    auto stopIcon = QIcon(":/Buttons/media-stop-32.png");
    auto startIcon = QIcon(":/Buttons/media-play-16.png");

    mp_ui->pbStartServer->setIcon(isServer && started ? stopIcon : startIcon);
    mp_ui->pbConnectToServer->setIcon(!isServer && started ? stopIcon : startIcon);
}




//===================================
