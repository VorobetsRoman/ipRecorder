#include "recorderform.h"
#include "ui_recorderform.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>




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
}




//=================================== Кнопка запуска записи
void RecorderForm::on_pbStartStopRecord_released()
{
    if (recordingOn) {
    }
    else {
    }
    recordingOn = !recordingOn;
}




//=================================== Кнопка паузы записи
void RecorderForm::on_pbPauseRecord_released()
{
    if (pauseOn) {

    }
    else {

    }
    pauseOn = !pauseOn;
}




//=================================== Функция записи в файл
void RecorderForm::writeToFile()
{
    if (!workFile) return;
    if (!workFile->isOpen()) return;
    if (!recordingOn) return;

    QTcpSocket* socket = (QTcpSocket*)sender() ;
    QByteArray ba = socket->readAll();
    qint64 packetSize = ba.size();
    workFile->write((char*)&packetSize, sizeof(packetSize));
    workFile->write(ba);
}




