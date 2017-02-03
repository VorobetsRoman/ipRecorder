#include "iprecorderwgt.h"
#include "ui_iprecorderwgt.h"
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>




//===================================
IpRecorderWgt::IpRecorderWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpRecorderWgt)
{
    ui->setupUi(this);
    recorderForm = ui->recorderWgt;
    playerForm = ui->playerWgt;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    ui->tabPlayRecord->setTabText(0, "Запись");
    ui->tabPlayRecord->setTabText(1, "Воспроизведение");
}




//=================================== Деструктор
IpRecorderWgt::~IpRecorderWgt()
{
    if (server) server->deleteLater();
    if (socket) socket->deleteLater();
    closeConnectionTimer();
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
        ui->pbStartServer->setText("Запустить");
    }
    else if (ui->rbServerChoice->isChecked()) {
        server = new QTcpServer();

        connect(server, &QTcpServer     ::newConnection,
                this,   &IpRecorderWgt  ::newServerConnectionSlot);

        bool success {true};
        server->listen(QHostAddress::Any, ui->lePortName->text().toInt(&success, 10));
        if (!success) {
            QMessageBox::warning(0, "Ошибка", "Ошибочно введен номер порта");
            return;
        }
        ui->pbStartServer->setText("Остановить");
    }
}




//=================================== Отметка
void IpRecorderWgt::on_rbClientChoice_toggled(bool checked)
{

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
        ui->pbConnectToServer->setText("Соединиться");
    }
    else if (ui->rbClientChoice->isChecked()) {
        if (!socket) {
            socket = new QTcpSocket();
            connect(socket, &QTcpSocket     ::connected,
                    this,   &IpRecorderWgt  ::socketConnected   );
            connect(socket, &QTcpSocket     ::disconnected,
                    this,   &IpRecorderWgt  ::socketDisconnected);
            connect(socket, &QTcpSocket     ::readyRead,
                    this,   &IpRecorderWgt  ::socketReadyRead   );
        }
        connectToHost();
        if (!connectionTimer) {
            connectionTimer = new QTimer();
            connect(connectionTimer,    &QTimer         ::timeout,
                    this,               &IpRecorderWgt  ::connectionTimerTimeoutSlot);
            connectionTimer->start(200);
        }
    }
}




//=================================== Слот нового подключения к серверу
void  IpRecorderWgt::newServerConnectionSlot()
{
    if (!socket) {
        socket = server->nextPendingConnection();

        connect(socket, &QTcpSocket     ::disconnected,
                this,   &IpRecorderWgt  ::socketDisconnected);
        connect(socket, &QTcpSocket     ::readyRead,
                this,   &IpRecorderWgt  ::socketReadyRead   );

        if (!socket->open(QIODevice::ReadWrite)) {
            qDebug() << "Ошибка открытия сокета";
        }

        ui->lbConnectionStatus->setText("Установлено соединение");
    }
}




//=================================== Слот установки соединения сокета
void IpRecorderWgt::socketConnected()
{
    socket->open(QIODevice::ReadWrite);
    ui->pbConnectToServer->setText("Разъединиться");
    ui->lbConnectionStatus->setText("Установлено соединение");
}




//=================================== Слот разрыва соединения сокета
void IpRecorderWgt::socketDisconnected()
{
    ui->pbConnectToServer->setText("Соединиться");
    socket->deleteLater();
    socket = NULL;
    ui->lbConnectionStatus->setText("Соединения потеряно");
}




//=================================== Слот таймера соединения
void IpRecorderWgt::connectionTimerTimeoutSlot()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        connectToHost();
    }
    else if (socket->state() == QAbstractSocket::ConnectedState) {
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




//=================================== Слот чтения из сокета
void IpRecorderWgt::socketReadyRead()
{
    // Функция чтения данных из сокета
    // и записи данных в файл
//    if (fileName == "") return;
//    if (!recordingOn)   return;
//    if (recordingPaused) return;

//    QByteArray ba = socket->readAll();
//    qint64 packetSize = ba.size();
//    workFile.write((char*)&packetSize, sizeof(packetSize));
//    qint64 saved = workFile.write(ba);
//    if (saved < ba.size()) {
//        QMessageBox::warning(0, "Ошибка", "В файл записалось меньше прочитанного, запись приостановлена");
//        recordingPaused = true;
        // добавить функцию остановки записи
//    }
}




