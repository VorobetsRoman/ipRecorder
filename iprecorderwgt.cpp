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
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->tabPlayRecord->setTabText(0, "Запись");
    ui->tabPlayRecord->setTabText(1, "Воспроизведение");
}




//===================================
IpRecorderWgt::~IpRecorderWgt()
{
    if (server) server->deleteLater();
    if (socket) socket->deleteLater();
    closeConnectionTimer();
    delete ui;
}




//===================================
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




//===================================
void IpRecorderWgt::on_rbClientChoice_toggled(bool checked)
{

}




//===================================
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
        socket = new QTcpSocket();
        connectToHost();
        if (!connectionTimer) {
            connectionTimer = new QTimer();
            connect(connectionTimer,    &QTimer         ::timeout,
                    this,               &IpRecorderWgt  ::connectionTimerTimeoutSlot);
            connectionTimer->start(200);
        }
    }
}




//===================================
void  IpRecorderWgt::newServerConnectionSlot()
{
    if (!socket) {
        socket = server->nextPendingConnection();
        connect(socket, &QTcpSocket     ::disconnected,
                this,   &IpRecorderWgt  ::socketDisconnected);
        connect(socket, &QTcpSocket     ::readyRead,
                this,   &IpRecorderWgt  ::socketReadyRead   );
    }
}




//===================================
void IpRecorderWgt::on_hsPlaySpeed_sliderMoved(int position)
{

}




//===================================
void IpRecorderWgt::on_tbFileNameForRecording_released()
{
    // Слот выбора файла для записи
    fileName = QFileDialog::getSaveFileName(0, "Файл для записи", qApp->applicationDirPath(), "*.dat");
    if (fileName == "") return;
    ui->lbFileNameForRecording->setText(fileName);
}




//===================================
void IpRecorderWgt::on_pbStartStopRecord_released()
{
    if (recordingOn) {
        if (workFile.isOpen()) {
            if (workFile.openMode() == QIODevice::WriteOnly) {
                workFile.close();
            }
        }
    }
    else {
        if (!workFile.isOpen()) {
            workFile.setFileName(fileName);
            workFile.open(QIODevice::WriteOnly);
        }
    }
    recordingOn = !recordingOn;
}




//===================================
void IpRecorderWgt::on_pbPauseRecord_released()
{
    if (recordingPaused) {

    }
    else {

    }
    recordingPaused = !recordingPaused;
}




//===================================
void IpRecorderWgt::on_tbFileNameForPlayer_released()
{
    fileName = QFileDialog::getOpenFileName(0, "Файл для воспроизведения", qApp->applicationDirPath(), "*.dat");
}




//===================================
void IpRecorderWgt::on_pbStartStopPlayer_released()
{
    if (playingOn) {
        playinGotoBegin();
    }
    else {
        if (!playTimer) {
            playTimer = new QTimer;
            connect(playTimer,  &QTimer         ::timeout,
                    this,       &IpRecorderWgt  ::playTimerTimeoutSlot);
        }
        playTimer->start(timeInterval);
    }
    playingOn = !playingOn;
}




//===================================
void IpRecorderWgt::socketConnected()
{
    ui->pbConnectToServer->setText("Разъединиться");

}




//===================================
void IpRecorderWgt::socketDisconnected()
{
    ui->pbConnectToServer->setText("Соединиться");
}




//===================================
void IpRecorderWgt::connectionTimerTimeoutSlot()
{
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        connectToHost();
    }
    else if (socket->state() == QAbstractSocket::ConnectedState) {
        closeConnectionTimer();
    }
}




//===================================
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




//===================================
void IpRecorderWgt::closeConnectionTimer()
{
    // Функция закрытия таймера соединения
    if (connectionTimer) {
        connectionTimer->stop();
        connectionTimer->deleteLater();
        connectionTimer = NULL;
    }
}




//===================================
void IpRecorderWgt::socketReadyRead()
{
    // Функция чтения данных из сокета
    // и записи данных в файл
    if (fileName == "") return;
    if (!recordingOn)   return;
    if (recordingPaused) return;

    QByteArray ba = socket->readAll();
    qint64 packetSize = ba.size();
    workFile.write((char*)&packetSize, sizeof(packetSize));
    qint64 saved = workFile.write(ba);
    if (saved < ba.size()) {
        QMessageBox::warning(0, "Ошибка", "В файл записалось меньше прочитанного, запись приостановлена");
        recordingPaused = true;
        // добавить функцию остановки записи
    }
}




//===================================
void IpRecorderWgt::playinGotoBegin()
{

}




//===================================
void IpRecorderWgt::playTimerTimeoutSlot()
{
    if (!workFile.isOpen()) return;
    if (!socket) return;
    if (socket->isOpen()) return;

    qint64 packetSize = workFile.read((char*)&packetSize, sizeof(packetSize));
    QByteArray ba = workFile.read(packetSize);
    socket->write(ba);
}



