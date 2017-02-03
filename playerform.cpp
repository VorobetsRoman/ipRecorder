#include "playerform.h"
#include "ui_playerform.h"




//===================================
PlayerForm::PlayerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerForm)
{
    ui->setupUi(this);
}



//===================================
PlayerForm::~PlayerForm()
{
    delete ui;
}




//===================================
void PlayerForm::on_tbFileNameForPlayer_released()
{
    // Слот выбора файла для воспроизведения
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
    if (!workFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, "Ошибка файла", "Файл не открывается для записи");
        return;
    }

    ui->lbFileNameForPlayer->setText(fileName);
}




//===================================
void PlayerForm::on_rbSetPlaySpeed_toggled(bool checked)
{
    if (playTimer && playTimer->isActive()) {
        playTimer->setInterval(defaultPlayInterval);
    }
}




//===================================
void PlayerForm::on_rbTimeMarkerIsOn_toggled(bool checked)
{
    if (playTimer && playTimer->isActive()) {
        playTimer->setInterval(timeInterval);
    }
}




//===================================
void PlayerForm::on_hsPlaySpeed_sliderMoved(int position)
{
    defaultPlayInterval = pow(1.5, position);
    if (playTimer->isActive()) {
        playTimer->setInterval(defaultPlayInterval);
    }
}




//===================================
void PlayerForm::on_pbStartStopPlayer_released()
{
    if (playingOn) {
        playinGotoBegin();
        workFile.close();
        if (playTimer) {
            playTimer->stop();
        }
    }
    else {
        if (!workFile.isOpen()) {
            workFile.setFileName(fileName);
            if (!workFile.open(QIODevice::ReadOnly)) {
                    qDebug() << "file open is unsuccessfully";
                    return;
            }
        }

        if (!playTimer) {
            playTimer = new QTimer;
            connect(playTimer,  &QTimer         ::timeout,
                    this,       &IpRecorderWgt  ::playTimerTimeoutSlot);
        }
        if (!ui->rbTimeMarkerIsOn->isChecked()) {
            playTimer->start(timeInterval);
        }
    }
    playingOn = !playingOn;
}

void PlayerForm::on_pbPauseRecord_2_released()
{

}




//=================================== Слот таймера воспроизведения
void IpRecorderWgt::playTimerTimeoutSlot()
{
    if (!workFile.isOpen()) return;
    if (!socket) return;
    if (!socket->isOpen()) return;

    qint64 packetSize = workFile.read((char*)&packetSize, sizeof(packetSize));
    QByteArray ba = workFile.read(packetSize);
    socket->write(ba);
}




