#include "recorderform.h"
#include "ui_recorderform.h"




//===================================
RecorderForm::RecorderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecorderForm)
{
    ui->setupUi(this);
}




//=================================== Деструктор
RecorderForm::~RecorderForm()
{
    delete ui;
}




//===================================
void RecorderForm::on_tbFileNameForRecording_released()
{
    // Слот выбора файла для записи
    fileName = QFileDialog::getSaveFileName(0, "Файл для записи", qApp->applicationDirPath(), "*.dat");
    if (fileName == "") return;
    ui->lbFileNameForRecording->setText(fileName);
}




//===================================
void RecorderForm::on_pbStartStopRecord_released()
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
void RecorderForm::on_pbPauseRecord_released()
{
    if (recordingPaused) {

    }
    else {

    }
    recordingPaused = !recordingPaused;
}
