#include "playerform.h"
#include "ui_playerform.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "fileheader.h"



//=================================== Конструктор
PlayerForm::PlayerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerForm)
{
    ui->setupUi(this);
}




//=================================== Деструктор
PlayerForm::~PlayerForm()
{
    if (playTimer) {
        if (playTimer->isActive()) playTimer->stop();
        playTimer->deleteLater();
    }
    if (workFile) {
        if (workFile->isOpen()) workFile->close();
        workFile->deleteLater();
    }
    if (socket) {
        if (socket->isOpen()) socket->close();
        socket->deleteLater();
    }
    delete ui;
}




//=================================== Слот кнопки выбора имени файла
void PlayerForm::on_tbFileNameForPlayer_released()
{
    // Слот выбора файла для воспроизведения
    QString fileName = QFileDialog::getOpenFileName(0, "Файл для чтения", qApp->applicationDirPath(), "*.dat");
    if (fileName == "") return;

    if (!workFile) {
        workFile = new QFile();
    }
    else {
        if (workFile->isOpen()) {
            workFile->close();
        }
    }

    QFile test(fileName);
    workFile->setFileName(fileName);
    if (!workFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, "Ошибка файла", "Файл не открывается для записи");
        return;
    }

    ui->lbFileNameForPlayer->setText(fileName);

    // Вычитать заголовок из файла, определить наличие временного маркера
    qint64 fileHeaderSize {0};
    workFile->read((char*)&fileHeaderSize, sizeof(fileHeaderSize));
    FileHeader fileHeader;
    workFile->read((char*)&fileHeader, fileHeaderSize);
    switch (fileHeader.timeMarkerExist) {
    case 0:
        timeMarkerExist = false;
        ui->rbSetPlaySpeed->toggle();
        ui->rbTimeMarkerIsOn->setDisabled(true);
        break;
    case 1:
        timeMarkerExist = true;
        ui->rbTimeMarkerIsOn->setEnabled(true);
        break;
    default:
        break;
    }

    // Если есть временной маркер, выкинуть его первое значение
    if (timeMarkerExist) {
        qint32 timeDelay;
        workFile->read((char*)&timeDelay, sizeof(timeDelay));
    }
}




//=================================== Слот использования скорости воспроизведения
void PlayerForm::on_rbSetPlaySpeed_toggled(bool)
{
    if (playTimer && playTimer->isActive()) {
//        playTimer->setInterval(playDelay);
    }
}




//=================================== Слот использования сохраненной задержки перед воспроизведением
void PlayerForm::on_rbTimeMarkerIsOn_toggled(bool)
{
    if (playTimer && playTimer->isActive()) {
        playTimer->setInterval(playDelay);
    }
}




//=================================== Слот изменения скорости воспроизведения
void PlayerForm::on_hsPlaySpeed_sliderMoved(int position)
{
    playDelay = pow(3, position);
    if (playTimer && playTimer->isActive()) {
        playTimer->setInterval(playDelay);
    }
}




//=================================== Слот кнопки запуска воспроизведения
void PlayerForm::on_pbStartStopPlayer_released()
{
    if (!(workFile && workFile->isOpen()
          && socket && socket->isOpen())) return;

    if (playingIsOn)
    {
        ui->pbStartStopPlayer->setIcon(QIcon(":/Buttons/media-play-16.png"));
        workFile->close();
        if (playTimer) {
            playTimer->stop();
        }
    }
    else
    {
        ui->pbStartStopPlayer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
        if (!workFile->isOpen()) {
            if (!workFile->open(QIODevice::ReadOnly)) {
                qDebug() << "file open is unsuccessfully";
                return;
            }
        }

        if (!playTimer) {
            playTimer = new QTimer;
            connect(playTimer,  &QTimer         ::timeout,
                    this,       &PlayerForm     ::playTimerTimeoutSlot);
        }
        playTimer->start(playDelay);
    }
    playingIsOn = !playingIsOn;
}




//=================================== Слот кнопки паузы воспроизведения
void PlayerForm::on_pbPausePlay_released()
{

}




//=================================== Слот таймера воспроизведения
void PlayerForm::playTimerTimeoutSlot()
{
    if (!workFile->isOpen()) return;
    if (!socket) return;
    if (!socket->isOpen()) return;
    if (workFile->atEnd()) {
        workFileAtEnd();
        return;
    }

    qint64 packetSize {0};
    workFile->read((char*)&packetSize, sizeof(packetSize));
    QByteArray ba = workFile->read(packetSize);
//    qDebug() << ba;
    socket->write(ba);

//    int filePos = 100 * workFile->pos() / workFile->size();
    ui->progressPlayer->setValue(100 * workFile->pos() / workFile->size());

    if (workFile->atEnd()) {
        workFileAtEnd();
        return;
    }

    if (timeMarkerExist) {
        qint32 timeDelay {0};
        workFile->read((char*)&timeDelay, sizeof(timeDelay));
//        qDebug() << timeDelay;
        if (ui->rbTimeMarkerIsOn->isChecked()) {
            playTimer->setInterval(timeDelay);
        }
    }
}




//=================================== Инициализация сокета, в который будет происходить запись
void PlayerForm::setSocket(QTcpSocket *newSocket)
{
    socket = newSocket;
}




void PlayerForm::workFileAtEnd()
{
    workFile->seek(0);
    playTimer->stop();
    playingIsOn = false;
}






