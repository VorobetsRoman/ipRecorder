#include "recorderform.h"
#include "ui_recorderform.h"
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>
#include "fileheader.h"




//=================================== Конструктор
RecorderForm::RecorderForm(QWidget *parent) :
    QWidget(parent),
    mp_ui(new Ui::RecorderForm)
{
    mp_ui->setupUi(this);
}




//=================================== Деструктор
RecorderForm::~RecorderForm()
{
    if (mp_workFile){
        if (mp_workFile->isOpen()) {
            mp_workFile->close();
        }
        mp_workFile->deleteLater();
    }
    delete mp_ui;
}




//=================================== Кнопка выбора файла для записи
void RecorderForm::on_tbFileNameForRecording_released()
{
    // Слот выбора файла для записи
    QString fileName = QFileDialog::getSaveFileName(
                nullptr
                , QStringLiteral("Файл для записи")
                , qApp->applicationDirPath()
                , "*.dat");
    if (fileName == "") return;

    if (!mp_workFile) {
        mp_workFile = new QFile();
    } else {
        if (mp_workFile->isOpen()) {
            mp_workFile->close();
        }
    }

    mp_workFile->setFileName(fileName);
    if (!mp_workFile->open(QIODevice::WriteOnly)) {
        QMessageBox::warning(
                    nullptr
                    , QStringLiteral("Ошибка файла")
                    , QStringLiteral("Файл не открывается для записи"));
        return;
    }

    mp_ui->lbFileNameForRecording->setText(fileName);
}




//=================================== Кнопка запуска записи
void RecorderForm::on_pbStartStopRecord_released()
{
    // По нажатию на кнопку "старт" файл пишется с начала
    if (m_recordingIsOn) {
        mp_ui->pbStartStopRecord->setIcon(QIcon(QStringLiteral(":/Buttons/media-record-16.png")));
        mp_ui->cbTimeMarker->setEnabled(true);
        mp_ui->cbCompression->setEnabled(true);
        if (mp_workFile && mp_workFile->isOpen()) {
            mp_workFile->close();
        }
        if (mp_recordTimer) {
            mp_recordTimer->stop();
            delete mp_recordTimer;
        }
    } else {
        mp_ui->pbStartStopRecord->setIcon(QIcon(QStringLiteral(":/Buttons/media-stop-32.png")));
        mp_ui->cbTimeMarker->setEnabled(false);
        mp_ui->cbCompression->setEnabled(false);
        if (mp_workFile && !mp_workFile->isOpen()) {
            mp_workFile->open(QIODevice::WriteOnly);
            m_tickCount = 0;
            m_fileSize = 0;
            m_lastTime = QTime::currentTime();
        }
        m_initRecordTimer();
        m_writeHeader();
    }
    m_recordingIsOn = !m_recordingIsOn;
}




//=================================== Кнопка паузы записи
void RecorderForm::on_pbPauseRecord_released()
{
    if (m_pauseOn) {
//        ui->pbPauseRecord->setIcon(QIcon(":\Buttons\media-pause-16.png"));
    }
    else {
//        ui->pbPauseRecord->setIcon(QIcon(":\Buttons\media-record-16.png"));
    }
    m_pauseOn = !m_pauseOn;
}




//=================================== Функция записи в файл
void RecorderForm::sl_writeToFile()
{
    if (!mp_workFile) return;
    if (!mp_workFile->isOpen()) return;
    if (!m_recordingIsOn) return;

    if (mp_ui->cbTimeMarker->isChecked()) {
        qint32 timeDelay = m_lastTime.msecsTo(QTime::currentTime());
        m_lastTime = QTime::currentTime();
        mp_workFile->write((char*)&timeDelay, sizeof(timeDelay));
    }

    QTcpSocket* socket = (QTcpSocket*)sender() ;
    QByteArray ba = socket->readAll();
    if (m_comressionIsOn) {
        ba = qCompress(ba);
    }
    qint64 packetSize = ba.size();
    mp_workFile->write((char*)&packetSize, sizeof(packetSize));
    mp_workFile->write(ba);

    ++m_tickCount;
    m_fileSize += packetSize;
    mp_ui->lbRecordedCount->setText(QString::number(m_tickCount));
    mp_ui->lbRecordedSize->setText(QString::number(m_fileSize / (1024 * 1024)));
}




//=================================== Слот отметки включения маркера
void RecorderForm::on_cbTimeMarker_toggled(bool setOn)
{
    m_timeMarkerIsOn = setOn;
}




//===================================
void RecorderForm::m_writeHeader()
{
    // Перейти в начало файла, записать размер заголовка,
    // Записать сам заголовок
    mp_workFile->seek(0);

    FileHeader fileHeader;
    fileHeader.timeMarkerExist = m_timeMarkerIsOn;
    fileHeader.compressionExist = m_comressionIsOn;
    mp_workFile->write((char*)&fileHeader, FileHeader::size());
}




//===================================
void RecorderForm::m_initRecordTimer()
{
    mp_recordTimer = new QTimer();
    mp_recordTimer->setInterval(1);
    connect(mp_recordTimer, &QTimer::timeout, this, [=] {
        auto time = QTime::fromMSecsSinceStartOfDay(m_lastTime.msecsTo(QTime::currentTime()));
        mp_ui->lb_recTime->setText(time.toString("hh:mm:ss:zzz"));
    });
    mp_recordTimer->start();
}




//===================================
void RecorderForm::on_cd_compression_toggled(bool checked)
{
    m_comressionIsOn = checked;
}




//===================================
