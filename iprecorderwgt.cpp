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
    ui(new Ui::IpRecorderWgt)
{
    ui->setupUi(this);
    recorderForm = ui->recorderWgt;
    playerForm = ui->playerWgt;

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    initSettings();
}




//===================================
void IpRecorderWgt::initSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "ipRecorder");

    if (!settings.contains("port")) {
        settings.setValue("port", "5000");
    } else {
        ui->lePortName->setText(settings.value("port").toString());
    }
    if (!settings.contains("address")) {
        settings.setValue("address", "127.0.0.1");
    } else {
        ui->leServerName->setText(settings.value("address").toString());
    }
}




//=================================== Деструктор
IpRecorderWgt::~IpRecorderWgt()
{
    if (server) server->deleteLater();
    if (socket) {
        if (socket->isOpen()) {
            socket->close();
        }
        socket->deleteLater();
    }
    closeConnectionTimer();
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "ipRecorder");
    settings.setValue("port", ui->lePortName->text());
    settings.setValue("address", ui->leServerName->text());
    delete ui;
}




//=================================== Кнопка старт сервера
void IpRecorderWgt::on_pbStartServer_released()
{
    // Включение или выключение сервера.
    // Сервер включается только если нажата
    // соответствующая radioButton

    if (server) {
        server->close();
        server->deleteLater();
        server = NULL;
        if (socket) {
            socket->disconnect();
            socket->deleteLater();
            socket = NULL;
        }

        ui->pbStartServer->setIcon(QIcon(":/Buttons/media-play-16.png"));
        ui->pbConnectToServer->setEnabled(true);
        ui->lePortName->setEnabled(true);
    } else {
        server = new QTcpServer();

        connect(server, &QTcpServer     ::newConnection,
                this,   &IpRecorderWgt  ::newServerConnectionSlot);

        bool success {true};
        server->listen(QHostAddress::Any, ui->lePortName->text().toInt(&success, 10));
        if (!success) {
            QMessageBox::warning(0, "Ошибка запуска сервера", server->errorString());
            server->deleteLater();
            server = NULL;
            return;
        }

        ui->pbStartServer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
        ui->pbConnectToServer->setEnabled(false);
        ui->lePortName->setEnabled(false);
    }
}




//=================================== Кнопка подключиться к серверу
void IpRecorderWgt::on_pbConnectToServer_released()
{
    // Запуск или остановка сокетного соединения с сервером
    // Запуск производится только если отмечена соответствующая radioButton
    if (socket) {
        socket->disconnect();
        socket->deleteLater();
        socket = NULL;
        ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-play-16.png"));
        ui->pbStartServer->setEnabled(true);
        ui->lePortName->setEnabled(true);
        if (connectionTimer) {
            connectionTimer->stop();
            connectionTimer->deleteLater();
            connectionTimer = NULL;
        }
    } else {
        socket = new QTcpSocket();
        connect(socket,         &QTcpSocket     ::connected,
                this,           &IpRecorderWgt  ::slSocketConnected   );
        connect(socket,         &QTcpSocket     ::disconnected,
                this,           &IpRecorderWgt  ::slSocketDisconnected);
        connect(socket,         &QTcpSocket     ::readyRead,
                recorderForm,   &RecorderForm   ::slWriteToFile       );
        connectToHost();
        if (!connectionTimer) {
            connectionTimer = new QTimer();
            connect(connectionTimer,    &QTimer         ::timeout,
                    this,               &IpRecorderWgt  ::slConnectionTimerTimeoutSlot);
            connectionTimer->start(200);
        }

        ui->pbStartServer->setEnabled(false);
        ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
        ui->lePortName->setEnabled(false);
    }
}




//=================================== Слот нового подключения к серверу
void  IpRecorderWgt::newServerConnectionSlot()
{
    if (!socket) {
        socket = server->nextPendingConnection();

        connect(socket,         &QTcpSocket     ::disconnected,
                this,           &IpRecorderWgt  ::slSocketDisconnected);
        connect(socket,         &QTcpSocket     ::readyRead,
                recorderForm,   &RecorderForm   ::slWriteToFile       );

        slSocketConnected();
    }
}




//=================================== Слот установки соединения сокета
void IpRecorderWgt::slSocketConnected()
{
    socket->open(QIODevice::ReadWrite);

    if (playerForm) {
        playerForm->setSocket(socket);
    }

    if (ui->pbConnectToServer->isChecked()) {
        ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
    }

    ui->lbConnectionStatus->setText("Установлено соединение");
    ui->lbConnectionStatus->setStyleSheet("background-color: rgb(64, 152, 50);");

    temp.start(500);
    connect(&temp, &QTimer::timeout, [=] {
        static long code = 111;
        if (socket->isOpen()) {
            socket->write((const char*)&code, 4);
        }
    });
}




//=================================== Слот разрыва соединения сокета
void IpRecorderWgt::slSocketDisconnected()
{
    ui->pbConnectToServer->setIcon(QIcon(":/Buttons/media-play-16.png"));
    socket->deleteLater();
    socket = NULL;
    if (playerForm) {
        playerForm->setSocket(NULL);
    }
    ui->lbConnectionStatus->setText("Соединение потеряно");
    ui->lbConnectionStatus->setStyleSheet("background-color: rgb(211, 36, 54);");
}




//=================================== Слот таймера соединения
void IpRecorderWgt::slConnectionTimerTimeoutSlot()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        connectToHost();
    } else if (socket->state() == QAbstractSocket::ConnectedState) {
        closeConnectionTimer();
    }
}




//=================================== Функция соединения с сервером
void IpRecorderWgt::connectToHost()
{
    bool success {true};
    socket->connectToHost(ui->leServerName->text(),
                          ui->lePortName->text().toInt(&success, 10),
                          QIODevice::ReadWrite);
    if (!success) {
        QMessageBox::warning(0, "Ошибка", "Ошибочно указан порт");
    }
}




//=================================== Функция закрытия сетевного соединения
void IpRecorderWgt::closeConnectionTimer()
{
    // Функция закрытия таймера соединения
    if (connectionTimer) {
        connectionTimer->stop();
        connectionTimer->deleteLater();
        connectionTimer = NULL;
    }
}


