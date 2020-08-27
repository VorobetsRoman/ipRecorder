#include "playerform.h"
#include "ui_playerform.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "fileheader.h"
#include <math.h>



//=================================== Конструктор
PlayerForm::PlayerForm(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::PlayerForm)
{
    mp_ui->setupUi(this);
}




//=================================== Деструктор
PlayerForm::~PlayerForm()
{
    if (mp_playTimer) {
        if (mp_playTimer->isActive()) mp_playTimer->stop();
        mp_playTimer->deleteLater();
    }
    if (mp_workFile) {
        if (mp_workFile->isOpen()) mp_workFile->close();
        mp_workFile->deleteLater();
    }
    if (mp_socket) {
        if (mp_socket->isOpen()) mp_socket->close();
        mp_socket->deleteLater();
    }
    delete mp_ui;
}




//=================================== Слот кнопки выбора имени файла
void PlayerForm::on_tbFileNameForPlayer_released()
{
    // Слот выбора файла для воспроизведения
    QString fileName = QFileDialog::getOpenFileName(0, "Файл для чтения", qApp->applicationDirPath(), "*.dat");
    if (fileName == "") return;

    if (!mp_workFile) {
        mp_workFile = new QFile();
    } else {
        if (mp_workFile->isOpen()) {
            mp_workFile->close();
        }
    }

    QFile test(fileName);
    mp_workFile->setFileName(fileName);
    if (!mp_workFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(0, "Ошибка файла", "Файл не открывается для записи");
        return;
    }

    mp_ui->lbFileNameForPlayer->setText(fileName);

    // Вычитать заголовок из файла, определить наличие временного маркера
    qint64 fileHeaderSize {0};
    mp_workFile->read((char*)&fileHeaderSize, sizeof(fileHeaderSize));
    FileHeader fileHeader;
    mp_workFile->read((char*)&fileHeader, fileHeaderSize);
    switch (fileHeader.timeMarkerExist) {
    case 0:
        m_timeMarkerExist = false;
        mp_ui->rbSetPlaySpeed->toggle();
        mp_ui->rbTimeMarkerIsOn->setDisabled(true);
        break;
    case 1:
        m_timeMarkerExist = true;
        mp_ui->rbTimeMarkerIsOn->setEnabled(true);
        break;
    default:
        break;
    }

    // Если есть временной маркер, выкинуть его первое значение
    if (m_timeMarkerExist) {
        qint32 timeDelay;
        mp_workFile->read((char*)&timeDelay, sizeof(timeDelay));
    }
}




//=================================== Слот использования скорости воспроизведения
void PlayerForm::on_rbSetPlaySpeed_toggled(bool)
{
    if (mp_playTimer && mp_playTimer->isActive()) {
//        playTimer->setInterval(playDelay);
    }
}




//=================================== Слот использования сохраненной задержки перед воспроизведением
void PlayerForm::on_rbTimeMarkerIsOn_toggled(bool)
{
    if (mp_playTimer && mp_playTimer->isActive()) {
        mp_playTimer->setInterval(m_playDelay);
    }
}




//=================================== Слот изменения скорости воспроизведения
void PlayerForm::on_hsPlaySpeed_sliderMoved(int position)
{
    m_playDelay = pow(3, position);
    if (mp_playTimer && mp_playTimer->isActive()) {
        mp_playTimer->setInterval(m_playDelay);
    }
}




//=================================== Слот кнопки запуска воспроизведения
void PlayerForm::on_pbStartStopPlayer_released()
{
    if (!(mp_workFile && mp_workFile->isOpen()
          && mp_socket && mp_socket->isOpen())) return;

    if (m_playingIsOn)
    {
        mp_ui->pbStartStopPlayer->setIcon(QIcon(":/Buttons/media-play-16.png"));
        mp_workFile->close();
        if (mp_playTimer) {
            mp_playTimer->stop();
        }
    } else {
        mp_ui->pbStartStopPlayer->setIcon(QIcon(":/Buttons/media-stop-32.png"));
        if (!mp_workFile->isOpen()) {
            if (!mp_workFile->open(QIODevice::ReadOnly)) {
                qDebug() << "file open is unsuccessfully";
                return;
            }
        }

        if (!mp_playTimer) {
            mp_playTimer = new QTimer;
            connect(mp_playTimer,  &QTimer         ::timeout,
                    this,       &PlayerForm     ::sl_playTimerTimeout);
        }
        mp_playTimer->start(m_playDelay);
    }
    m_playingIsOn = !m_playingIsOn;
}




//=================================== Слот кнопки паузы воспроизведения
void PlayerForm::on_pbPausePlay_released()
{

}




//=================================== Слот таймера воспроизведения
void PlayerForm::sl_playTimerTimeout()
{
    if (!mp_workFile->isOpen()) return;
    if (!mp_socket) return;
    if (!mp_socket->isOpen()) return;
    if (mp_workFile->atEnd()) {
        m_workFileAtEnd();
        return;
    }

    qint64 packetSize {0};
    mp_workFile->read((char*)&packetSize, sizeof(packetSize));
    QByteArray ba = mp_workFile->read(packetSize);
    mp_socket->write(ba);

//    int filePos = 100 * workFile->pos() / workFile->size();
    mp_ui->progressPlayer->setValue(100 * mp_workFile->pos() / mp_workFile->size());

    if (mp_workFile->atEnd()) {
        m_workFileAtEnd();
        return;
    }

    if (m_timeMarkerExist) {
        qint32 timeDelay {0};
        mp_workFile->read((char*)&timeDelay, sizeof(timeDelay));
        if (mp_ui->rbTimeMarkerIsOn->isChecked()) {
            mp_playTimer->setInterval(timeDelay);
        }
    }
}




//=================================== Инициализация сокета, в который будет происходить запись
void PlayerForm::setSocket(QTcpSocket *newSocket)
{
    mp_socket = newSocket;
}




void PlayerForm::m_workFileAtEnd()
{
    mp_workFile->seek(0);
    mp_playTimer->stop();
    m_playingIsOn = false;
}





