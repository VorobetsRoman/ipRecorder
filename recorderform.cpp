#include "recorderform.h"
#include "ui_recorderform.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include "fileheader.h"




//=================================== Конструктор
RecorderForm::RecorderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecorderForm)
{
    ui->setupUi(this);
}




//=================================== Деструктор
RecorderForm::~RecorderForm()
{
    if (workFile){
        if (workFile->isOpen()) {
            workFile->close();
        }
        workFile->deleteLater();
    }
    delete ui;
}




//=================================== Кнопка выбора файла для записи
void RecorderForm::on_tbFileNameForRecording_released()
{
    // Слот выбора файла для записи
    QString fileName = QFileDialog::getSaveFileName(0, "Файл для записи", qApp->applicationDirPath(), "*.dat");
    if (fileName == "") return;

    if (!workFile) {
        workFile = new QFile();
    }
    else {
        if (workFile->isOpen()) {
            workFile->close();
        }
    }

    workFile->setFileName(fileName);
    if (!workFile->open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0, "Ошибка файла", "Файл не открывается для записи");
        return;
    }

    ui->lbFileNameForRecording->setText(fileName);

    writeHeader();
}




//=================================== Кнопка запуска записи
void RecorderForm::on_pbStartStopRecord_released()
{
    // По нажатию на кнопку "старт" файл пишется с начала
    if (recordingOn) {
        ui->pbStartStopRecord->setIcon(QIcon(":/Buttons/media-record-16.png"));
        ui->cbTimeMarker->setEnabled(true);
        if (workFile && workFile->isOpen()) {
            workFile->close();
        }
    }
    else {
        ui->pbStartStopRecord->setIcon(QIcon(":/Buttons/media-stop-32.png"));
        ui->cbTimeMarker->setEnabled(false);
        if (workFile && !workFile->isOpen()) {
            workFile->open(QIODevice::WriteOnly);
            tickCount = 0;
            fileSize = 0;
            lastTime = QTime::currentTime();
        }
    }
    recordingOn = !recordingOn;
}




//=================================== Кнопка паузы записи
void RecorderForm::on_pbPauseRecord_released()
{
    if (pauseOn) {
//        ui->pbPauseRecord->setIcon(QIcon(":\Buttons\media-pause-16.png"));
    }
    else {
//        ui->pbPauseRecord->setIcon(QIcon(":\Buttons\media-record-16.png"));
    }
    pauseOn = !pauseOn;
}




//=================================== Функция записи в файл
void RecorderForm::writeToFile()
{
    if (!workFile) return;
    if (!workFile->isOpen()) return;
    if (!recordingOn) return;

    if (ui->cbTimeMarker->isChecked()) {
        qint32 timeDelay = lastTime.msecsTo(QTime::currentTime());
        lastTime = QTime::currentTime();
        workFile->write((char*)&timeDelay, sizeof(timeDelay));
    }

    QTcpSocket* socket = (QTcpSocket*)sender() ;
    QByteArray ba = socket->readAll();
    qint64 packetSize = ba.size();
    workFile->write((char*)&packetSize, sizeof(packetSize));
    workFile->write(ba);

    tickCount++;
    fileSize += packetSize;
    ui->lbRecordedCount->setText(QString::number(tickCount));
    ui->lbRecordedSize->setText(QString::number(fileSize / (1024 * 1024)));
}




//=================================== Слот отметки включения маркера
void RecorderForm::on_cbTimeMarker_toggled(bool)
{
    if (workFile && workFile->isOpen()) {
        writeHeader();
    }
}




//===================================
void RecorderForm::writeHeader()
{
    // Перейти в начало файла, записать размер заголовка,
    // Записать сам заголовок
    workFile->seek(0);
    qint64 headerSize = sizeof(FileHeader);
    workFile->write((char*)&headerSize, sizeof(headerSize));

    FileHeader fileHeader;
    fileHeader.timeMarkerExist = ui->cbTimeMarker->isChecked() ? 1 : 0;
    workFile->write((char*)&fileHeader, headerSize);
}




